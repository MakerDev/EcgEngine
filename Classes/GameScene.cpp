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
	player_sprite->setAnchorPoint(Point(0, 0));

	player_sprite->setFlippedX(true);

	Point point = Point(10, 2);

	//Size size = player_sprite->getContentSize();

	player_sprite->setPosition(level->tileCoordinateToPosition(point));

	player = new Player();
	player->retain();
	player->state = Player::State::Standing;
	player->position = player_sprite->getPosition();
	player->player_size.width = player_sprite->getBoundingBox().size.width;
	player->player_size.height = player_sprite->getBoundingBox().size.height;
	
	Point origin = Director::getInstance()->getVisibleOrigin();
	Size wsize = Director::getInstance()->getVisibleSize();  //default screen size (or design resolution size, if you are using design resolution)
	Point* center = new Point(wsize.width / 2 + origin.x, wsize.height / 2 + origin.y);

	cameraTarget = Sprite::create();
	cameraTarget->setPositionX(player_sprite->getPosition().x); // set to players x
	cameraTarget->setPositionY(wsize.height / 2 + origin.y); // center of height

	cameraTarget->retain();

	this->setupAnimations();
	this->addChild(player_sprite);
	this->schedule(schedule_selector(GameScene::updateScene));
	
	this->addChild(cameraTarget);

	rectWithBorder = DrawNode::create();
	Vec2 vertices[] =
	{
		Vec2(0, player_sprite->getBoundingBox().size.height),
		Vec2(player_sprite->getBoundingBox().size.width, player_sprite->getBoundingBox().size.height),
		Vec2(player_sprite->getBoundingBox().size.width, 0),
		Vec2(0,0)
	};

	rectWithBorder->drawPolygon(vertices, 4, Color4F(0.0f, 0.3f, 0.3f, 1), 0, Color4F(0.0f, 0.2f, 0.0f, 1));

	addChild(rectWithBorder);

	camera = Follow::create(cameraTarget, Rect::ZERO);
	camera->retain();

	this->runAction(camera);

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
	player->setPositionX(player->getPositionX() + x);
	player_sprite->setPositionX(player_sprite->getPositionX() + x);
}

void GameScene::updateScene(float delta) {
	cameraTarget->setPositionX(player_sprite->getPosition().x + CAMERA_SPRITE_OFFSET_X);
	this->updatePlayer(delta);
}

void GameScene::updatePlayer(float delta) {

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

	if (std::find(heldKeys.begin(), heldKeys.end(), UP_ARROW) != heldKeys.end()) {
		if (player->grounded && player->velocity.y <= 0) {
			player->velocity.y = PLAYER_JUMP_VELOCITY;
			player->state = Player::State::Jumping;
			player->grounded = false;
		}

	}
	
	player->velocity -= Point(0, GRAVITY);
	stutteringFix = 1;

	Rect player_rect = player_sprite->getTextureRect();

	Point tmp;
	vector<Rect> tiles;
	tiles.clear();

	tmp = level->positionToTileCoordinate(Point(player->position.x + player->player_size.width * 0.5f,
		player->position.y + player->player_size.height * 0.5f));

	if (player->velocity.x > 0) {
		tiles = level->getCollisionTilesX(tmp, 1);
	}
	else {
		tiles = level->getCollisionTilesX(tmp, -1);
	}

	player_rect.setRect(
		player_sprite->getBoundingBox().getMinX() + player->velocity.x,
		player_sprite->getBoundingBox().getMinY() + 2.0f, // dont let the rectangle touch the ground otherwise, will count as collision
		player->player_size.width,
		player->player_size.height
	);

	for (Rect tile : tiles) {
		if (player_rect.intersectsRect(tile)) {
			player->velocity.x = 0;
			break;
		}
	}

	tiles.clear();

	if (player->velocity.y > 0) {
		tiles = level->getCollisionTilesY(tmp, 1);
	}
	else {
		tiles = level->getCollisionTilesY(tmp, -1);
	}

	player_rect.setRect(
		player_sprite->getBoundingBox().getMinX(),
		player_sprite->getBoundingBox().getMinY(),
		player->player_size.width,
		player->player_size.height
	);


	for (Rect tile : tiles) {
		if (tile.intersectsRect(player_rect)) {
			if (player->velocity.y > 0) {
				player->position.y = tile.getMinY() - player->player_size.height;
			}
			else {
				player->position.y = tile.getMaxY();
				// if we hit the ground, mark us as grounded so we can jump
				player->grounded = true;
				stutteringFix = 0;
			}
			player->velocity.y = 0;
			break;
		}
		player->grounded = false;
	}

	// unscale the velocity by the inverse delta time and set
	// the latest position
	player->position.x = player->position.x + player->velocity.x;
	player->position.y = player->position.y + player->velocity.y;
	
	this->updatePlayerSprite(delta);
	

	if (std::find(heldKeys.begin(), heldKeys.end(), RIGHT_ARROW) == heldKeys.end() && player->grounded) {
		player->velocity.x = 0;
		player->state = Player::State::Standing;
	}

	if (std::find(heldKeys.begin(), heldKeys.end(), LEFT_ARROW) == heldKeys.end() && player->grounded) {
		player->velocity.x = 0;
		player->state = Player::State::Standing;
	}
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
		player_sprite->setSpriteFrame(Sprite::createWithSpriteFrameName("jump")->getSpriteFrame());
		if (player->facingRight) {
			player_sprite->setFlippedX(true);
		}
		else {
			player_sprite->setFlippedX(false);
		}
	}
	else {
		player_sprite->setSpriteFrame(Sprite::createWithSpriteFrameName("idle")->getSpriteFrame());
	}

	player_sprite->setPositionX(player->position.x);
	if (stutteringFix != 0) {
		player_sprite->setPositionY(player->position.y);
	}
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (std::find(heldKeys.begin(), heldKeys.end(), keyCode) == heldKeys.end()) {
		heldKeys.push_back(keyCode);
	}
	//printf("pressed\n");
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
	//Close the cocos2d-x game scene and quit the application
	//Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}

GameScene::GameScene(void)
{
	setKeyboardEnabled(true);
	collidesX = false;
}
GameScene::~GameScene(void)
{
}
