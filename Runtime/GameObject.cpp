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

unique_ptr<GameObject> GameObject::CreateFromJsonValue(const rapidjson::Value& value)
{
	auto gameObject = make_unique<GameObject>();

	//TODO: Extract these infomation from json file.
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("solbrain.plist");
	AnimationCache::getInstance()->addAnimationsWithFile("solbrain-animations.plist");

	//TODO: Encapsulate them
	gameObject->sprite = Sprite::createWithSpriteFrameName("idle");
	gameObject->sprite->setFlippedX(true);

	const int scaleFactor = value["ScaleFactor"].GetInt();
	gameObject->setScaleFactor(scaleFactor);

	auto& position = value["Position"];
	gameObject->position = Point(position["X"].GetInt(), position["Y"].GetInt());
	gameObject->size = gameObject->sprite->getContentSize();

	auto& scriptComponents = value["ScriptComponents"];


	for (auto& scriptComponent : scriptComponents.GetArray())
	{
		gameObject->addActionFromJsonValue(scriptComponent);
	}

	//float moveDelta = 2;
	//gameObject->addAction("MoveX", &moveDelta);

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

/// <summary>
/// Add action from json 'ScriptComponent' Value
/// </summary>
/// <param name="scriptComponentValue">ScriptComponent rapidjson Value</param>
void GameObject::addActionFromJsonValue(const rapidjson::Value& scriptComponentValue)
{
	auto& triggerValue = scriptComponentValue["Trigger"];
	TriggerType triggerType = static_cast<TriggerType>(triggerValue["Type"].GetInt());


	switch (triggerType)
	{
	case TriggerType::KeyboardEvent:
	{
		auto& keyEventTrigger = triggerValue["KeyEventTrigger"];
		KeyEventType keyEventType = static_cast<KeyEventType>(keyEventTrigger["KeyEventType"].GetInt());
		EventKeyboard::KeyCode keycode = static_cast<EventKeyboard::KeyCode>(keyEventTrigger["Key"].GetInt());


		//TODO : fix this. 키코드가 닷넷이랑 다르다.
		if ((int)keycode == 39)
		{
			keycode = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
		}
		else
		{
			keycode = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
		}

		auto trigger = make_unique<KeyEventTrigger>(keyEventType, keycode);

		auto& actionValueList = scriptComponentValue["Actions"];

		auto runtimeAction = make_shared<RuntimeAction>(std::move(trigger));

		for (auto& actionValue : actionValueList.GetArray())
		{
			string actionName = actionValue["Name"].GetString();

			//TODO : Extract this to proprt function
			if (actionName.compare("MoveX") == 0)
			{
				const auto& arguments = actionValue["Arguments"].GetArray();

				//TODO : 여기도 템플릿을 각 클래스로 만들어서 매개변수 같은거 제대로 설정편하게 하돌고 바꾸자
				//각 템플릿 내부에서 Arguments를 받아서 처리하거나한다. 아래와 같은 바인딩할 함수도 좀 미리 만들어두고

				//Arg1 : Direction
				std::function<void(void)> flipFalse = std::bind(RuntimeActionTemplates::FlipSpriteXFalse, this);
				std::function<void(void)> flipTrue = std::bind(RuntimeActionTemplates::FlipSpriteXTrue, this);

				if (strcmp(arguments[0]["Value"].GetString(), "Right") == 0)
				{
					runtimeAction->pushFunction(flipTrue);
				}
				else
				{
					runtimeAction->pushFunction(flipFalse);
				}

				//Value값이 generic이라서 string이기 때문. 타입보고 변환해줄필요있음
				string val = arguments[1]["Value"].GetString();
				int velocity = stoi(val);
				std::function<void(void)> moveFunc = std::bind(RuntimeActionTemplates::MoveX, this, velocity);

				runtimeAction->pushFunction(moveFunc);
			}
		}

		this->_keyboardTriggeredActions.push_back(runtimeAction);

		break;
	}
	case TriggerType::ClickEvent:
		break;
	case TriggerType::InteractionEvent:
		break;
	case TriggerType::VariableEvent:
		break;
	default:
		break;
	}
}
