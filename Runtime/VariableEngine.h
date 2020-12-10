#pragma once
#include <map>
#include <memory>
#include <string>
#include <functional>
#include <vector>

#include "EcgVariable.h"
#include "VariableType.h"

using namespace std;

class VariableEngine
{
public:
	static VariableEngine* GetGlobalInstance();

	void CreateNewVariableWithName(const std::string& name, VariableType type);
	EcgVariable* GetVariableWithName(const std::string& name);

	//Helpers
	void SetFloatValueWithName(const string& variableName, float value);
	void SetIntegerValueWithName(const string& variableName, int value);
	void SetStringValueWithName(const string& variableName, const std::string& value);

	float GetFloatValueWithName(const string& variableName) const;
	int GetIntegerValueWithName(const string& variableName) const;
	const std::string& GetStringValueWithName(const string& variableName) const;

private:
	static std::unique_ptr<VariableEngine> _instance;
	std::map<std::string, std::unique_ptr<EcgVariable>> _variableTable;
};

