#include "VariableCondition.h"



inline VariableCondition::VariableCondition(GameObject& target, const std::string& variableName, ConditionType conditionType, const string& valueToCompare)
	:_conditionType(conditionType), _valueToCompare(valueToCompare)
{
	const auto localVariableEngine = target.GetLocalVariableEngine();
	_targetVariable = localVariableEngine->GetVariableWithName(variableName);
}

inline VariableCondition::VariableCondition(const std::string& variableName, ConditionType conditionType, const string& valueToCompare)
	:_conditionType(conditionType), _valueToCompare(valueToCompare)
{
	const auto globalVariableEngine = VariableEngine::GetGlobalInstance();
	_targetVariable = globalVariableEngine->GetVariableWithName(variableName);
}

bool VariableCondition::IsMatched() const
{
	bool isMatched = true;

	auto value = _targetVariable->GetValueAsString();

	//For number comparision
	const double valueDouble = std::stod(value);
	const double valueToCompareDouble = std::stod(_valueToCompare);

	switch (_conditionType)
	{
	case ConditionType::EqualTo:
		isMatched = _valueToCompare.compare(value) == 0;
		break;

	case ConditionType::GreaterOrEqualTo:
		isMatched = valueToCompareDouble >= valueDouble;
		break;

	case ConditionType::GreaterThan:
		isMatched = valueToCompareDouble > valueDouble;
		break;

	case ConditionType::LessOrEqualTo:
		isMatched = valueToCompareDouble <= valueDouble;
		break;

	case ConditionType::LessThan:
		isMatched = valueToCompareDouble < valueDouble;
		break;

	default:
		break;
	}

	return isMatched;
}
