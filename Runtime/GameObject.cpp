#include <functional>
#include <rapidjson/document.h>

#include "GameObject.h"
#include "KeyEventTrigger.h"
#include "KeyEventTypes.h"
#include "RuntimeActionTemplates.h"

unique_ptr<GameObject> GameObject::CreateFromJson(string filename, int speed)
{
	auto gameObject = make_unique<GameObject>();

	//TODO: Extract these infomation from json file.
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("solbrain.plist");
	AnimationCache::getInstance()->addAnimationsWithFile("solbrain-animations.plist");

	//TODO: Encapsulate them
	gameObject->sprite = Sprite::createWithSpriteFrameName("idle");
	gameObject->sprite->setFlippedX(true);

	gameObject->setScaleFactor(2.0F);

	gameObject->position = Point(10, 2);
	gameObject->size = gameObject->sprite->getContentSize();

	float moveDelta = speed;
	gameObject->addAction("MoveX", &moveDelta);

	return std::move(gameObject);
}

float GameObject::getScaleFactor() const noexcept
{
	return _scaleFactor;
}

void GameObject::setScaleFactor(float scaleFactor)
{
	_scaleFactor = scaleFactor;
	this->sprite->setScale(_scaleFactor);
}

void GameObject::onUpdate(float delta, const vector<EventKeyboard::KeyCode>& heldKeys)
{
	//TODO: 만약 timeDelta가 필요한 액션이면 placeholder에 delta값을 채워넘기기

	//1. handle key events
	for (auto i = _keyboardTriggeredActions.begin(); i != _keyboardTriggeredActions.end(); i++)
	{
		for (auto j = heldKeys.begin(); j != heldKeys.end(); j++)
		{
			const auto context = EventContext(KeyEventType::Down, *j);

			if ((*i)->GetTrigger().IsMatched(context))
			{
				(*i)->execute();
			}
		}
	}
}

//TODO : void* 배열을 인자로 받기 -> 각 액션에 필요한 파라미터 리스트임
void GameObject::addAction(string name, void* param)
{
	if (name == "MoveX")
	{
		/// <param name="keycode">어떤키를 누를때 움직일 것인가</param>
		/// <param name="delta">얼마나 움직일지</param>
		assert(param != nullptr && "Param should never be null for MoveX");

		float delta = *((float*)param);

		std::function<void(void)> func = std::bind(RuntimeActionTemplates::MoveX, this, -delta);
		std::function<void(void)> flipFalse = std::bind(RuntimeActionTemplates::FlipSpriteXFalse, this);

		auto trigger = make_unique<KeyEventTrigger>(KeyEventType::Down, EventKeyboard::KeyCode::KEY_LEFT_ARROW);
		auto runtimeAction = make_shared<RuntimeAction>(std::move(trigger));
		runtimeAction->pushFunction(func);
		runtimeAction->pushFunction(flipFalse);

		this->_keyboardTriggeredActions.push_back(runtimeAction);

		trigger = make_unique<KeyEventTrigger>(KeyEventType::Down, EventKeyboard::KeyCode::KEY_RIGHT_ARROW);
		std::function<void(void)> func_right = std::bind(RuntimeActionTemplates::MoveX, this, delta);
		std::function<void(void)> flipTrue = std::bind(RuntimeActionTemplates::FlipSpriteXTrue, this);

		runtimeAction = make_shared<RuntimeAction>(std::move(trigger));
		runtimeAction->pushFunction(func_right);
		runtimeAction->pushFunction(flipTrue);

		this->_keyboardTriggeredActions.push_back(runtimeAction);
	}
}
