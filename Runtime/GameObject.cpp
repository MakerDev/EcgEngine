#include <functional>
#include <rapidjson/document.h>

#include "GameObject.h"
#include "KeyEventTrigger.h"
#include "KeyEventType.h"
#include "ActionArgument.h"
#include "JsonHelper.h"
#include "RuntimeActionCatalog.h"
#include "runtime-core.h"

unique_ptr<GameObject> GameObject::CreateFromJsonValue(const rapidjson::Value& value)
{
	auto gameObject = make_unique<GameObject>();
	
	gameObject->_name = value["Name"].GetString();

	//TODO: Extract these infomation from json file.
	gameObject->_visualComponent = make_unique<VisualComponent>("solbrain.plist", "solbrain-animations.plist", "idle");

	//TODO : Extract this from json
	gameObject->_visualComponent->RegisterAnimation("walk", 0.5);
	gameObject->GetSprite()->setFlippedX(true);

	const float scaleFactor = value["ScaleFactor"].GetFloat();
	gameObject->SetScaleFactor(scaleFactor);

	auto& position = value["Position"];

	gameObject->position = Point(position["X"].GetInt(), position["Y"].GetInt());
	gameObject->size = gameObject->GetSprite()->getContentSize();


	//INFO : Variables must be parsed before ScriptComponents as some script depends on variables
	auto& localVariables = value["Variables"];

	for (auto& localVariable : JsonHelper::GetConstArray(localVariables))
	{
		gameObject->addNewVariableFromJsonValue(localVariable);
	}

	GameObject* target = gameObject.get();

	gameObject->_registerActions = [&value, target] () {
		//TODO orignal unique_ptr is moved due to std::move.
		target->registerAllActionInternal(value);
	};

	//Check if this is affcted by gravity
	//This creates constatnt true trigger
	gameObject->_gravity = make_unique<RuntimeAction>();
	auto gravityFuntor = make_shared<MoveYFunctor>(gameObject.get(), -GRAVITY_FACTOR);
	gameObject->_gravity->PushFunctor(gravityFuntor);
	
	return std::move(gameObject);
}


void GameObject::registerAllActionInternal(const rapidjson::Value& value)
{
	auto& scriptComponents = value["ScriptComponents"];

	for (auto& scriptComponent : JsonHelper::GetConstArray(scriptComponents))
	{
		this->addActionFromJsonValue(scriptComponent);
	}
}

GameObject::GameObject()
{
	_localVariableEngine = make_unique<VariableEngine>();
}

float GameObject::GetScaleFactor() const noexcept
{
	return _scaleFactor;
}

void GameObject::SetScaleFactor(float scaleFactor)
{
	_scaleFactor = scaleFactor;
	this->GetSprite()->setScale(_scaleFactor);
}

Point GameObject::GetPosition() const
{
	return this->GetSprite()->getPosition();
}

string GameObject::GetObjectName() const noexcept
{
	return _name;
}

void GameObject::OnUpdate(float delta, const vector<EventKeyboard::KeyCode>& heldKeys, const vector<EventKeyboard::KeyCode>& releasedKeys)
{
	//TODO: 만약 timeDelta가 필요한 액션이면 placeholder에 delta값을 채워넘기기
	for (auto& keyTriggeredAction : _keyboardTriggeredActions)
	{
		//Process keyDown events
		for (auto& pressedKey : heldKeys)
		{
			const auto context = EventContext(KeyEventType::Down, pressedKey);

			if (keyTriggeredAction->GetTrigger().IsMatched(context))
			{
				keyTriggeredAction->Execute(delta);

				//If the trigger was matched with KeyDownEvent, it will never math KeyUpEvent.
				continue;
			}
		}

		//Process keyUp events
		for (auto& releasedKey : releasedKeys)
		{
			const auto context = EventContext(KeyEventType::Released, releasedKey);

			if (keyTriggeredAction->GetTrigger().IsMatched(context))
			{
				keyTriggeredAction->Execute(delta);
			}
		}
	}

	if (_gravity != nullptr)
	{
		_gravity->Execute(delta);
	}
}

VisualComponent* GameObject::GetVisual() const noexcept
{
	assert(_visualComponent != nullptr && "VisualComponent is null");

	return _visualComponent.get();
}

VisualComponent* GameObject::GetVisualConst() const noexcept
{
	assert(_visualComponent != nullptr && "VisualComponent is null");

	return _visualComponent.get();
}

Sprite* GameObject::GetSprite() const noexcept
{
	assert(_visualComponent != nullptr && "Couldn't get sprite from null visual component");

	return _visualComponent->GetSprite();
}

VariableEngine* GameObject::GetLocalVariableEngine() noexcept
{
	return _localVariableEngine.get();
}

void GameObject::RegisterAllActions()
{
	this->_registerActions();
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

		for (auto& actionValue : JsonHelper::GetConstArray(actionValueList))
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

void GameObject::addNewVariableFromJsonValue(const rapidjson::Value& variableValue)
{
	auto name = variableValue["Name"].GetString();
	const VariableType type = static_cast<VariableType>(variableValue["EcgVariableType"].GetInt());
	auto valueString = variableValue["Value"].GetString();

	auto newVariable = this->GetLocalVariableEngine()->CreateNewVariableWithName(name, type);

	assert(newVariable != nullptr && "Creating new variable failed");

	newVariable->SetValueByString(valueString);
}
