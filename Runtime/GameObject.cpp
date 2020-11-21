#include <functional>
#include <rapidjson/document.h>

#include "GameObject.h"
#include "KeyEventTrigger.h"
#include "KeyEventTypes.h"
#include "ActionArgument.h"
#include "RuntimeActionCatalog.h"

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
	gameObject->SetScaleFactor(scaleFactor);

	auto& position = value["Position"];
	gameObject->position = Point(position["X"].GetInt(), position["Y"].GetInt());
	gameObject->size = gameObject->sprite->getContentSize();

	auto& scriptComponents = value["ScriptComponents"];

	for (auto& scriptComponent : scriptComponents.GetArray())
	{
		gameObject->addActionFromJsonValue(scriptComponent);
	}

	return std::move(gameObject);
}

float GameObject::GetScaleFactor() const noexcept
{
	return _scaleFactor;
}

void GameObject::SetScaleFactor(float scaleFactor)
{
	_scaleFactor = scaleFactor;
	this->sprite->setScale(_scaleFactor);
}

Point GameObject::GetPosition() const
{
	return sprite->getPosition();
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
				(*i)->Execute();
			}
		}
	}
}

Sprite* GameObject::GetSprite() const
{
	return sprite;
}

/// <summary>
/// Add action from json 'ScriptComponent' Value
/// </summary>
/// <param name="scriptComponentValue">ScriptComponent rapidjson Value</param>
void GameObject::addActionFromJsonValue(const rapidjson::Value& scriptComponentValue)
{
	auto& triggerValue = scriptComponentValue["Trigger"];
	const TriggerType triggerType = static_cast<TriggerType>(triggerValue["Type"].GetInt());

	switch (triggerType)
	{
	case TriggerType::KeyboardEvent:
	{
		auto trigger = KeyEventTrigger::CreateFromJsonValue(triggerValue["KeyEventTrigger"]);
		auto& actionValueList = scriptComponentValue["Actions"];

		auto runtimeAction = make_shared<RuntimeAction>(std::move(trigger));

		for (auto& actionValue : actionValueList.GetArray())
		{
			string actionName = actionValue["Name"].GetString();

			RuntimeActionCatalog::AddAction(actionName, runtimeAction.get(), this, actionValue);
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
