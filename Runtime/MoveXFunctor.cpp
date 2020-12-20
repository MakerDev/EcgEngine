#include "MoveXFunctor.h"
#include "RuntimeActionTemplates.h"
#include "ActionArgument.h"
#include "JsonHelper.h"

void MoveXFunctor::Execute(float delta)
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
	const auto& arguments = JsonHelper::GetConstArray(actionObjectValue["Arguments"]);

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
	//Value���� generic�̶� string�̱� ����. Ÿ�Ժ��� ��ȯ�����ʿ�����
	int velocity = stoi(arg2.GetValue());
	auto moveFunction = std::bind(RuntimeActionTemplates::MoveX, target, velocity);

	unique_ptr<ActionFunctor> functor = make_unique<MoveXFunctor>(flipFunction, moveFunction);

	runtimeAction->PushFunctor(std::move(functor));
}
