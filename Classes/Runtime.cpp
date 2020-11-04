#include "AppDelegate.h"
#include "Runtime.h"
#include "HelloWorldScene.h"
#include "GameScene.h"

using namespace cocos2d;

void Runtime::Initilaize(int parent)
{
	cocos2d::GLViewImpl::SetParent((HWND)parent);

	AppDelegate app;

	cocos2d::Application::getInstance()->run();
}

void Runtime::SwitchScene()
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

void Runtime::Destroy()
{
	auto director = Director::getInstance();
	director->end();
}
