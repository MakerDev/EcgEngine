#include "ActionArgument.h"
#include "SetVariableValueFunctor.h"
#include "JsonHelper.h"

void SetVariableValueFunctor::RegisterToRuntimeAction(RuntimeAction* runtimeAction, GameObject* targetGameObject, const rapidjson::Value& actionValueObject)
{
	const auto& arguments = JsonHelper::GetConstArray(actionValueObject["Arguments"]);

	//Arg1 : VarableName
	const ActionArgument arg1(arguments[0]);
	const string& variableName = arg1.GetValue();

	//Arg2 : Value Type
	const ActionArgument arg2(arguments[0]);
	const string& valueType = arg2.GetValue();

	//Arg2 : Value converted to string
	const ActionArgument arg3(arguments[0]);
	function<void(void)> setter;

	if (valueType=="float")
	{
		const float value = stof(arg3.GetValue());
	}

	//function<void(void)> flipFunction;

	//if (arg1.GetValue().compare("Right") == 0)
	//{
	//	flipFunction = std::bind(RuntimeActionTemplates::FlipSpriteXTrue, target);
	//}
	//else
	//{
	//	flipFunction = std::bind(RuntimeActionTemplates::FlipSpriteXFalse, target);
	//}

	//const ActionArgument arg2(arguments[1]);
	////Value값이 generic이라서 string이기 때문. 타입보고 변환해줄필요있음
	//int velocity = stoi(arg2.GetValue());
	//auto moveFunction = std::bind(RuntimeActionTemplates::MoveX, target, velocity);

	//unique_ptr<ActionFunctor> functor = make_unique<MoveXFunctor>(flipFunction, moveFunction);

	//runtimeAction->PushFunctor(std::move(functor));
}

SetVariableValueFunctor::SetVariableValueFunctor(GameObject* target, const string& name, function<void(void)> setter)
	: _target(target), _variableName(name), _setter(setter)
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
}

void SetVariableValueFunctor::Execute(float delta)
{
}
