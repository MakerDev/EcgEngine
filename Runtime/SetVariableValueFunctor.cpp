#include "ActionArgument.h"
#include "SetVariableValueFunctor.h"
#include "JsonHelper.h"

void SetVariableValueFunctor::RegisterToRuntimeAction(RuntimeAction* runtimeAction, GameObject* targetGameObject, const rapidjson::Value& actionValueObject)
{
	const auto& arguments = JsonHelper::GetConstArray(actionValueObject["Arguments"]);

	//Arg1 : VarableName
	const ActionArgument arg1(arguments[0]);
	const string& variableName = arg1.GetValue();

	//Arg2 : New Value
	const ActionArgument arg2(arguments[0]);
	const string& newValue = arg2.GetValue();

	shared_ptr<ActionFunctor> functor = make_shared<SetVariableValueFunctor>(targetGameObject, variableName, newValue);

	runtimeAction->PushFunctor(functor);
}

SetVariableValueFunctor::SetVariableValueFunctor(GameObject* target, const string& variableName, const string& newValue)
	: _target(target), _variableName(variableName), _newValue(newValue)
{
	VariableEngine* variableEngine = nullptr;

	if (_target == nullptr)
	{
		variableEngine = VariableEngine::GetGlobalInstance();
	}
	else
	{
		variableEngine = _target->GetLocalVariableEngine();
	}

	_targetVariable = variableEngine->GetVariableWithName(variableName);
}

void SetVariableValueFunctor::Execute(float delta)
{
	_targetVariable->SetValueByString(_newValue);
}
