#pragma once
#include "VariableEngine.h"
#include "GameObject.h"
#include "ConditionType.h"

class VariableCondition
{
public:
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

