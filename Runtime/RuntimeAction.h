#pragma once
#include <vector>
#include <functional>

#include "Trigger.h"

using namespace std;

class RuntimeAction
{
public:
	RuntimeAction(shared_ptr<Trigger> trigger) noexcept;

	void execute();
	void pushFunction(std::function<void(void)> function);
	const shared_ptr<Trigger> GetTrigger() const noexcept;

private:
	shared_ptr<Trigger> _trigger;
	std::vector<std::function<void(void)>> _functions;
};

