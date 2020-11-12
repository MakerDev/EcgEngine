#include <rapidjson/document.h>

#include "AppDelegate.h"
#include "Runtime.h"
#include "HelloWorldScene.h"
#include "GameScene.h"
#include "Level.h"

#include "GameObject.h"
#include "DefaultLayer.h"

using namespace cocos2d;

//TODO : 오직 parent를 세팅하는 용도로만 사용하도록 변경
void Runtime::initialize(int parent)
{
	cocos2d::GLViewImpl::SetParent((HWND)parent);

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
	this->CreateScene(2.0F);
}

void Runtime::CreateScene(int speed)
{
	//TODO : Enable to make custom sized Scene;
	Scene* newScene = Scene::createWithSize(Size(640, 640));

	assert(newScene != nullptr && "Failed to create new scene");

	auto player = GameObject::CreateFromJson("player.json", speed);

	//TODO : Make proper error
	assert(player != nullptr && "Failed to create gameobject from player.json");

	//Add level background
	auto gameObjectsLayer = DefaultLayer::CreateDefaultLayer();

	assert(gameObjectsLayer != nullptr && "Failed to create default layer");

	gameObjectsLayer->LoadLevel("level1.tmx", 2.0F);
	gameObjectsLayer->AddGameObject(std::move(player));

	//TODO : Consider how to skip this verbose step.
	gameObjectsLayer->SetInitialPositions();

	newScene->addChild(gameObjectsLayer);

	auto director = Director::getInstance();
	director->replaceScene(newScene);
}


