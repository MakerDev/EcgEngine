#include <iostream>

#ifdef _WIN32
#include <direct.h>
#endif

#include "AppDelegate.h"
#include "Runtime.h"
#include "HelloWorldScene.h"
#include "GameScene.h"
#include "Level.h"
#include "GameObject.h"
#include "DefaultLayer.h"
#include "EngineManager.h"

using namespace cocos2d;

//TODO : 오직 parent를 세팅하는 용도로만 사용하도록 변경
void Runtime::initialize(int parent)
{
#ifdef _WIN32
    cocos2d::GLViewImpl::SetParent((HWND)parent);
	char strBuffer[_MAX_PATH] = { 0, };
	char* pstrBuffer = NULL;

	pstrBuffer = getcwd(strBuffer, _MAX_PATH);
#endif

	AppDelegate app;
	cocos2d::Application::getInstance()->run();
}

void Runtime::switchScene()
{
	const auto director = Director::getInstance();

	Scene* newScene = nullptr;

	if (_currentScene++ % 2 == 0)
	{
		newScene = HelloWorld::createScene();
	}
	else
	{
		newScene = GameScene::createScene();
	}

	director->replaceScene(newScene);
}

void Runtime::destroy()
{
	auto director = Director::getInstance();
	director->end();
}

void Runtime::CreateScene()
{
	CreateScene("ecgsave1.json");
}

void Runtime::CreateScene(const std::string& filename)
{
	//TODO : Enable to make custom sized Scene;
	Scene* newScene = Scene::createWithSize(Size(320, 320));

	assert(newScene != nullptr && "Failed to create new scene");

	auto gameObjectsLayer = DefaultLayer::CreateDefaultLayerFromJson(filename.c_str());

#ifndef _WIN32
	gameObjectsLayer->AddButtonLayer(newScene, gameObjectsLayer);
#endif // !_WIN32


	newScene->addChild(gameObjectsLayer);

	auto director = Director::getInstance();
	director->replaceScene(newScene);

	director->stopAnimation();
	_isAnimationStopped = true;
}

void Runtime::CreateScene(const std::string& packagename, const std::string& jsonFileName)
{

}

void Runtime::Run()
{
	auto director = Director::getInstance();

	if (_isAnimationStopped)
	{
		director->startAnimation();
		_isAnimationStopped = false;
	}
}


