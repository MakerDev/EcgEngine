#include "RuntimeActionCatalog.h"

std::map<string, REGISTER_FUNC_TYPE> RuntimeActionCatalog::_actionList =
{
	{"MoveX", MoveXFunctor::RegisterToRuntimeAction},
	{"JumpBy", RuntimeJumpByFunctor::RegisterToRuntimeAction},
	{"PlayAnimation", PlayAnimationFunctor::RegisterToRuntimeAction},
	{"SetSpriteFrame", SetSpriteFrameFunctor::RegisterToRuntimeAction},
};

//TODO : Return error code or throw exception
void RuntimeActionCatalog::AddAction(string actionName, RuntimeAction* runtimeAction, GameObject* target, const rapidjson::Value& actionObjectValue)
{
	if (_actionList.count(actionName) <= 0)
	{
		return;
	}

	const auto& functorRegisterFunction = _actionList[actionName];
	functorRegisterFunction(runtimeAction, target, actionObjectValue);
}
