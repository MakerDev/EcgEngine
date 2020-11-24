#include "VariableEventTrigger.h"

VariableEventTrigger::VariableEventTrigger(VariableEventType variableEventType, const std::string& variableName) noexcept
	:_variableEventType(variableEventType), _variableName(variableName)
{
}