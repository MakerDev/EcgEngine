#include "RuntimeJumpByFunctor.h"
#include "ActionArgument.h"

void RuntimeJumpByFunctor::AddActionFromJson(GameObject* targetGameObject, RuntimeAction* runtimeAction, const rapidjson::Value& actionValueObject)
{
	const auto& arguments = actionValueObject["Arguments"].GetArray();

	//Arg1 : Duration to height repeat
	const ActionArgument durationArg(arguments[0]);
	const float duration = stof(durationArg.GetValue());

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

void RuntimeJumpByFunctor::Execute()
{
	auto sprite = _target->GetSprite();

	assert(sprite != nullptr);

  	if (_isFirstJump || _jumpBy->isDone())
	{
		sprite->runAction(_jumpBy.get());
		CCLOG("executed");
		_isFirstJump = false;
	}/*
	else if (_jumpBy->isDone())
	{
		sprite->runAction(_jumpBy.get());
	}	*/
}