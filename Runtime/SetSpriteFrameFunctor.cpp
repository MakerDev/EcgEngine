#include "SetSpriteFrameFunctor.h"
#include "ActionArgument.h"
#include "JsonHelper.h"

std::shared_ptr<ActionFunctor> SetSpriteFrameFunctor::Create(GameObject* target, const rapidjson::Value& actionObjectValue)
{
	const auto& arguments = JsonHelper::GetConstArray(actionObjectValue["Arguments"]);

	//Arg1 : animation name
	const ActionArgument arg1(arguments[0]);
	auto& spriteName = arg1.GetValue();

	auto functor = new SetSpriteFrameFunctor();
	functor->_visualComponent = target->GetVisual();
	functor->_spriteName = spriteName;

	return shared_ptr<SetSpriteFrameFunctor>(functor);
}

void SetSpriteFrameFunctor::RegisterToRuntimeAction(RuntimeAction* runtimeAction, GameObject* target, const rapidjson::Value& actionObjectValue)
{
	auto functor = SetSpriteFrameFunctor::Create(target, actionObjectValue);

	assert(runtimeAction != nullptr && "Runtimeaction must not be null");

	runtimeAction->PushFunctor(functor);
}

void SetSpriteFrameFunctor::Execute(float delta)
{
	_visualComponent->GetSprite()->setSpriteFrame(Sprite::createWithSpriteFrameName(_spriteName)->getSpriteFrame());
}
