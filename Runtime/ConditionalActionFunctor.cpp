#include "ConditionalActionFunctor.h"
#include "JsonHelper.h"
#include "ActionArgument.h"

void ConditionalActionFunctor::Execute(float delta)
{
	for (auto functor : _nestedFunctors)
	{
		functor->Execute(delta);
	}
}

void ConditionalActionFunctor::RegisterToRuntimeAction(RuntimeAction* runtimeAction, GameObject* target, const rapidjson::Value& actionObjectValue)
{
	const auto& arguments = JsonHelper::GetConstArray(actionObjectValue["Arguments"]);

	//TODO : Parse condition

	//TODO : Parse nested actions

}
