#pragma once
#include "ActionFunctor.h"
#include "GameObject.h"

class RuntimeJumpBy : public ActionInterval
{
public:
	static unique_ptr<RuntimeJumpBy> Create(float duration, int height);
	/**
	 * @param time In seconds.
	 */
	virtual void update(float time) override;

	/**
	 * initializes the action
	 * @param duration in seconds
	 */

	bool initWithDuration(float duration, const Vec2& position, float height, int jumps);
protected:
	Vec2           _startPosition;
	Vec2           _delta;
	float           _height;
	int             _jumps;
	Vec2           _previousPos;
};

