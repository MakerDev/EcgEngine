#include "RuntimeAction.h"

RuntimeAction::RuntimeAction(Trigger* trigger) 
	: _trigger(trigger)
{
}

RuntimeAction::~RuntimeAction()
{
	delete _trigger;
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

Trigger* RuntimeAction::GetTrigger() const
{
	return _trigger;
}
