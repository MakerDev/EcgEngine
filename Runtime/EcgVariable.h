#pragma once
#include <vector>
#include <string>
#include <functional>

class EcgVariable
{
public:
	void RegisterOnChangedCallback(std::function<void(EcgVariable*)> callback);

	void SetFloatValue(float value);
	void SetIntegerValue(int value);
	void SetStringValue(const std::string& value);

	float GetFloatValue() const noexcept;
	int GetIntegerValue() const noexcept;
	const std::string& GetStringValue() const;

private:
	void notifyValueChanged();

private:
	float _floatValue;
	int _integerValue;
	std::string _stringValue;

	std::vector <std::function<void(EcgVariable*)>> _onChangedCallbacks;
};

