#pragma once
#include "ActionFunctor.h"
#include "RuntimeAction.h"
#include "GameObject.h"

class SetVariableValueFunctor :public ActionFunctor
{
public:
	static void RegisterToRuntimeAction(RuntimeAction* runtimeAction, GameObject* targetGameObject, const rapidjson::Value& actionValueObject);
	SetVariableValueFunctor(GameObject* target, const string& name, const string& newValue);
	virtual void Execute(float delta) override;

private:
	GameObject* _target;
	EcgVariable* _targetVariable;
	string _newValue;
	string _variableName;
};

