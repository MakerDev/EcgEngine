#include "ActionArgument.h"

ActionArgument::ActionArgument(const rapidjson::Value& argumentValue)
{
	_name = argumentValue["Name"].GetString();
	_type = argumentValue["Type"].GetString();
	_value = argumentValue["Value"].GetString();
}

const string& ActionArgument::GetValue() const
{
	return _value;
}
