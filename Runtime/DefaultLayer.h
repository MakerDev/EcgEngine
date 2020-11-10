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

	bool init() override;
	void SetInitialPositions();

	//To trigger and execute proper callbacks
	void UpdateScene(float interval);

	void AddGameObject(shared_ptr<GameObject> gameObject);
	//TODO: consider changing name to LoadTmxMap
	void LoadLevel(string filename, float scaleFactor);
	const vector<shared_ptr<GameObject>>& GetGameObjects() const;

protected:
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) override;
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) override;

	shared_ptr<Level> _level;
	vector<shared_ptr<GameObject>> _gameObjects;
	vector<EventKeyboard::KeyCode> _heldKeys;
};

