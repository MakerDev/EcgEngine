#include "RuntimeJumpByFunctor.h"
#include "ActionArgument.h"
#include "JsonHelper.h"
#include "runtime-core.h"

shared_ptr<ActionFunctor> RuntimeJumpByFunctor::Create(GameObject* targetGameObject, const rapidjson::Value& actionValueObject)
{
	assert(targetGameObject != nullptr && "Param targetGameObject cannot be null");

	const auto& arguments = JsonHelper::GetConstArray(actionValueObject["Arguments"]);

	//Arg1 : Duration
	const ActionArgument durationArg(arguments[0]);
	const float duration = stof(durationArg.GetValue());

	//Arg2 : Height
	const ActionArgument heightArg(arguments[1]);
	const float height = stoi(heightArg.GetValue());

	std::shared_ptr<ActionFunctor> functor = make_shared<RuntimeJumpByFunctor>(targetGameObject, duration, height);

	return functor;
}

void RuntimeJumpByFunctor::RegisterToRuntimeAction(RuntimeAction* runtimeAction, GameObject* targetGameObject, const rapidjson::Value& actionValueObject)
{
	auto functor = RuntimeJumpByFunctor::Create(targetGameObject, actionValueObject);
	runtimeAction->PushFunctor(functor);
}

RuntimeJumpByFunctor::RuntimeJumpByFunctor(GameObject* target, float duration, int height)
	: _isFirstJump(true), _target(target)
{
	this->_jumpBy = RuntimeJumpBy::Create(duration, height);
	//this->_jumpBy = unique_ptr<JumpBy>(JumpBy::create(duration, Vec2(0, 0), height, 1));
	this->_jumpBy->retain();
}

void RuntimeJumpByFunctor::Execute(float delta)
{
	auto sprite = _target->GetSprite();

	assert(sprite != nullptr);

	if (_isFirstJump || _jumpBy->isDone())
	{
		sprite->runAction(_jumpBy.get());
		_isFirstJump = false;
	}
}