#pragma once
#include <map>

#include "RuntimeJumpByFunctor.h"
#include "MoveXFunctor.h"
#include "PlayAnimationFunctor.h"
#include "SetSpriteFrameFunctor.h"

#define REGISTER_FUNC_TYPE function<void(RuntimeAction*, GameObject*, const rapidjson::Value&)>

class RuntimeActionCatalog
{
public:
	static void AddAction(string actionName, RuntimeAction* runtimeAction, GameObject* target, const rapidjson::Value& actionObjectValue);

private:
	//TODO : 이름 - 등록 함수 페어를 여기에 등록해서 그냥 바로 함수 이름을 키로 쓸 수 있게 바꾸기
	static std::map<string, REGISTER_FUNC_TYPE> _actionList;
};