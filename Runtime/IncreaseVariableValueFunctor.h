#pragma once
#include <functional>

#include "ActionFunctor.h"
#include "RuntimeAction.h"
#include "EcgVariable.h"
#include "GameObject.h"

class IncreaseVariableValueFunctor : public ActionFunctor
{
public:
	//TODO : Make Create static funciton
	static void RegisterToRuntimeAction(RuntimeAction* runtimeAction, GameObject* targetGameObject, const rapidjson::Value& actionValueObject);
	IncreaseVariableValueFunctor(GameObject* target, const string& vairableName, float increaseBy);	
	virtual void Execute(float delta) override;

private:
	static void increase(EcgVariable* targetVariable, float increaseBy);

private:
	GameObject* _target;
	EcgVariable* _targetVariable;
	std::function<void(EcgVariable*, float)> _increaseFunction;
	string _variableName;
	//TODO : Support _increaseBy to be a Variable
	//This can be negative value
	float _increaseBy = 0;
};

