#pragma once
#include <map>

#include "MoveX.h"

#define REGISTER_FUNC_TYPE function<void(GameObject*, RuntimeAction* runtimeAction, const rapidjson::Value&)>

class RuntimeActionFactoryConatiner
{
public:
	static void Register(string actionName, REGISTER_FUNC_TYPE actionFactory);

private:
	//TODO : 이름 - 등록 함수 페어를 여기에 등록해서 그냥 바로 함수 이름을 키로 쓸 수 있게 바꾸기
	static std::map<string, REGISTER_FUNC_TYPE> _actionList;
};