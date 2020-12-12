#include "IncreaseVariableValueFunctor.h"
#include "JsonHelper.h"
#include "ActionArgument.h"


void IncreaseVariableValueFunctor::RegisterToRuntimeAction(RuntimeAction* runtimeAction, GameObject* targetGameObject, const rapidjson::Value& actionValueObject)
{
	const auto& arguments = JsonHelper::GetConstArray(actionValueObject["Arguments"]);

	//Arg1 : VarableName
	const ActionArgument arg1(arguments[0]);
	const string& variableName = arg1.GetValue();

	//Arg2 : IncreaseBy
	const ActionArgument arg2(arguments[0]);
	const float increaseBy = std::stof(arg2.GetValue());

	shared_ptr<IncreaseVariableValueFunctor> functor = make_shared<IncreaseVariableValueFunctor>(targetGameObject, variableName, increaseBy);

	runtimeAction->PushFunctor(std::shared_ptr<IncreaseVariableValueFunctor>(functor));
}

IncreaseVariableValueFunctor::IncreaseVariableValueFunctor(GameObject* target, const string& variableName, float increaseBy)
	: _target(target), _variableName(_variableName), _increaseBy(increaseBy)
{
	auto localVariableEngine = _target->GetLocalVariableEngine();

	assert(localVariableEngine != nullptr && "Failed to get localVariableEngine");
	_targetVariable = localVariableEngine->GetVariableWithName(_variableName);

	assert(_targetVariable->GetType() != VariableType::typeString && "Cannot increase string variable");
}

void IncreaseVariableValueFunctor::Execute(float delta)
{
	increase(_targetVariable, _increaseBy);
}

void IncreaseVariableValueFunctor::increase(EcgVariable* targetVariable, float increaseBy)
{
	const auto type = targetVariable->GetType();

	if (type == VariableType::typeInteger)
	{
		const auto originalValue = targetVariable->GetIntegerValue();
		targetVariable->SetIntegerValue(increaseBy + originalValue);
	}
	else if (type == VariableType::typeFloat)
	{
		const auto originalValue = targetVariable->GetFloatValue();
		targetVariable->SetFloatValue(increaseBy + originalValue);
	}
}
