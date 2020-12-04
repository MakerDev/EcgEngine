#pragma once
#include <memory>

#include "cocos2d.h"
#include "network/CCDownloader.h"
#include "Runtime.h"

class AndroidLauncherScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(AndroidLauncherScene);


private:
    std::unique_ptr<Runtime> _ecgRuntime;
    void DownloadPackage(const std::string& packageName);
    void RunPackage(const std::string& packageName);
    bool UnzipPackage(const std::string& packageName);

private:
    const std::string PACKAGE_SERVER_URL = "https://ecgenginestorage.blob.core.windows.net/packagecontainer";

    bool _downloadRunning;

    cocos2d::network::Downloader* _downloader;
    std::shared_ptr<const cocos2d::network::DownloadTask> _task;

};

