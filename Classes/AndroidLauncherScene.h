#pragma once
#include <memory>
#include <string>

#include "ui/CocosGUI.h"
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
    void downloadAndUnzipPackage(const std::string& packageName);
    void runPackage();
    void onHttpRequestCompleted(HttpClient* sender, HttpResponse* response);
    const std::string& getPackageName();


private:
    const std::string PACKAGE_SERVER_URL = "https://ecgenginestorage.blob.core.windows.net/packagecontainer";
    
    std::unique_ptr<Runtime> _ecgRuntime;    
    std::string _packageName = "";
    
    cocos2d::Label* _infoLabel;
    cocos2d::ui::TextField* _packageNameField;
    
    bool _unziping = false;
    bool _downloadRunning = false;
};

