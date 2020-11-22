#include "RuntimeJumpByFunctor.h"
#include "ActionArgument.h"

void RuntimeJumpByFunctor::RegisterToRuntimeAction(RuntimeAction* runtimeAction, GameObject* targetGameObject, const rapidjson::Value& actionValueObject)
{
	assert(runtimeAction != nullptr && "Param runtimeAction cannot be null");
	assert(targetGameObject != nullptr && "Param targetGameObject cannot be null");

	const auto& arguments = actionValueObject["Arguments"].GetArray();

	//Arg1 : Duration
	const ActionArgument durationArg(arguments[0]);
	const float duration = stof(durationArg.GetValue());

	//Arg2 : Height
	const ActionArgument heightArg(arguments[1]);
	const float height = stoi(heightArg.GetValue());

	std::unique_ptr<ActionFunctor> functor = make_unique<RuntimeJumpByFunctor>(targetGameObject, duration, height);
	runtimeAction->PushFunctor(std::move(functor));
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