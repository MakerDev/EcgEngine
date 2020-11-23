#pragma once
#include <map>
#include <memory>
#include <string>
#include <functional>
#include <vector>

#include "EcgVariable.h"

class VariableEngine
{
public:
	static VariableEngine* GetInstance();

	void CreateNewVariableWithName(const std::string& name);
	EcgVariable* GetVariableWithName(const std::string& name);

private:
	static std::unique_ptr<VariableEngine> _instance;
	std::map<std::string, std::unique_ptr<EcgVariable>> _varableTable;
};

