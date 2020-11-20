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

#include "GameScene.h"
#include "globals.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::create();

	auto layer = GameScene::create();

	scene->addChild(layer);

	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	_level = new Level();
	_level->loadMap("level1.tmx");
	_level->retain();

	auto director = Director::getInstance();
	_level->getMap()->setScale(SCALE_FACTOR);

	this->addChild(_level->getMap());

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("solbrain.plist");
	AnimationCache::getInstance()->addAnimationsWithFile("solbrain-animations.plist");

	player_sprite = Sprite::createWithSpriteFrameName("idle");
	player_sprite->setScale(SCALE_FACTOR);
	player_sprite->setFlippedX(true);

	Point point = Point(10, 2);
	Size size = player_sprite->getContentSize();

	player_sprite->setPosition(_level->positionForTileCoordinate(size, point));

	_player = new Player();
	_player->state = Player::State::Standing;
	_player->retain();
	this->setupAnimations();

	this->addChild(player_sprite);
	this->schedule(CC_SCHEDULE_SELECTOR(GameScene::updateScene));

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	_jumpAction = JumpBy::create(0.4f, Point(0, 0), 120, 1);
	_jumpAction->retain();

	return true;
}

void GameScene::setupAnimations() {

	AnimationCache* cache = AnimationCache::getInstance();
	Animation* animation = cache->getAnimation("walk");
	Animate* animate = Animate::create(animation);
	animate->getAnimation()->setRestoreOriginalFrame(true);
	animate->setDuration(0.80f);
	animate->setTarget(player_sprite);

	this->walkRight = animate;
	this->walkRight->retain();
}

void GameScene::movePlayerForTest(int x)
{
	_player->setPositionX(_player->getPositionX() + x);
	player_sprite->setPositionX(player_sprite->getPositionX() + x);
}

void GameScene::updateScene(float delta) {

	this->updatePlayer(delta);
}

static bool isJumping = false;

void GameScene::updatePlayer(float delta) {

	if (std::find(heldKeys.begin(), heldKeys.end(), EventKeyboard::KeyCode::KEY_SPACE) != heldKeys.end()) {

		if (_jumpAction->isDone())
		{
			//_jumpAction = JumpBy::create(0.4f, Point(0, 0), 120, 1);
			isJumping = false;
		}

		if (!isJumping)
		{
			player_sprite->runAction(_jumpAction);
			isJumping = true;
		}
	}

	if (std::find(heldKeys.begin(), heldKeys.end(), RIGHT_ARROW) != heldKeys.end()) {

		_player->velocity.x = PLAYER_MAX_VELOCITY;

		if (_player->grounded) {
			_player->state = Player::State::Walking;
		}

		_player->facingRight = true;
	}

	if (std::find(heldKeys.begin(), heldKeys.end(), LEFT_ARROW) != heldKeys.end()) {
		_player->velocity.x = -PLAYER_MAX_VELOCITY;
		if (_player->grounded) {
			_player->state = Player::State::Walking;
		}
		_player->facingRight = false;
	}
	// clamp the velocity to the maximum, x-axis only
	if (std::abs(_player->velocity.x) > PLAYER_MAX_VELOCITY) {
		_player->velocity.x = signum(_player->velocity.x) * PLAYER_MAX_VELOCITY;
	}
	// clamp the velocity to 0 if it's < 1, and set the state to standing
	if (std::abs(_player->velocity.x) < 1) {
		_player->velocity.x = 0;
		if (_player->grounded) {
			_player->state = Player::State::Standing;
		}
	}

	// unscale the velocity by the inverse delta time and set
	// the latest position
	_player->velocity = _player->velocity * delta;
	_player->position = _player->position + _player->velocity;
	_player->velocity = _player->velocity * 1 / delta;

	_player->velocity.x *= DAMPING;
	this->updatePlayerSprite(delta);
}

void GameScene::updatePlayerSprite(float delta) {

	if (_player->state == Player::State::Walking) {

		if (walkRight->isDone()) {
			walkRight->startWithTarget(player_sprite);
		}

		walkRight->step(delta);

		if (_player->facingRight) {
			player_sprite->setFlippedX(true);
		}
		else {
			player_sprite->setFlippedX(false);
		}

	}
	else if (_player->state == Player::State::Jumping) {

	}
	else {
		player_sprite->setSpriteFrame(Sprite::createWithSpriteFrameName("idle")->getSpriteFrame());
	}

	player_sprite->setPositionX(player_sprite->getPositionX() + _player->velocity.x);
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (std::find(heldKeys.begin(), heldKeys.end(), keyCode) == heldKeys.end()) {
		heldKeys.push_back(keyCode);
	}

	printf("pressed\n");
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(), keyCode), heldKeys.end());
}

int GameScene::signum(float x)
{
	if (x > 0.0L)
		return 1.0L;
	else if (x < 0.0L)
		return -1.0L;
	else
		return 0.0L;
}

void GameScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}
