#include "EcgVariable.h"

void EcgVariable::RegisterOnChangedCallback(std::function<void(EcgVariable*)> callback)
{
	_onChangedCallbacks.push_back(callback);
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

const std::string& EcgVariable::GetStringValue() const
{
	return _stringValue;
}

void EcgVariable::notifyValueChanged()
{
	for (auto& callback : _onChangedCallbacks)
	{
		callback(this);
	}
}
