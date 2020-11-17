#pragma once
#include <string>


using namespace std;

class ActionArgument
{
public:
	ActionArgument();

private:
	string _name;
	string _type;
	string _value;
};