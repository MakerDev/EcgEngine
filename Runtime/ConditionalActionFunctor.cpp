#include "ConditionalActionFunctor.h"
#include "JsonHelper.h"
#include "ActionArgument.h"
#include "EngineManager.h"
#include "VariableCondition.h"
#include "RuntimeActionCatalog.h"


ConditionalActionFunctor::ConditionalActionFunctor(std::unique_ptr<VariableCondition> condition, std::unique_ptr<RuntimeAction> nestedActions)
	: _condition(std::move(condition)), _nestedActions(std::move(nestedActions))
{

}
void ConditionalActionFunctor::Execute(float delta)
{
	if (_condition->IsMatched())
	{
		_nestedActions->Execute(delta);
	}
}

void ConditionalActionFunctor::RegisterToRuntimeAction(RuntimeAction* runtimeAction, GameObject* target, const rapidjson::Value& actionObjectValue)
{
	//TODO : Rather than using ActionArgument, directly use json value
	const auto& arguments = JsonHelper::GetConstArray(actionObjectValue["Arguments"]);

	auto& conditionJsonValue = actionObjectValue["VariableCondition"];
	auto variableCondition = VariableCondition::CreateFromJsonValue(conditionJsonValue);

	auto nestedActionFunctors = make_unique<RuntimeAction>();
	const auto& nestedActions = JsonHelper::GetConstArray(actionObjectValue["NestedActions"]);

	for (auto& nestedAction : nestedActions)
	{
		string actionName = nestedAction["Name"].GetString();
		RuntimeActionCatalog::AddAction(actionName, nestedActionFunctors.get(), target, nestedAction);
	}
	//As we cannot use unique_ptr after moved, functor should be created at the end
	shared_ptr<ActionFunctor> functor = make_shared<ConditionalActionFunctor>(std::move(variableCondition), std::move(nestedActionFunctors));

	
	runtimeAction->PushFunctor(functor);
}

