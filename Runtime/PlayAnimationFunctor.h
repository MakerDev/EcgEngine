#pragma once
#include "ActionFunctor.h"
#include "RuntimeAction.h"
#include "GameObject.h"

class PlayAnimationFunctor : public ActionFunctor
{
public:
	void static RegisterToRuntimeAction(RuntimeAction* runtimeAction, GameObject* target, const rapidjson::Value& actionObjectValue);
	virtual void Execute(float delta) override;

	PlayAnimationFunctor(GameObject* target, const string& animationName);
	
private:
	void SetToIdle(bool result);

private:
	GameObject* _target;
	VisualComponent* _visualComponent;
	string _animationName;
};


