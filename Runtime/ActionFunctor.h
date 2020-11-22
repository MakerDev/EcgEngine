#pragma once
#include <functional>
#include <rapidjson/document.h>

class ActionFunctor
{
public:
	virtual void Execute(float delta) = 0;
};

