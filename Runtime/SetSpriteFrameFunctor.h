#pragma once
#include "GameObject.h"
#include "RuntimeAction.h"
#include "ActionFunctor.h"

class SetSpriteFrameFunctor: public ActionFunctor
{
public:
	void static RegisterToRuntimeAction(RuntimeAction* runtimeAction, GameObject* target, const rapidjson::Value& actionObjectValue);

	virtual void Execute(float delta) override;

private:
	VisualComponent* _visualComponent;
	string _spriteName;
};

