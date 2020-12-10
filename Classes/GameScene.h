/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include <algorithm>
#include <vector>
#include <string>

#include "cocos2d.h"
#include "Level.h"
#include "Player.h"
#include "ui/CocosGUI.h"

using namespace std;

class GameScene : public cocos2d::Layer
{
public:
    static void AddButtonLayer(Scene* layer, GameScene* gameLayer);

public:
    Level* level;
    Player* player;
    Sprite* cameraTarget;

    boolean collidesX;

    Animate* walkRight;
    Animate* jumping;
    Animate* falling;
    Follow* camera;

    DrawNode* rectWithBorder;

    vector<EventKeyboard::KeyCode> heldKeys;

    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

    void updateScene(float interval);

    void updatePlayer(float interval);

    int signum(float x);

    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    Action* _jumpAction;
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

    GameScene(void);
    virtual ~GameScene(void);

private:
    static void ButtonEventHandler(GameScene* gameScene, EventKeyboard::KeyCode keyCode, ui::Widget::TouchEventType touchEventType);
};

#endif // __HELLOWORLD_SCENE_H__
