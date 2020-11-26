#include <assert.h>

#include "VariableEngine.h"

std::unique_ptr<VariableEngine> VariableEngine::_instance = nullptr;

VariableEngine* VariableEngine::GetGlobalInstance()
{
	if (_instance == nullptr)
	{
		_instance = std::make_unique<VariableEngine>();
	}

	return _instance.get();
}

void VariableEngine::CreateNewVariableWithName(const std::string& name)
{
	assert(_variableTable.count(name) <= 0 && ("Variable " + name + "already exists").c_str());

	_variableTable.insert(std::make_pair(name, std::make_unique<EcgVariable>()));
}

EcgVariable* VariableEngine::GetVariableWithName(const std::string& name)
{
	if (_variableTable.count(name) <= 0)
	{
		return nullptr;
	}

	return _variableTable[name].get();
}

void VariableEngine::SetFloatValueWithName(const string& variableName, float value)
{
	_variableTable[variableName]->SetFloatValue(value);
}

void VariableEngine::SetIntegerValueWithName(const string& variableName, int value)
{
	_variableTable[variableName]->SetIntegerValue(value);
}

void VariableEngine::SetStringValueWithName(const string& variableName, const std::string& value)
{
	_variableTable[variableName]->SetStringValue(value);
}

float VariableEngine::GetFloatValueWithName(const string& variableName) const
{
	return _variableTable.at(variableName)->GetFloatValue();
}

int VariableEngine::GetIntegerValueWithName(const string& variableName) const
{
	return _variableTable.at(variableName)->GetIntegerValue();
}

const std::string& VariableEngine::GetStringValueWithName(const string& variableName) const
{
	return _variableTable.at(variableName)->GetStringValue();
}
