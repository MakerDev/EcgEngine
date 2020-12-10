#pragma once
#include <vector>
#include <string>
#include <functional>

#include "VariableType.h"

class EcgVariable
{
public:
	void RegisterOnChangedCallback(std::function<void(EcgVariable*)> callback);

	EcgVariable(VariableType type);

	void SetFloatValue(float value);
	void SetIntegerValue(int value);
	void SetStringValue(const std::string& value);

	float GetFloatValue() const noexcept;
	int GetIntegerValue() const noexcept;
	const std::string& GetStringValue() const noexcept;

	std::string GetValueAsString() const;
	void SetValueByString(const std::string& value);

private:
	void notifyValueChanged();

private:
	VariableType _type;
	float _floatValue;
	int _integerValue;
	std::string _stringValue;

	std::vector <std::function<void(EcgVariable*)>> _onChangedCallbacks;
};

