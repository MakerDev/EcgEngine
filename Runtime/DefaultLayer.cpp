#include <iostream>
#include <fstream>
#include <rapidjson/document.h>

#include "DefaultLayer.h"
#include "Level.h"
#include "FileHelper.h"
#include "JsonHelper.h"
#include "EngineManager.h" 

using namespace rapidjson;

DefaultLayer* DefaultLayer::CreateDefaultLayer()
{
	DefaultLayer* ret = new (std::nothrow) DefaultLayer();

	EngineManager::GetInstance()->SetDefaultLayer(shared_ptr<DefaultLayer>(ret));

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

DefaultLayer* DefaultLayer::CreateDefaultLayerFromJson(const string& filename)
{
	auto defaultLayer = DefaultLayer::CreateDefaultLayer();

	assert(defaultLayer != nullptr && "Failed to create DefaultLayer");

	auto jsonContent = readJson(filename);

	Document document;
	document.Parse(jsonContent.c_str());

	assert(document.HasMember("DefaultLayer") && "There is no default layer!");

	const rapidjson::Value& layer = document["DefaultLayer"];
	const rapidjson::Value& gameobjects = document["GameObjects"];

	//auto gameObjects

	for (auto& gameObjectJsonValue : JsonHelper::GetConstArray(gameobjects))
	{
		auto gameObject = GameObject::CreateFromJsonValue(gameObjectJsonValue);
		defaultLayer->AddGameObject(std::move(gameObject));
	}

	//TODO : clean up this process
	for (auto& gameObject : defaultLayer->GetGameObjects())
	{
		gameObject->RegisterAllActions();
	}

	//TODO : enable to manually set this scale factor 
	defaultLayer->LoadTileMap(FileHelper::GetPackageRelativePath("level1.tmx"), defaultLayer->GetScaleFactor());
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

		if (gameobject.GetSprite() != nullptr)
		{
			//TODO: enable the case where _level doesn't have to be set.
			assert(_level != nullptr);

			//TODO Choose whether to use World Position or just to use TileCoordination Position.
			gameobject.GetSprite()->setPosition(
				_level->tileCoordinateToPosition(gameobject.GetSprite()->getContentSize(), gameobject.position));
		}
	}
}

void DefaultLayer::UpdateScene(float timeDelta)
{
	for (auto gameObject = _gameObjects.begin(); gameObject < _gameObjects.end(); gameObject++)
	{
		(*gameObject)->OnUpdate(timeDelta, _heldKeys, _releasedKeys);
		_releasedKeys.clear();
	}
}

void DefaultLayer::AddGameObject(unique_ptr<GameObject> gameObject)
{
	if (gameObject->GetSprite() == nullptr)
	{
		this->addChild(gameObject.get());
	}
	else
	{
		this->addChild(gameObject->GetSprite());
	}

	gameObject->retain();

	this->_gameObjects.push_back(std::move(gameObject));
}

void DefaultLayer::LoadTileMap(string packageRelativeFilePath, float scaleFactor)
{
	_level = make_unique<Level>();
	_level->loadMap(packageRelativeFilePath.c_str());
	_level->retain();

	_level->getMap()->setScale(scaleFactor);

	this->addChild(_level->getMap());
}

const vector<unique_ptr<GameObject>>& DefaultLayer::GetGameObjects() const noexcept
{
	return _gameObjects;
}

GameObject* DefaultLayer::FindGameObject(const std::string& name)
{
	for (auto gameObject = _gameObjects.begin(); gameObject < _gameObjects.end(); gameObject++)
	{
		if ((*gameObject)->GetObjectName().compare(name) == 0)
		{
			return gameObject->get();
		}

	}

	return nullptr;
}

float DefaultLayer::GetScaleFactor() const
{
	return _scaleFactor;
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
	_releasedKeys.push_back(keyCode);
}

//TODO : Consider move this to another place
string DefaultLayer::readJson(const string& filename)
{
	string jsonContent;

#ifdef _WIN32
	ifstream jsonFile;
	jsonFile.open(filename);

	assert(jsonFile.is_open() && "Cannot open json file");

	jsonFile.seekg(0, std::ios::end);
	const int size = jsonFile.tellg();
	jsonContent.resize(size);
	jsonFile.seekg(0, std::ios::beg);
	jsonFile.read(&jsonContent.at(0), size);
#else
	string fullPath = FileUtils::getInstance()->fullPathForFilename(FileHelper::GetPackageRelativePath(filename));
	jsonContent = FileUtils::getInstance()->getStringFromFile(fullPath);
#endif // _WIN32

	return jsonContent;
}


//For Android
void DefaultLayer::AddButtonLayer(Scene* scene, DefaultLayer* layer)
{
	auto buttonLayer = Layer::create();

	const auto screenSize = Director::getInstance()->getVisibleSize();

	constexpr int buttonXOffset = 100;
	constexpr int buttonYPos = 50;
	constexpr int opacity = 200;
	constexpr float arrowButtonScale = 0.4F;

	auto rightArrowButton = ui::Button::create("rightArrowButton.png");
	rightArrowButton->setOpacity(opacity);
	rightArrowButton->setScale(arrowButtonScale);
	rightArrowButton->setPosition(Vec2(screenSize.width - buttonXOffset, buttonYPos));
	rightArrowButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
		DefaultLayer::ButtonEventHandler(layer, EventKeyboard::KeyCode::KEY_RIGHT_ARROW, type);
		}
	);

	auto leftArrowButton = ui::Button::create("rightArrowButton.png");
	leftArrowButton->setFlippedX(true);
	leftArrowButton->setOpacity(opacity);
	leftArrowButton->setScale(arrowButtonScale);
	leftArrowButton->setPosition(Vec2(buttonXOffset, buttonYPos));
	leftArrowButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
		DefaultLayer::ButtonEventHandler(layer, EventKeyboard::KeyCode::KEY_LEFT_ARROW, type);
		}
	);

	auto spaceButton = ui::Button::create("spacebarButton.png");
	spaceButton->setOpacity(opacity);
	spaceButton->setScale(0.5f);
	spaceButton->setScaleX(1.4f);
	spaceButton->setPosition(Vec2(screenSize.width / 2, buttonYPos));
	spaceButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
		DefaultLayer::ButtonEventHandler(layer, EventKeyboard::KeyCode::KEY_SPACE, type);
		}
	);

	buttonLayer->addChild(leftArrowButton);
	buttonLayer->addChild(rightArrowButton);
	buttonLayer->addChild(spaceButton);
	scene->addChild(buttonLayer, 5);
}

void DefaultLayer::ButtonEventHandler(DefaultLayer* layer, EventKeyboard::KeyCode keyCode, ui::Widget::TouchEventType touchEventType)
{
	switch (touchEventType) {
	case ui::Widget::TouchEventType::BEGAN:
		layer->onKeyPressed(keyCode, nullptr);
		break;
	case ui::Widget::TouchEventType::ENDED:
		layer->onKeyReleased(keyCode, nullptr);
		break;
	case ui::Widget::TouchEventType::CANCELED:
		layer->onKeyReleased(keyCode, nullptr);
		break;

	default:
		break;
	}
}
