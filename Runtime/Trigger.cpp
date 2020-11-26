#include "Trigger.h"

bool Trigger::GetLastMatchResult() const noexcept
{
	return _lastMatchResult;
}

void Trigger::RegisterMatchResultChangedCallback(std::function<void(bool)> callback)
{
	_onLastMatchResultChangedCallbacks.push_back(callback);
}

bool Trigger::SetLastMatchResult(bool result)
{
	const bool isResultChanged = result != _lastMatchResult;
	_lastMatchResult = result;

	if (isResultChanged)
	{
		for (auto& callback : _onLastMatchResultChangedCallbacks)
		{
			callback(result);
		}
	}

	return isResultChanged;
}
