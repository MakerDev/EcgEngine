#pragma once
#include <vector>
#include <functional>

#include "Trigger.h"

using namespace std;

class RuntimeAction
{
public:
	RuntimeAction(unique_ptr<Trigger> trigger) noexcept;

	void Execute();
	void PushFunctiona(std::function<void(void)> function);
	const Trigger& GetTrigger() const noexcept;

private:
	unique_ptr<Trigger> _trigger;
	std::vector<std::function<void(void)>> _functions;
};

