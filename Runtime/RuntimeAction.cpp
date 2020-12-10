#include "RuntimeAction.h"
#include "ConstantTrigger.h"

RuntimeAction::RuntimeAction()
{
	this->_trigger = make_unique<ConstantTrigger>(true);
}

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

void RuntimeAction::PushFunctor(shared_ptr<ActionFunctor> functor)
{
	_functors.push_back(functor);
}

const Trigger& RuntimeAction::GetTrigger() const noexcept
{
	return *_trigger;
}

Trigger& RuntimeAction::GetTrigger() noexcept
{
	return *_trigger;
}
