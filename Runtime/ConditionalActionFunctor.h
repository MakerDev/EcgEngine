#pragma once
#include <rapidjson/document.h>

#include "ActionFunctor.h"
#include "RuntimeAction.h"
#include "GameObject.h"
#include "VariableCondition.h"

class ConditionalActionFunctor : public ActionFunctor
{
public:
	static void RegisterToRuntimeAction(RuntimeAction* runtimeAction, GameObject* target, const rapidjson::Value& actionObjectValue);
	ConditionalActionFunctor(std::unique_ptr<VariableCondition> condition, std::unique_ptr<RuntimeAction> nestedActions);
	void Execute(float delta) override;

private:
	std::unique_ptr<VariableCondition> _condition;
	std::unique_ptr<RuntimeAction> _nestedActions;
};

