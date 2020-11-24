#include "RuntimeAction.h"

RuntimeAction::RuntimeAction(unique_ptr<Trigger> trigger) noexcept
	: _trigger(std::move(trigger))
{
}

void RuntimeAction::Execute(float delta)
{
	for (auto& functor : _functors)
	{
		functor->Execute(delta);
	}
}

void RuntimeAction::PushFunctor(unique_ptr<ActionFunctor> functor)
{
	_functors.push_back(std::move(functor));
}

const Trigger& RuntimeAction::GetTrigger() const noexcept
{
	return *_trigger;
}

Trigger& RuntimeAction::GetTrigger() noexcept
{
	return *_trigger;
}
