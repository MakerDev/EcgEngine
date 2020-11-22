#include "SetSpriteFrameFunctor.h"
#include "ActionArgument.h"

void SetSpriteFrameFunctor::RegisterToRuntimeAction(RuntimeAction* runtimeAction, GameObject* target, const rapidjson::Value& actionObjectValue)
{
	const auto& arguments = actionObjectValue["Arguments"].GetArray();

	//Arg1 : animation name
	const ActionArgument arg1(arguments[0]);
	auto& spriteName = arg1.GetValue();

	auto functor = new SetSpriteFrameFunctor();
	functor->_visualComponent = target->GetVisual();
	functor->_spriteName = spriteName;

	runtimeAction->PushFunctor(unique_ptr<ActionFunctor>(functor));
}

void SetSpriteFrameFunctor::Execute(float delta)
{
	_visualComponent->GetSprite()->setSpriteFrame(Sprite::createWithSpriteFrameName(_spriteName)->getSpriteFrame());
}
