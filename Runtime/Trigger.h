#pragma once

#include "EventContext.h"

//TODO : consider to change this class to interface
class Trigger
{
public:
	virtual bool IsMatched(const EventContext& context) = 0;
	bool GetLastMatchResult() const noexcept;
	void RegisterMatchResultChangedCallback(std::function<void(bool)> callback);
	virtual TriggerType GetType() const = 0;

protected:
	bool SetLastMatchResult(bool result);

protected:
	bool _lastMatchResult = false;
	std::vector<std::function<void(bool)>> _onLastMatchResultChangedCallbacks;
};

