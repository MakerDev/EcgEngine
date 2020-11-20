#include "RuntimeAction.h"

RuntimeAction::RuntimeAction(unique_ptr<Trigger> trigger) noexcept
	: _trigger(std::move(trigger))
{
}

void RuntimeAction::Execute()
{
	for (auto i = _functions.begin(); i != _functions.end(); i++)
	{
		(*i)();
	}
}

void RuntimeAction::PushFunctiona(std::function<void(void)> function)
{
	_functions.push_back(function);
}

const Trigger& RuntimeAction::GetTrigger() const noexcept
{
	return *_trigger;
}
