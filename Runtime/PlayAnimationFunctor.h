#pragma once
#include "ActionFunctor.h"
#include "RuntimeAction.h"
#include "GameObject.h"

class PlayAnimationFunctor : public ActionFunctor
{
public:
	void static RegisterToRuntimeAction(RuntimeAction* runtimeAction, GameObject* target, const rapidjson::Value& actionObjectValue);
	virtual void Execute(float delta) override;

	PlayAnimationFunctor(const string& animationName);

private:
	VisualComponent* _visualComponent;
	string _animationName;
};


