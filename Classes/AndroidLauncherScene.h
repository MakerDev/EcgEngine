#pragma once
#include <memory>
#include <string>
#include "cocos2d.h"
#include "network/CCDownloader.h"
#include "Runtime.h"
#include "network/HttpRequest.h"
#include "network/HttpResponse.h"
#include "network/HttpClient.h"

using namespace cocos2d::network;

class AndroidLauncherScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(AndroidLauncherScene);


private:
    std::unique_ptr<Runtime> _ecgRuntime;
    void DownloadAndUnzipPackage(const std::string& packageName);
    void RunPackage(const std::string& packageName);
    void onHttpRequestCompleted(HttpClient* sender, HttpResponse* response);
    bool UnzipPackage(const std::string& packageName);

private:
    const std::string PACKAGE_SERVER_URL = "https://ecgenginestorage.blob.core.windows.net/packagecontainer";
    cocos2d::Label* _infoLabel;
    bool _unziping = false;
    bool _downloadRunning = false;
    std::string _packageName;
};

