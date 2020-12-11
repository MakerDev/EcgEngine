#pragma once
#include <rapidjson/document.h>

#include "ActionFunctor.h"
#include "RuntimeAction.h"
#include "EcgVariable.h"
#include "ConditionType.h"
#include "GameObject.h"

class ConditionalActionFunctor : public ActionFunctor
{
public:
	static void RegisterToRuntimeAction(RuntimeAction* runtimeAction, GameObject* target, const rapidjson::Value& actionObjectValue);

	void Execute(float delta) override;

private:
	ConditionType _conditionType;
	EcgVariable* _targetVariable;
	std::vector<std::shared_ptr<ActionFunctor>> _nestedFunctors;
};

