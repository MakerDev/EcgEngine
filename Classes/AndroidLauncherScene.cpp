#include "AndroidLauncherScene.h"
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
    _infoLabel = infoLabel;
    this->addChild(infoLabel);

	_packageNameField = ui::TextField::create("Click here to enter the package name", "Arial", 45);
	_packageNameField->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {

		});
	_packageNameField->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2));

	this->addChild(_packageNameField);

	auto debugLabel = Label::createWithSystemFont("Debug label", "Arial", 30);
	debugLabel->setPosition(viewSize.width / 2, viewSize.height - 100);
	this->addChild(debugLabel);

	auto fetchButton = Button::create("HelloWorld.png");
	fetchButton->addTouchEventListener([this, debugLabel](Ref* sender, ui::Widget::TouchEventType type) {
		auto& packageName = getPackageName();

        debugLabel->setString(packageName);
        CCLOG("PACKAGE NAME IS : %s\n", packageName.c_str());
		downloadAndUnzipPackage(packageName);
		});
	fetchButton->setPosition(Vec2(viewSize.width / 2, 100));

	this->addChild(fetchButton);

	auto playButton = Button::create("HelloWorld.png");
	playButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
		if (_downloadRunning || _unziping)
		{
			return;
		}

		runPackage();
		});
	playButton->setPosition(Vec2(viewSize.width / 2 + 500, 100));
	this->addChild(playButton);

	return true;
}

void AndroidLauncherScene::downloadAndUnzipPackage(const std::string& packageName)
{
	if (packageName.empty())
	{
		_infoLabel->setString("Invalid PackageName");
		return;
	}

	const std::string fileName = packageName + ".zip";
	const std::string packageUrl = PACKAGE_SERVER_URL + "/" + fileName;

	_downloadRunning = true;

	network::HttpRequest* request = new (std::nothrow) network::HttpRequest();
	request->setUrl(packageUrl);
	request->setRequestType(network::HttpRequest::Type::GET);
	request->setResponseCallback(CC_CALLBACK_2(AndroidLauncherScene::onHttpRequestCompleted, this));

	network::HttpClient::getInstance()->sendImmediate(request);

	request->release();

	_infoLabel->setString("Downloading...");
	CCLOG("download started");
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

	int code = response->getResponseCode();

	if (code == 404)
    {
	    _infoLabel->setString("Error during downloading");
	    return;
    }
    // Dump the data
	std::vector<char>* buffer = response->getResponseData();
	auto zipfile = cocos2d::ZipFile::createWithBuffer(&buffer->front(), buffer->size());
	auto contentFileName = zipfile->getFirstFilename();
	std::string filename = contentFileName;

	std::string directoryName =
		cocos2d::FileUtils::getInstance()->getWritablePath() + getPackageName() + "/";

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

void AndroidLauncherScene::runPackage()
{
	auto& packageName = getPackageName();

	if (packageName.empty())
	{
		_infoLabel->setString("Invalid Package Name");
		return;
	}

	FileUtils::getInstance()->addSearchPath(FileUtils::getInstance()->getWritablePath());

	//TODO: change file name
	_ecgRuntime->CreateScene(getPackageName(), "ecgsave1.json");
	_ecgRuntime->Run();
}

const std::string& AndroidLauncherScene::getPackageName()
{
	_packageName = _packageNameField->getString();

	return _packageName;
}
