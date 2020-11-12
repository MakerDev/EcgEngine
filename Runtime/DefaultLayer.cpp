#include "DefaultLayer.h"
#include "Level.h"

DefaultLayer* DefaultLayer::CreateDefaultLayer()
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

	this->schedule(CC_SCHEDULE_SELECTOR(DefaultLayer::UpdateScene));

	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(DefaultLayer::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(DefaultLayer::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void DefaultLayer::SetInitialPositions()
{
	for (auto i = _gameObjects.begin(); i != _gameObjects.end(); i++)
	{
		GameObject& gameobject = *(i->get());

		if (gameobject.sprite != nullptr)
		{
			//TODO: enable the case where _level doesn't have to be set.
			assert(_level != nullptr);

			//TODO Choose whether to use World Position or just to use TileCoordination Position.
			gameobject.sprite->setPosition(
				_level->positionForTileCoordinate(gameobject.size, gameobject.position));
		}
	}
}

void DefaultLayer::UpdateScene(float timeDelta)
{
	for (auto gameObject = _gameObjects.begin(); gameObject < _gameObjects.end(); gameObject++)
	{
		(*gameObject)->onUpdate(timeDelta, _heldKeys);
	}
}

void DefaultLayer::AddGameObject(unique_ptr<GameObject> gameObject)
{
	if (gameObject->sprite == nullptr)
	{
		this->addChild(gameObject.get());
	}
	else
	{
		this->addChild(gameObject->sprite);
	}

	gameObject->retain();

	this->_gameObjects.push_back(std::move(gameObject));
}

void DefaultLayer::LoadLevel(string filename, float scaleFactor)
{
	_level = make_unique<Level>();
	_level->loadMap("level1.tmx");
	_level->retain();

	_level->getMap()->setScale(scaleFactor);

	this->addChild(_level->getMap());
}
const vector<unique_ptr<GameObject>>& DefaultLayer::GetGameObjects() const
{
	return _gameObjects;
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
