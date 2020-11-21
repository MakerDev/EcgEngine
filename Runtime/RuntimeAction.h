#pragma once
#include <vector>
#include <functional>

#include "Trigger.h"
#include "ActionFunctor.h"

using namespace std;

class RuntimeAction
{
public:
	RuntimeAction(unique_ptr<Trigger> trigger) noexcept;

	void Execute();
	void PushFunctor(unique_ptr<ActionFunctor> functor);
	const Trigger& GetTrigger() const noexcept;

private:
	unique_ptr<Trigger> _trigger;
	std::vector<unique_ptr<ActionFunctor>> _functors;
};

