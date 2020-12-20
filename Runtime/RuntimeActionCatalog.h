#pragma once
#include <map>

#include "RuntimeJumpByFunctor.h"
#include "MoveXFunctor.h"
#include "MoveYFunctor.h"
#include "PlayAnimationFunctor.h"
#include "SetSpriteFrameFunctor.h"
#include "SetVariableValueFunctor.h"
#include "IncreaseVariableValueFunctor.h"
#include "ConditionalActionFunctor.h"

#define REGISTER_FUNC_TYPE function<void(RuntimeAction*, GameObject*, const rapidjson::Value&)>

class RuntimeActionCatalog
{
public:
	static void AddAction(string actionName, RuntimeAction* runtimeAction, GameObject* target, const rapidjson::Value& actionObjectValue);

private:
	//TODO : �̸� - ��� �Լ� �� ���⿡ ����ؼ� �׳� �ٷ� �Լ� �̸��� Ű�� �� �� �ְ� �ٲٱ�
	static std::map<string, REGISTER_FUNC_TYPE> _actionList;
};