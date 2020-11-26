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

	void Execute(float delta);
	void PushFunctor(unique_ptr<ActionFunctor> functor);
	const Trigger& GetTrigger() const noexcept;
	Trigger& GetTrigger() noexcept;

private:
	//TODO : Conditional execution needs to be added
	unique_ptr<Trigger> _trigger;
	std::vector<unique_ptr<ActionFunctor>> _functors;
};

