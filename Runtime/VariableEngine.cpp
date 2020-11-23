#include <assert.h>

#include "VariableEngine.h"

std::unique_ptr<VariableEngine> VariableEngine::_instance = nullptr;

VariableEngine* VariableEngine::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = std::make_unique<VariableEngine>();
	}

	return _instance.get();
}


void VariableEngine::CreateNewVariableWithName(const std::string& name)
{
	assert(_varableTable.count(name) <= 0 && ("Variable " + name + "already exists").c_str());

	_varableTable.insert(std::make_pair(name, std::make_unique<EcgVariable>()));
}

EcgVariable* VariableEngine::GetVariableWithName(const std::string& name)
{
	assert(_varableTable.count(name) > 0 && ("Variable " + name + "doesn't exits").c_str());

	return _varableTable[name].get();
}
