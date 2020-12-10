#pragma once
#include <vector>
#include <functional>

#include "Trigger.h"
#include "ActionFunctor.h"

using namespace std;

class RuntimeAction
{
public:
	RuntimeAction();
	RuntimeAction(unique_ptr<Trigger> trigger) noexcept;

	virtual void Execute(float delta);
	void PushFunctor(shared_ptr<ActionFunctor> functor);
	const Trigger& GetTrigger() const noexcept;
	Trigger& GetTrigger() noexcept;

private:
	//TODO : Conditional execution needs to be added
	unique_ptr<Trigger> _trigger;
	std::vector<shared_ptr<ActionFunctor>> _functors;
};

