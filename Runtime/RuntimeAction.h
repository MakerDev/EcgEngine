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
	void PushFunction(std::function<void(void)> function);
	void PushFunctor(unique_ptr<ActionFunctor> functor);
	const Trigger& GetTrigger() const noexcept;

private:
	unique_ptr<Trigger> _trigger;
	//TODO: replace this with Functors for stateful actions. i.e) Jump
	std::vector<std::function<void(void)>> _functions;
	std::vector<unique_ptr<ActionFunctor>> _functors;

};

