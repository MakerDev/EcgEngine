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

#define SCALE_FACTOR 2.0

GameObject* parseGameObject(std::string filename)
{
	GameObject* player = new GameObject();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("solbrain.plist");
	AnimationCache::getInstance()->addAnimationsWithFile("solbrain-animations.plist");

	//TODO: Encapsulate them
	player->sprite = Sprite::createWithSpriteFrameName("idle");
	player->sprite->setScale(SCALE_FACTOR);
	player->sprite->setFlippedX(true);

	player->position = Point(10, 2);
	player->size = player->sprite->getContentSize();

	return player;
}

void Runtime::createScene()
{
	//TODO : Enable to make custom sized Scene;
	Scene* newScene = Scene::createWithSize(Size(640, 640));

	auto player = parseGameObject("player.json");

	if (player == nullptr)
	{
		//TODO : Make proper error
		assert(false && "Failed to create gameobject from player.json");
	}

	//Add level background
	auto gameObjectsLayer = DefaultLayer::createDefaultLayer();
	gameObjectsLayer->LoadLevel("level1.tmx");
	gameObjectsLayer->addGameObject(player);

	//TODO : Consider how to skip this verbose step.
	gameObjectsLayer->setInitialPositions();

	newScene->addChild(gameObjectsLayer);

	auto director = Director::getInstance();

	director->replaceScene(newScene);
}


