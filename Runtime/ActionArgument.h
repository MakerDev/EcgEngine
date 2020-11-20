#pragma once
#include <string>
#include <rapidjson/document.h>
using namespace std;

class ActionArgument
{
public:
	ActionArgument(const rapidjson::Value& argumentValue);
	const string& GetValue() const;
private:
	string _name;
	string _type;
	string _value;
};