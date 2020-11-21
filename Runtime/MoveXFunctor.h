#pragma once
#include "ActionFunctor.h"
#include "RuntimeAction.h"
#include "GameObject.h"

class MoveXFunctor: public ActionFunctor
{
public:
	void static RegisterToRuntimeAction(RuntimeAction* runtimeAction, GameObject* target, const rapidjson::Value& actionObjectValue);
	virtual void Execute() override;

	MoveXFunctor(function<void(void)> flipFuction, function<void(void)> moveFunction);
private:
	function<void(void)> _flipFunction;
	function<void(void)> _moveFunction;
};

