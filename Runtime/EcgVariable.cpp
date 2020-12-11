#include "EcgVariable.h"

void EcgVariable::RegisterOnChangedCallback(std::function<void(EcgVariable*)> callback)
{
	_onChangedCallbacks.push_back(callback);
}

EcgVariable::EcgVariable(const std::string& name, VariableType type)
	:_name(name), _type(type)
{
}

const std::string& EcgVariable::GetName() const noexcept
{
	return _name;
}

void EcgVariable::SetFloatValue(float value)
{
	_floatValue = value;
	this->notifyValueChanged();
}

void EcgVariable::SetIntegerValue(int value)
{
	_integerValue = value;
	this->notifyValueChanged();
}

void EcgVariable::SetStringValue(const std::string& value)
{
	_stringValue = value;
	this->notifyValueChanged();
}

float EcgVariable::GetFloatValue() const noexcept
{
	return _floatValue;
}

int EcgVariable::GetIntegerValue() const noexcept
{
	return _integerValue;
}

const std::string& EcgVariable::GetStringValue() const noexcept
{
	return _stringValue;
}

std::string EcgVariable::GetValueAsString() const
{
	switch (_type)
	{
	case VariableType::typeInteger:
		return std::to_string(_integerValue);
	case VariableType::typeFloat:
		return std::to_string(_floatValue);
	case VariableType::typeString:
		return _stringValue;
	default:
		break;
	}
}

void EcgVariable::SetValueByString(const std::string& value)
{
	switch (_type)
	{
	case VariableType::typeInteger:
		_integerValue = std::stoi(value);
		break;

	case VariableType::typeFloat:
		_floatValue = std::stof(value);
		break;

	case VariableType::typeString:
		_stringValue = value;
		break;

	default:
		break;
	}
}

void EcgVariable::notifyValueChanged()
{
	for (auto& callback : _onChangedCallbacks)
	{
		callback(this);
	}
}
