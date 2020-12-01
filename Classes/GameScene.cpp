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

#define CAMERA_SPRITE_OFFSET_X 100

void GameScene::AddButtonLayer(Scene* scene, GameScene* gameLayer)
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
		GameScene::ButtonEventHandler(gameLayer, EventKeyboard::KeyCode::KEY_RIGHT_ARROW, type);
		}
	);

	auto leftArrowButton = ui::Button::create("rightArrowButton.png");
	leftArrowButton->setFlippedX(true);
	leftArrowButton->setOpacity(opacity);
	leftArrowButton->setScale(arrowButtonScale);
	leftArrowButton->setPosition(Vec2(buttonXOffset, buttonYPos));
	leftArrowButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
		GameScene::ButtonEventHandler(gameLayer, EventKeyboard::KeyCode::KEY_LEFT_ARROW, type);
		}
	);

	auto spaceButton = ui::Button::create("spacebarButton.png");
	spaceButton->setOpacity(opacity);
	spaceButton->setScale(0.5f);
	spaceButton->setScaleX(1.4f);
	spaceButton->setPosition(Vec2(screenSize.width / 2, buttonYPos));
	spaceButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
		GameScene::ButtonEventHandler(gameLayer, EventKeyboard::KeyCode::KEY_SPACE, type);
		}
	);

	buttonLayer->addChild(leftArrowButton);
	buttonLayer->addChild(rightArrowButton);
	buttonLayer->addChild(spaceButton);
	scene->addChild(buttonLayer, 5);
}

void GameScene::ButtonEventHandler(GameScene* gameScene, EventKeyboard::KeyCode keyCode, ui::Widget::TouchEventType touchEventType)
{
	switch (touchEventType) {
	case ui::Widget::TouchEventType::BEGAN:
		gameScene->onKeyPressed(keyCode, nullptr);
		break;
	case ui::Widget::TouchEventType::ENDED:
		gameScene->onKeyReleased(keyCode, nullptr);
		break;
	case ui::Widget::TouchEventType::CANCELED:
		gameScene->onKeyReleased(keyCode, nullptr);
		break;

	default:
		break;
	}
}



Scene* GameScene::createScene() {
	auto scene = Scene::create();

	auto layer = GameScene::create();
	scene->addChild(layer);

#ifdef BUILD_ANDROID
	AddButtonLayer(scene, layer);
#endif // BUILD_ANDROID


	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename) {
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init() {
	//////////////////////////////
	// 1. super init first
	if (!Layer::init()) {
		return false;
	}

	level = new Level();
	level->loadMap("level1.tmx");
	level->retain();

	auto director = Director::getInstance();
	level->getMap()->setScale(SCALE_FACTOR);

	this->addChild(level->getMap());

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("solbrain.plist");
	AnimationCache::getInstance()->addAnimationsWithFile("solbrain-animations.plist");

	player_sprite = Sprite::createWithSpriteFrameName("idle");
	player_sprite->setScale(SCALE_FACTOR);
	player_sprite->setFlippedX(true);

	Point point = Point(10, 2);
	Size size = player_sprite->getContentSize();

	player_sprite->setPosition(level->tileCoordinateToPosition(size, point));

	player = new Player();
	player->state = Player::State::Standing;
	player->retain();

	Point origin = Director::getInstance()->getVisibleOrigin();
	Size wsize = Director::getInstance()->getVisibleSize();  //default screen size (or design resolution size, if you are using design resolution)
	Point* center = new Point(wsize.width / 2 + origin.x, wsize.height / 2 + origin.y);

	cameraTarget = Sprite::create();
	cameraTarget->setPositionX(
		player_sprite->getPosition().x + CAMERA_SPRITE_OFFSET_X); // set to players x
	cameraTarget->setPositionY(wsize.height / 2 + origin.y); // center of height
	cameraTarget->retain();

	camera = Follow::create(cameraTarget, Rect::ZERO);
	camera->retain();

	this->runAction(camera);

	this->setupAnimations();
	this->addChild(player_sprite);
	this->schedule(CC_SCHEDULE_SELECTOR(GameScene::updateScene));
	this->addChild(cameraTarget);

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

void GameScene::movePlayerForTest(int x) {
	player->setPositionX(player->getPositionX() + x);
	player_sprite->setPositionX(player_sprite->getPositionX() + x);
}

void GameScene::updateScene(float delta) {
	this->cameraTarget->setPositionX(player_sprite->getPosition().x + CAMERA_SPRITE_OFFSET_X);
	this->updatePlayer(delta);
}

static bool isJumping = false;

void GameScene::updatePlayer(float delta) {

	//Jump
	if (std::find(heldKeys.begin(), heldKeys.end(), EventKeyboard::KeyCode::KEY_SPACE) !=
		heldKeys.end()) {

		if (_jumpAction->isDone() || !isJumping) {
			player_sprite->runAction(_jumpAction);
			isJumping = true;
		}
	}

	if (std::find(heldKeys.begin(), heldKeys.end(), RIGHT_ARROW) != heldKeys.end()) {

		player->velocity.x = PLAYER_MAX_VELOCITY;

		if (player->grounded) {
			player->state = Player::State::Walking;
		}

		player->facingRight = true;
	}

	if (std::find(heldKeys.begin(), heldKeys.end(), LEFT_ARROW) != heldKeys.end()) {
		player->velocity.x = -PLAYER_MAX_VELOCITY;
		if (player->grounded) {
			player->state = Player::State::Walking;
		}
		player->facingRight = false;
	}

	// clamp the velocity to the maximum, x-axis only
	if (std::abs(player->velocity.x) > PLAYER_MAX_VELOCITY) {
		player->velocity.x = signum(player->velocity.x) * PLAYER_MAX_VELOCITY;
	}
	// clamp the velocity to 0 if it's < 1, and set the state to standing
	if (std::abs(player->velocity.x) < 1) {
		player->velocity.x = 0;
		if (player->grounded) {
			player->state = Player::State::Standing;
		}
	}

	//Rect player_rect = player_sprite->getTextureRect();
	//Point tmp = level->positionToTileCoordinate(Point(player->position.x + player->velocity.x, player->position.y));



	// unscale the velocity by the inverse delta time and set
	// the latest position
	player->velocity = player->velocity * delta;
	player->position = player->position + player->velocity;
	player->velocity = player->velocity * 1 / delta;

	player->velocity.x *= DAMPING;
	this->updatePlayerSprite(delta);
}

void GameScene::updatePlayerSprite(float delta) {

	if (player->state == Player::State::Walking) {

		if (walkRight->isDone()) {
			walkRight->startWithTarget(player_sprite);
		}

		walkRight->step(delta);

		if (player->facingRight) {
			player_sprite->setFlippedX(true);
		}
		else {
			player_sprite->setFlippedX(false);
		}

	}
	else if (player->state == Player::State::Jumping) {

	}
	else {
		player_sprite->setSpriteFrame(Sprite::createWithSpriteFrameName("idle")->getSpriteFrame());
	}

	player_sprite->setPositionX(player_sprite->getPositionX() + player->velocity.x);
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	if (std::find(heldKeys.begin(), heldKeys.end(), keyCode) == heldKeys.end()) {
		heldKeys.push_back(keyCode);
	}

	printf("pressed\n");
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(), keyCode), heldKeys.end());
}

int GameScene::signum(float x) {
	if (x > 0.0L)
		return 1.0L;
	else if (x < 0.0L)
		return -1.0L;
	else
		return 0.0L;
}

void GameScene::menuCloseCallback(Ref* pSender) {
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}
