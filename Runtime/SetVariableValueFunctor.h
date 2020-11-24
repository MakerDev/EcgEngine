#pragma once
#include "ActionFunctor.h"
#include "RuntimeAction.h"
#include "GameObject.h"

class SetVariableValueFunctor :public ActionFunctor
{
public:
	static void RegisterToRuntimeAction(RuntimeAction* runtimeAction, GameObject* targetGameObject, const rapidjson::Value& actionValueObject);
	SetVariableValueFunctor(GameObject* target, const string& name, function<void(void)> setter);
	virtual void Execute(float delta) override;

private:
	GameObject* _target;
	string _variableName;
	function<void(void)> _setter;
};

