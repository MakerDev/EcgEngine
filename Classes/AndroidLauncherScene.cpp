#include "AndroidLauncherScene.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;

Scene* AndroidLauncherScene::createScene() {
	auto scene = Scene::create();

	auto layer = AndroidLauncherScene::create();
	scene->addChild(layer);

	return scene;
}

bool AndroidLauncherScene::init()
{
	auto infoLabel = Label::createWithSystemFont("다운받을 파일명:", "Arial", 30);

	this->addChild(infoLabel);

	auto textField = ui::TextField::create("", "Arial", 30);
	textField->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{

		});


	this->addChild(textField);

	auto fetchButton = Button::create("HelloWorld.png");
	fetchButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{
			auto packageName = textField->getString();
			
		});

	return true;
}




