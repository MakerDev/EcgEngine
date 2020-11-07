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
    static DefaultLayer* createDefaultLayer();

    virtual bool init() override;
    void setInitialPositions();


    //To trigger and execute proper callbacks
    vector<GameObject*> gameObjects;
    void updateScene(float interval);

    void addGameObject(GameObject* gameObject);
    //TODO: consider changing name to LoadTmxMap
    void LoadLevel(string filename);

protected:
    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) override;
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) override;

    Level* _level;
    vector<EventKeyboard::KeyCode> _heldKeys;
};

