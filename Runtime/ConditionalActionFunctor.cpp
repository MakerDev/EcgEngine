#include "ConditionalActionFunctor.h"
#include "JsonHelper.h"
#include "ActionArgument.h"
#include "EngineManager.h"
#include "VariableCondition.h"

void ConditionalActionFunctor::Execute(float delta)
{
	for (auto functor : _nestedFunctors)
	{
		functor->Execute(delta);
	}
}

void ConditionalActionFunctor::RegisterToRuntimeAction(RuntimeAction* runtimeAction, GameObject* target, const rapidjson::Value& actionObjectValue)
{
	//TODO : Rather than using ActionArgument, directly use json value
	const auto& arguments = JsonHelper::GetConstArray(actionObjectValue["Arguments"]);

	//TODO : Parse condition
	auto& conditionJsonValue = actionObjectValue["VariableCondition"];
	auto variableCondition = VariableCondition::CreateFromJsonValue(conditionJsonValue);

	const int numOfNestedAction = actionObjectValue["NestedActionsCount"].GetInt();

	//TODO : Parse nested actions

}
