#pragma once
#include <vector>
#include <string>
#include <functional>
#include <rapidjson/document.h>
#include <memory>
#include "VariableType.h"

class EcgVariable
{
public:
	void RegisterOnChangedCallback(std::function<void(EcgVariable*)> callback);

	EcgVariable(const std::string& name, VariableType type);

	const std::string& GetName() const noexcept;

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
	std::string _name;
	VariableType _type;
	float _floatValue = 0;
	int _integerValue = 0;
	std::string _stringValue;

	std::vector <std::function<void(EcgVariable*)>> _onChangedCallbacks;
};

