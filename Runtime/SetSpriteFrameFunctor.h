#pragma once
#include "GameObject.h"
#include "RuntimeAction.h"
#include "ActionFunctor.h"

class SetSpriteFrameFunctor : public ActionFunctor
{
public:
	static std::shared_ptr<ActionFunctor> Create(GameObject* target, const rapidjson::Value& actionObjectValue);
	static void RegisterToRuntimeAction(RuntimeAction* runtimeAction, GameObject* target, const rapidjson::Value& actionObjectValue);
	virtual void Execute(float delta) override;

private:
	VisualComponent* _visualComponent;
	string _spriteName;
};

