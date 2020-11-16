#include <iostream>
#include <fstream>
#include <rapidjson/document.h>

#include "DefaultLayer.h"
#include "Level.h"

using namespace rapidjson;

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

DefaultLayer* DefaultLayer::CreateDefaultLayerFromJson(const char* filename)
{
	auto defaultLayer = DefaultLayer::CreateDefaultLayer();
	

	auto jsonContent = readJson(filename);
		
	Document document;
	document.Parse(jsonContent.c_str());

	assert(document.HasMember("DefaultLayer") && "There is no default layer!");

	const rapidjson::Value& layer = document["DefaultLayer"];

	const rapidjson::Value& gameobjects = layer["GameObjects"];



	auto player = GameObject::CreateFromJson("player.json");

	defaultLayer->LoadLevel("level1.tmx", 2.0F);
	defaultLayer->AddGameObject(std::move(player));

	//TODO : Consider how to skip this verbose step.
	defaultLayer->SetInitialPositions();

	return defaultLayer;
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

string DefaultLayer::readJson(const char* filename)
{
	ifstream jsonFile;
	jsonFile.open(filename);

	assert(jsonFile.is_open() && "Cannot open json file");

	string jsonContent;

	jsonFile.seekg(0, std::ios::end);
	const int size = jsonFile.tellg();
	jsonContent.resize(size);
	jsonFile.seekg(0, std::ios::beg);
	jsonFile.read(&jsonContent[0], size);

	return jsonContent;
}
