#include "MoveXFunctor.h"
#include "RuntimeActionTemplates.h"
#include "ActionArgument.h"

void MoveXFunctor::Execute()
{
	_flipFunction();
	_moveFunction();
}

MoveXFunctor::MoveXFunctor(function<void(void)> flipFuction, function<void(void)> moveFunction)
	:_flipFunction(flipFuction), _moveFunction(moveFunction)
{

}
//TODO : Make this non static so that ActionFunctor can be abstract
void MoveXFunctor::RegisterToRuntimeAction(RuntimeAction* runtimeAction, GameObject* target, const rapidjson::Value& actionObjectValue)
{
	const auto& arguments = actionObjectValue["Arguments"].GetArray();

	//Arg1 : Direction
	const ActionArgument arg1(arguments[0]);

	function<void(void)> flipFunction;

	if (arg1.GetValue().compare("Right") == 0)
	{
		flipFunction = std::bind(RuntimeActionTemplates::FlipSpriteXTrue, target);
	}
	else
	{
		flipFunction = std::bind(RuntimeActionTemplates::FlipSpriteXFalse, target);
	}

	const ActionArgument arg2(arguments[1]);
	//Value값이 generic이라서 string이기 때문. 타입보고 변환해줄필요있음
	int velocity = stoi(arg2.GetValue());
	auto moveFunction = std::bind(RuntimeActionTemplates::MoveX, target, velocity);

	unique_ptr<ActionFunctor> functor = make_unique<MoveXFunctor>(flipFunction, moveFunction);

	runtimeAction->PushFunctor(std::move(functor));
}
