#include "RuntimeAction.h"

RuntimeAction::RuntimeAction(unique_ptr<Trigger> trigger) noexcept
	: _trigger(std::move(trigger))
{
}

void RuntimeAction::Execute()
{
	for (auto& functor : _functors)
	{
		functor->Execute();
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
