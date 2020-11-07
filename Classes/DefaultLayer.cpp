#include "DefaultLayer.h"
#include "Level.h"

DefaultLayer* DefaultLayer::createDefaultLayer()
{
	DefaultLayer* ret = new (std::nothrow) DefaultLayer();
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

bool DefaultLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->schedule(CC_SCHEDULE_SELECTOR(DefaultLayer::updateScene));

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(DefaultLayer::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(DefaultLayer::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void DefaultLayer::setInitialPositions()
{
	for (auto i = gameObjects.begin(); i < gameObjects.end(); i++)
	{
		auto gameobject = *i;

		if (gameobject->sprite != nullptr)
		{
			//TODO: enable the case where _level doesn't have to be set.
			assert(_level != nullptr);

			gameobject->sprite->setPosition(
				_level->positionForTileCoordinate(gameobject->size, gameobject->position));
		}
	}
}

void DefaultLayer::updateScene(float interval)
{
	for (auto gameObject = gameObjects.begin(); gameObject < gameObjects.end(); gameObject++)
	{
		(*gameObject)->onUpdate(_heldKeys);
	}
}


void DefaultLayer::addGameObject(GameObject* gameObject)
{
	gameObject->retain();
	this->gameObjects.push_back(gameObject);

	if (gameObject->sprite == nullptr)
	{
		this->addChild(gameObject);
	}
	else
	{
		this->addChild(gameObject->sprite);
	}

}

void DefaultLayer::LoadLevel(string filename)
{
	_level = new Level();
	_level->loadMap("level1.tmx");
	_level->retain();

	//TODO : Change 2.0F to SCALE_FACTOR
	_level->getMap()->setScale(2.0F);
	this->addChild(_level->getMap());
}

void DefaultLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (std::find(_heldKeys.begin(), _heldKeys.end(), keyCode) == _heldKeys.end()) {
		_heldKeys.push_back(keyCode);
	}
}

void DefaultLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	_heldKeys.erase(std::remove(_heldKeys.begin(), _heldKeys.end(), keyCode), _heldKeys.end());
}
