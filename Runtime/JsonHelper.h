#pragma once
#include <rapidjson/document.h>

class JsonHelper
{
public:
	static rapidjson::GenericArray<true, rapidjson::Value> GetConstArray(const rapidjson::Value& value);
};

