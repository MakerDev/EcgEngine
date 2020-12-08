#include "JsonHelper.h"


rapidjson::GenericArray<true, rapidjson::Value> JsonHelper::GetConstArray(const rapidjson::Value& value)
{
	return value["$values"].GetArray();
}
