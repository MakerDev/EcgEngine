#include "AndroidLauncherScene.h"
#include "ui/CocosGUI.h"
#include "FileHelper.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace std;
using namespace network;

Scene* AndroidLauncherScene::createScene() {
	auto scene = Scene::create();

	auto layer = AndroidLauncherScene::create();
	scene->addChild(layer);

	return scene;
}

bool AndroidLauncherScene::init()
{
	_ecgRuntime = std::make_unique<Runtime>();

	const auto viewSize = Director::getInstance()->getVisibleSize();

	auto infoLabel = Label::createWithSystemFont("FileName:", "Arial", 60);
	infoLabel->setPosition(viewSize.width / 2, viewSize.height / 2 + 100);
	this->addChild(infoLabel);

	auto textField = ui::TextField::create("Click here to enter the package name", "Arial", 45);
	textField->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {

		});
	textField->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2));

	this->addChild(textField);

	auto debugLabel = Label::createWithSystemFont("Debug label", "Arial", 30);
	debugLabel->setPosition(viewSize.width / 2, viewSize.height - 100);
	_infoLabel = infoLabel;
	this->addChild(infoLabel);

	auto fetchButton = Button::create("HelloWorld.png");
	fetchButton->addTouchEventListener([this, debugLabel, textField](Ref* sender, ui::Widget::TouchEventType type) {
		_packageName = textField->getString();
		debugLabel->setString(_packageName);
		if (_packageName.empty())
		{
			_packageName = "ecgpackagetest";
		}
		CCLOG("PACKAGE NAME IS : %s\n", _packageName.c_str());
		DownloadAndUnzipPackage(_packageName);
		});
	fetchButton->setPosition(Vec2(viewSize.width / 2, 100));

	this->addChild(fetchButton);

	auto playButton = Button::create("HelloWorld.png");
	playButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
		if (_downloadRunning || _unziping)
		{
			return;
		}

		RunPackage(_packageName);
		});
	playButton->setPosition(Vec2(viewSize.width / 2 + 500, 100));
	this->addChild(playButton);

	return true;
}

void AndroidLauncherScene::DownloadAndUnzipPackage(const std::string& packageName)
{
	const std::string fileName = packageName + ".zip";
	const std::string packageUrl = PACKAGE_SERVER_URL + "/" + fileName;
	std::string filePath = FileUtils::getInstance()->getWritablePath() + fileName;

	_downloadRunning = true;

	network::HttpRequest* request = new (std::nothrow) network::HttpRequest();
	request->setUrl(packageUrl);
	request->setRequestType(network::HttpRequest::Type::GET);
	request->setResponseCallback(CC_CALLBACK_2(AndroidLauncherScene::onHttpRequestCompleted, this));

	_packageName = packageName;

	network::HttpClient::getInstance()->sendImmediate(request);

	request->release();

	_infoLabel->setString("Downloading...");
	CCLOG("download started");
}

void AndroidLauncherScene::RunPackage(const std::string& packageName)
{
	FileUtils::getInstance()->addSearchPath(FileUtils::getInstance()->getWritablePath());

	//TODO: change file name
	_ecgRuntime->CreateScene(packageName, "ecgsave1.json");
	_ecgRuntime->Run();
}

void AndroidLauncherScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
{
	if (!response)
	{
		_infoLabel->setString("Download failed");

		return;
	}
	_downloadRunning = false;
	_infoLabel->setString("Download completed!");
	_unziping = true;

	// Dump the data
	std::vector<char>* buffer = response->getResponseData();

	auto zipfile = cocos2d::ZipFile::createWithBuffer(&buffer->front(), buffer->size());
	auto contentFileName = zipfile->getFirstFilename();
	std::string filename = contentFileName;

	std::string directoryName =
		cocos2d::FileUtils::getInstance()->getWritablePath() + _packageName + "/";

	if (!cocos2d::FileUtils::getInstance()->isDirectoryExist(directoryName)) {
		cocos2d::FileUtils::getInstance()->createDirectory(directoryName);
	}

	ssize_t dataSize = 0;
	unsigned char* data = zipfile->getFileData(contentFileName, &dataSize);

	while (data != nullptr) {
		FileHelper::RemoveDirectoryInPath(&filename, "Resources");
		FileHelper::RemoveDirectoryInPath(&filename, "Fonts");

		std::string fullFileName = directoryName + filename;

		CCLOG("%s\n", fullFileName.c_str());

		FILE* fp = fopen(fullFileName.c_str(), "wb");

		if (fp) {
			fwrite(data, 1, dataSize, fp);
			fclose(fp);
		}

		free(data);

		contentFileName = zipfile->getNextFilename();
		filename = contentFileName;

		data = zipfile->getFileData(contentFileName, &dataSize);
	}

	_unziping = false;

	_infoLabel->setString("Unzip completed!");
	CCLOG("Unzip completed");
}

bool AndroidLauncherScene::UnzipPackage(const std::string& packageName)
{
	string zipFilePath = FileUtils::getInstance()->fullPathForFilename(packageName + ".zip");
	auto zipData = FileUtils::getInstance()->getDataFromFile(zipFilePath);
	ssize_t t = 0;
	auto dataFromZip = FileUtils::getInstance()->getFileDataFromZip(zipFilePath, "ecgsave1.json", &t);

	auto zipfile = cocos2d::ZipFile::createWithBuffer(zipData.getBytes(), zipData.getSize());
	auto contentFileName = zipfile->getFirstFilename();
	std::string filename = contentFileName;

	std::string directoryName =
		cocos2d::FileUtils::getInstance()->getWritablePath() + packageName + "/";

	if (!cocos2d::FileUtils::getInstance()->isDirectoryExist(directoryName)) {
		cocos2d::FileUtils::getInstance()->createDirectory(directoryName);
	}

	ssize_t dataSize = 0;
	unsigned char* data = zipfile->getFileData(contentFileName, &dataSize);

	while (data != nullptr) {
		std::string fullFileName = directoryName + filename;

		CCLOG("%s\n", fullFileName.c_str());

		FILE* fp = fopen(fullFileName.c_str(), "wb");

		if (fp) {
			fwrite(data, 1, dataSize, fp);
			fclose(fp);
		}

		free(data);

		contentFileName = zipfile->getNextFilename();
		filename = contentFileName;

		data = zipfile->getFileData(contentFileName, &dataSize);
	}

	return true;
}