#include "PlayAnimationFunctor.h"
#include "ActionArgument.h"

void PlayAnimationFunctor::RegisterToRuntimeAction(RuntimeAction* runtimeAction, GameObject* target, const rapidjson::Value& actionObjectValue)
{
	const auto& arguments = actionObjectValue["Arguments"].GetArray();

	//Arg1 : animation name
	const ActionArgument arg1(arguments[0]);
	auto& animationName = arg1.GetValue();

	auto functor = new PlayAnimationFunctor(animationName);
	functor->_visualComponent = target->GetVisual();

	runtimeAction->PushFunctor(unique_ptr<ActionFunctor>(functor));
}

inline PlayAnimationFunctor::PlayAnimationFunctor(const string& animationName)
	: _animationName(animationName)
{

}

void PlayAnimationFunctor::Execute(float delta)
{
	_visualComponent->PlayAnimation(_animationName, delta);
}