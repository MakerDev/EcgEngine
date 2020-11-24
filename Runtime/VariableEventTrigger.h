#pragma once
#include <rapidjson/document.h>
#include <memory>
#include <string>

#include "VariableEventType.h"

class VariableEventTrigger
{
public:
	static std::unique_ptr<VariableEventTrigger> CreateFromJsonValue(const rapidjson::Value& keyEventTrigger);
	VariableEventTrigger(VariableEventType variableEventType, const std::string& variableName) noexcept;

private:
	VariableEventType _variableEventType;
	std::string _variableName;
};