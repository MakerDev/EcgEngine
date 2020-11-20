#pragma once
#include "ActionFunctor.h"
#include "RuntimeJumpBy.h"
using namespace std;
class RuntimeJumpByFunctor : public ActionFunctor
{
public:
	static void AddActionFromJson(GameObject* targetGameObject, RuntimeAction* runtimeAction, const rapidjson::Value& actionValueObject);
	RuntimeJumpByFunctor(GameObject* target, float duration, int height);
	virtual void Execute() override;

private:
	unique_ptr<Action> _jumpBy;
	GameObject* _target;
	bool _isFirstJump = true;
};

