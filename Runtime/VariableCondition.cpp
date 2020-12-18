#include "VariableCondition.h"
#include "EngineManager.h"

unique_ptr<VariableCondition> VariableCondition::CreateFromJsonValue(const rapidjson::Value& value)
{
	string targetObjectName = value["TargetObjectName"].GetString();
	auto targetVariableName = value["TargetVariableName"].GetString();
	const auto conditionType = static_cast<ConditionType>(value["ConditionType"].GetInt());
	string valueToCompare = value["ValueToCompare"].GetString();

	if (targetObjectName.empty())
	{
		return make_unique<VariableCondition>(targetVariableName, conditionType, valueToCompare);
	}

	auto defaultLayer = EngineManager::GetInstance()->GetDefaultLayer();

	assert(defaultLayer != nullptr && "Default layer is null");


	if (targetObjectName.empty())
	{
		return make_unique<VariableCondition>(targetVariableName, conditionType, valueToCompare);
	}

	auto targetObject = defaultLayer->FindGameObject(targetObjectName);

	assert(targetObject != nullptr && "Failed to find target object");

	return make_unique<VariableCondition>(*targetObject, targetVariableName, conditionType, valueToCompare);
}

VariableCondition::VariableCondition(GameObject& target, const std::string& variableName, ConditionType conditionType, const string& valueToCompare)
	:_conditionType(conditionType), _valueToCompare(valueToCompare)
{
	const auto localVariableEngine = target.GetLocalVariableEngine();
	_targetVariable = localVariableEngine->GetVariableWithName(variableName);
}

VariableCondition::VariableCondition(const std::string& variableName, ConditionType conditionType, const string& valueToCompare)
	:_conditionType(conditionType), _valueToCompare(valueToCompare)
{
	const auto globalVariableEngine = VariableEngine::GetGlobalInstance();
	_targetVariable = globalVariableEngine->GetVariableWithName(variableName);
}

bool VariableCondition::IsMatched() const
{
	bool isMatched = true;

	auto value = _targetVariable->GetValueAsString();

	if (_targetVariable->GetType() == VariableType::typeString)
	{
		return value.compare(_valueToCompare) == 0;
	}

	//For number comparision
	const double valueDouble = std::stod(value);
	const double valueToCompareDouble = std::stod(_valueToCompare);

	switch (_conditionType)
	{
	case ConditionType::EqualTo:
		isMatched = valueToCompareDouble == valueDouble;
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
