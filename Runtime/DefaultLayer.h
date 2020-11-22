#pragma once
#include <algorithm>
#include <vector>
#include <string>

#include "cocos2d.h"
#include "Level.h"
#include "GameObject.h"

using namespace std;
using namespace cocos2d;


class DefaultLayer : public cocos2d::Layer
{
public:
	static DefaultLayer* CreateDefaultLayer();
	static DefaultLayer* CreateDefaultLayerFromJson(const char* filename);

	bool init() override;
	void SetInitialPositions();

	//To trigger and execute proper callbacks
	void UpdateScene(float interval);

	void AddGameObject(unique_ptr<GameObject> gameObject);
	//TODO: consider changing name to LoadTmxMap
	void LoadTileMap(string filename, float scaleFactor);
	const vector<unique_ptr<GameObject>>& GetGameObjects() const noexcept;

protected:
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) override;
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) override;

	unique_ptr<Level> _level;
	vector<unique_ptr<GameObject>> _gameObjects;
	vector<EventKeyboard::KeyCode> _heldKeys;
	vector<EventKeyboard::KeyCode> _releasedKeys;

private:
	static string readJson(const char* filename);
};

