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

#ifndef _WIN32
#include "CCFileUtils-android.h"
#endif

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

#ifndef _WIN32
	AddButtonLayer(scene, layer);
#endif // _WIN32


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

	player = Player::create();
	player->retain();
	player->setScale(SCALE_FACTOR);

	Point point = Point(10, 2);

	player->setPosition(level->tileCoordinateToPosition(point));

	Point origin = Director::getInstance()->getVisibleOrigin();
	Size wsize = Director::getInstance()->getVisibleSize();  //default screen size (or design resolution size, if you are using design resolution)
	Point* center = new Point(wsize.width / 2 + origin.x, wsize.height / 2 + origin.y);

	cameraTarget = Sprite::create();
	cameraTarget->setPositionX(player->getPositionX()); // set to players x
	cameraTarget->setPositionY(wsize.height / 2 + origin.y); // center of height

	cameraTarget->retain();

	loadEnemies();

	this->addChild(player);
	this->schedule(schedule_selector(GameScene::updateScene));

	this->addChild(cameraTarget);
	rectWithBorder = DrawNode::create();
	Vec2 vertices[] =
	{
		Vec2(0, player->player_size.height),
		Vec2(player->player_size.width, player->player_size.height),
		Vec2(player->player_size.width, 0),
		Vec2(0,0)
	};

	rectWithBorder->drawPolygon(vertices, 4, Color4F(0.0f, 0.3f, 0.3f, 1), 0, Color4F(0.0f, 0.2f, 0.0f, 1));

	addChild(rectWithBorder);

	camera = Follow::create(cameraTarget, Rect::ZERO);
	camera->retain();

	this->runAction(camera);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("solbrain.plist");
	AnimationCache::getInstance()->addAnimationsWithFile("solbrain-animations.plist");	

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	_jumpAction = JumpBy::create(0.4f, Point(0, 0), 120, 1);
	_jumpAction->retain();

	return true;
}

void GameScene::loadEnemies() {

	Sprite* enemy1 = Sprite::create("94.png");
	enemy1->setPosition(level->tileCoordinateToPosition(Point(33, 2)));
	enemy1->setAnchorPoint(Point::ZERO);
	enemy1->setScale(ENEMY_SCALE_FACTOR);
	enemy1->setFlippedX(true);
	enemy1->retain();

	enemyList.push_back(enemy1);
	this->addChild(enemy1);

	Sprite* enemy2 = Sprite::create("94.png");
	enemy2->setPosition(level->tileCoordinateToPosition(Point(44, 2)));
	enemy2->setAnchorPoint(Point::ZERO);
	enemy2->setScale(ENEMY_SCALE_FACTOR);
	enemy2->setFlippedX(true);
	enemy2->retain();

	enemyList.push_back(enemy2);
	this->addChild(enemy2);


	Sprite* enemy3 = Sprite::create("94.png");
	enemy3->setPosition(level->tileCoordinateToPosition(Point(55, 2)));
	enemy3->setAnchorPoint(Point::ZERO);
	enemy3->setScale(ENEMY_SCALE_FACTOR);
	enemy3->setFlippedX(true);
	enemy3->retain();

	enemyList.push_back(enemy3);
	this->addChild(enemy3);

	Sprite* enemy4 = Sprite::create("94.png");
	enemy4->setPosition(level->tileCoordinateToPosition(Point(100, 2)));
	enemy4->setAnchorPoint(Point::ZERO);
	enemy4->setScale(ENEMY_SCALE_FACTOR);
	enemy4->setFlippedX(true);
	enemy4->retain();

	enemyList.push_back(enemy4);
	this->addChild(enemy4);

	Sprite* enemy5 = Sprite::create("94.png");
	enemy5->setPosition(level->tileCoordinateToPosition(Point(100, 6)));
	enemy5->setAnchorPoint(Point::ZERO);
	enemy5->setScale(ENEMY_SCALE_FACTOR);
	enemy5->setFlippedX(true);
	enemy5->retain();

	enemyList.push_back(enemy5);
	this->addChild(enemy5);

}

void GameScene::updateScene(float delta) {

	cameraTarget->setPositionX(player->getPositionX());

	this->updatePlayer(delta);

}

static bool isJumping = false;

void GameScene::updatePlayer(float delta) {

	//Jump
	if (std::find(heldKeys.begin(), heldKeys.end(), EventKeyboard::KeyCode::KEY_SPACE) !=
		heldKeys.end()) {

		if (player->grounded && player->velocity_y <= 0) {

			player->velocity_y = PLAYER_JUMP_VELOCITY;
			player->jumping = true;
			player->grounded = false;
		}
	}

	if (std::find(heldKeys.begin(), heldKeys.end(), RIGHT_ARROW) != heldKeys.end()) {

		player->velocity_x = PLAYER_MAX_VELOCITY;

		player->facing_right = true;
	}

	if (std::find(heldKeys.begin(), heldKeys.end(), LEFT_ARROW) != heldKeys.end()) {
		player->velocity_x = -PLAYER_MAX_VELOCITY;
		player->facing_right = false;
	}

	player->velocity_y -= GRAVITY;

	Rect player_rect = player->getBoundingBox();

	Point tmp;
	vector<Rect> tiles;
	tiles.clear();

	tmp = level->positionToTileCoordinate(Point(player->getPositionX() + player->player_size.width * 0.5f,
		player->getPositionY() + player->player_size.height * 0.5f));

	if (player->velocity_x > 0) {
		tiles = level->getCollisionTilesX(tmp, 1);
	}
	else {
		tiles = level->getCollisionTilesX(tmp, -1);
	}

	player_rect.setRect(
		player->getBoundingBox().getMinX() + player->velocity_x,
		player->getBoundingBox().getMinY() + 1.0f, // dont let the rectangle touch the ground otherwise, will count as collision
		player->player_size.width,
		player->player_size.height
	);

	for (Rect tile : tiles) {
		if (player_rect.intersectsRect(tile)) {
			player->velocity_x = 0;
			break;
		}
	}

	tiles.clear();

	if (player->velocity_y > 0) {
		tiles = level->getCollisionTilesY(tmp, 1);
	}
	else if (player->velocity_y < 0) {
		tiles = level->getCollisionTilesY(tmp, -1);
	}

	player_rect.setRect(
		player->getBoundingBox().getMinX(),
		player->getBoundingBox().getMinY(),
		player->player_size.width,
		player->player_size.height + level->getMap()->getTileSize().height * SCALE_FACTOR + 100
	);
	

	for (Rect tile : tiles) {

		if (tile.intersectsRect(player_rect)) {
			if (player->velocity_y > 0) {

				player->setPositionY(player->getPositionY() - player->velocity_y);

			}
			else {

				player->setPositionY(tile.getMaxY());
				// if we hit the ground, mark us as grounded so we can jump
				player->grounded = true;
				player->jumping = false;

			}
			player->velocity_y = 0;
			break;

		}
		player->grounded = false;
	}


	player->updateState(delta);
	player->velocity_x = 0;
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{

	if (std::find(heldKeys.begin(), heldKeys.end(), keyCode) == heldKeys.end()) {
		heldKeys.push_back(keyCode);
	}

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
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

GameScene::GameScene(void)
{
	setKeyboardEnabled(true);
	collidesX = false;
}
GameScene::~GameScene(void)
{
}