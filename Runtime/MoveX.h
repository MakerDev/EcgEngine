#pragma once
#include <rapidjson/document.h>

#include "RuntimeAction.h"
#include "GameObject.h"

using namespace std;

class MoveX
{
public:
	static void MoveX::AddActionFromJson(GameObject* targetGameObject, RuntimeAction* runtimeAction, const rapidjson::Value& actionValueObject);
};

