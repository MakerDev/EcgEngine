#pragma once
#include "GameObject.h"

class RuntimeJumpBy : ActionInterval
{
public:
	static void AddActionFromJson(GameObject* targetGameObject, RuntimeAction* runtimeAction, const rapidjson::Value& actionValueObject);
	/**
	 * @param time In seconds.
	 */
	virtual void update(float time) override;

	/**
	 * initializes the action
	 * @param duration in seconds
	 */
	bool initWithDuration(float duration, const Vec2& position, float height, int jumps);


	static void JumpByAction(GameObject* target, float duration, int height);
protected:
	Vec2           _startPosition;
	Vec2           _delta;
	float           _height;
	int             _jumps;
	Vec2           _previousPos;
	JumpBy* _action = nullptr;
	bool _isInitialJump = true;
};

