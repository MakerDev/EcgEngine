#pragma once
#include <rapidjson/document.h>

#include "VariableEngine.h"
#include "GameObject.h"
#include "ConditionType.h"

class VariableCondition
{
public:
	static unique_ptr<VariableCondition> CreateFromJsonValue(const rapidjson::Value& value);
	//To offer more overloads for each vaeluType to support fast comparision
	VariableCondition(GameObject& target, const std::string& variableName, ConditionType conditionType, const string& valueToCompare);

	//For global variable
	VariableCondition(const std::string& variableName, ConditionType conditionType, const string& valueToCompare);

	bool IsMatched() const;

private:
	ConditionType _conditionType;	
	string _valueToCompare;
	EcgVariable* _targetVariable;
};

