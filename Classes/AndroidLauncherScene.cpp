#include "AndroidLauncherScene.h"
#include "ui/CocosGUI.h"
#include "FileHelper.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace std;

Scene* AndroidLauncherScene::createScene() {
	auto scene = Scene::create();

	auto layer = AndroidLauncherScene::create();
	scene->addChild(layer);

	return scene;
}

bool AndroidLauncherScene::init() {
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
	this->addChild(debugLabel);

	auto fetchButton = Button::create("HelloWorld.png");
	fetchButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
		auto packageName = textField->getString();
		debugLabel->setString(packageName);
		DownloadPackage("ecgtest");
		});
	fetchButton->setPosition(Vec2(viewSize.width / 2, 100));

	this->addChild(fetchButton);

	return true;
}

void AndroidLauncherScene::DownloadPackage(const std::string& packageName) {
	const std::string fileName = packageName + ".zip";
	const std::string packageUrl = PACKAGE_SERVER_URL + "/" + fileName;
	std::string filePath = FileUtils::getInstance()->getWritablePath() + fileName;

	_downloader = new (std::nothrow)
		network::Downloader();

	_downloader->onTaskProgress = ([](const network::DownloadTask& task, int64_t bytesReceived,
		int64_t totalBytesReceived, int64_t totalBytesExpected) {
			CCLOG("download progress %.0f%%", (float)totalBytesReceived * 100.0 / totalBytesExpected);
		});

	_downloader->onFileTaskSuccess = ([this, &packageName](const network::DownloadTask& task) {
		CCLOG("downloaded success");

		delete _downloader;
		_downloader = nullptr;
		_task = nullptr;
		_downloadRunning = false;
		RunPackage(packageName);
		});

	_downloader->onTaskError = ([](const network::DownloadTask& task, int errorCode,
		int errorCodeInternal, const std::string& errorStr) {
			CCLOG("downloading error %s", errorStr.c_str());
		});

	//TODO : Check if file exists before downloading
	_task = _downloader->createDownloadFileTask(packageUrl, filePath);

	_downloadRunning = true;

	CCLOG("download started");
}

void AndroidLauncherScene::RunPackage(const std::string& packageName) {
	UnzipPackage(packageName);

	//TODO: change file name
	_ecgRuntime->CreateScene(FileHelper::CombinePath(packageName, "ecgsave1.json"));
	_ecgRuntime->Run();
}

bool AndroidLauncherScene::UnzipPackage(const std::string& packageName) {
	auto zipfile = cocos2d::ZipFile(packageName);

	auto contentFileName = zipfile.getFirstFilename();
	std::string filename = contentFileName;

	std::string directoryName =
		cocos2d::FileUtils::getInstance()->getWritablePath() + packageName + "/";

	if (!cocos2d::FileUtils::getInstance()->isDirectoryExist(directoryName)) {
		cocos2d::FileUtils::getInstance()->createDirectory(directoryName);
	}

	ssize_t dataSize = 0;
	unsigned char* data = zipfile.getFileData(contentFileName, &dataSize);

	while (data != nullptr) {
		std::string fullFileName = directoryName + filename;

		FILE* fp = fopen(fullFileName.c_str(), "wb");

		if (fp) {
			fwrite(data, 1, dataSize, fp);
			fclose(fp);
		}

		free(data);

		contentFileName = zipfile.getNextFilename();
		filename = contentFileName;

		data = zipfile.getFileData(contentFileName, &dataSize);
	}

	return true;
}




