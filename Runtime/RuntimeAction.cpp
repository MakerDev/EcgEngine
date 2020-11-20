#include "RuntimeAction.h"

RuntimeAction::RuntimeAction(unique_ptr<Trigger> trigger) noexcept
	: _trigger(std::move(trigger))
{
}

void RuntimeAction::Execute()
{
	//TODO : Integrate functions to functors
	for (auto i = _functions.begin(); i != _functions.end(); i++)
	{
		(*i)();
	}

	for (auto& functor : _functors)
	{
		functor->Execute();
	}
}

void RuntimeAction::PushFunction(std::function<void(void)> function)
{
	_functions.push_back(function);
}

void RuntimeAction::PushFunctor(unique_ptr<ActionFunctor> functor)
{
	_functors.push_back(std::move(functor));
}

const Trigger& RuntimeAction::GetTrigger() const noexcept
{
	return *_trigger;
}
