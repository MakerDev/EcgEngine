#include "RuntimeAction.h"

RuntimeAction::RuntimeAction(shared_ptr<Trigger> trigger) noexcept
	: _trigger(trigger)
{
}

void RuntimeAction::execute()
{
	for (auto i = _functions.begin(); i != _functions.end(); i++)
	{
		//Execute all functions
		(*i)();
	}
}

void RuntimeAction::pushFunction(std::function<void(void)> function)
{
	_functions.push_back(function);
}

const shared_ptr<Trigger> RuntimeAction::GetTrigger() const noexcept
{
	return _trigger;
}
