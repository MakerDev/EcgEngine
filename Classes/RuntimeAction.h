#pragma once
#include <vector>
#include <functional>

#include "Trigger.h"

class RuntimeAction
{
public:
	RuntimeAction(Trigger* trigger);
	virtual ~RuntimeAction();

	void execute();
	void pushFunction(std::function<void(void)> function);
	Trigger* GetTrigger() const;

private:
	Trigger* _trigger;
	std::vector<std::function<void(void)>> _functions;
};

