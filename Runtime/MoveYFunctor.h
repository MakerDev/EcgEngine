#pragma once
#include "ActionFunctor.h"
#include "RuntimeAction.h"
#include "GameObject.h"

class MoveYFunctor: public ActionFunctor
{
public:
	void static RegisterToRuntimeAction(RuntimeAction* runtimeAction, GameObject* target, const rapidjson::Value& actionObjectValue);
	virtual void Execute(float delta) override;

	MoveYFunctor(GameObject* target, float delta);
private:
	function<void(void)> _moveFunction;
	GameObject* _target;
	float _delta;
};


