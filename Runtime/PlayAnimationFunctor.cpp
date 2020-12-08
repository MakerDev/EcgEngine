#include "PlayAnimationFunctor.h"
#include "ActionArgument.h"
#include "KeyEventTrigger.h"
#include "JsonHelper.h"
void PlayAnimationFunctor::RegisterToRuntimeAction(RuntimeAction* runtimeAction, GameObject* target, const rapidjson::Value& actionObjectValue)
{
	assert(runtimeAction != nullptr);

	const auto& arguments = JsonHelper::GetConstArray(actionObjectValue["Arguments"]);

	//Arg1 : animation name
	const ActionArgument arg1(arguments[0]);
	auto& animationName = arg1.GetValue();

	auto functor = new PlayAnimationFunctor(target, animationName);

	auto& trigger = runtimeAction->GetTrigger();

	if (trigger.GetType() == TriggerType::KeyboardEvent)
	{
		auto keyTrigger = dynamic_cast<KeyEventTrigger&>(trigger);
		if (keyTrigger.GetKeyEventType() == KeyEventType::Down)
		{
			//TODO : Unregister callback when destructed
			trigger.RegisterMatchResultChangedCallback(std::bind(&PlayAnimationFunctor::SetToIdle, functor, std::placeholders::_1));
		}
	}

	runtimeAction->PushFunctor(unique_ptr<ActionFunctor>(functor));
}

void PlayAnimationFunctor::Execute(float delta)
{
	_visualComponent->PlayAnimation(_animationName, delta);
}

PlayAnimationFunctor::PlayAnimationFunctor(GameObject* target, const string& animationName)
	: _animationName(animationName), _target(target)

{
	_visualComponent = _target->GetVisual();
}

void PlayAnimationFunctor::SetToIdle(bool result)
{
	if (result == false)
	{
		_visualComponent->GetSprite()->setSpriteFrame(Sprite::createWithSpriteFrameName("idle")->getSpriteFrame());
	}
}
