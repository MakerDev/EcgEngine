#pragma once
#include "ActionFunctor.h"
#include "RuntimeJumpBy.h"
using namespace std;
class RuntimeJumpByFunctor : public ActionFunctor
{
public:
	static shared_ptr<ActionFunctor> Create(GameObject* targetGameObject, const rapidjson::Value& actionValueObject);

	static void RegisterToRuntimeAction(RuntimeAction* runtimeAction, GameObject* targetGameObject, const rapidjson::Value& actionValueObject);
	RuntimeJumpByFunctor(GameObject* target, float duration, int height);
	virtual void Execute(float delta) override;

private:
	unique_ptr<Action> _jumpBy;
	GameObject* _target;
	bool _isFirstJump = true;

};

