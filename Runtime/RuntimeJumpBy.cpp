#include <rapidjson/document.h>

#include "RuntimeActionTemplates.h"
#include "ActionArgument.h"
#include "RuntimeJumpBy.h"

/// <summary>
/// Json param:
/// -duration
/// -height
/// </summary>
/// <param name="targetGameObject"></param>
/// <param name="runtimeAction"></param>
/// <param name="actionValueObject"></param>
void RuntimeJumpBy::AddActionFromJson(GameObject* targetGameObject, RuntimeAction* runtimeAction, const rapidjson::Value& actionValueObject)
{
	const auto& arguments = actionValueObject["Arguments"].GetArray();

	//Arg1 : Duration to height repeat
	const ActionArgument durationArg(arguments[0]);
	const float duration = stof(durationArg.GetValue());

	const ActionArgument heightArg(arguments[3]);
	const float height = stoi(heightArg.GetValue());

	std::function<void(void)> jumpFunc =
		std::bind(RuntimeActionTemplates::JumpBy, targetGameObject, duration, height);

	runtimeAction->PushFunctiona(jumpFunc);
}

void RuntimeJumpBy::update(float t)
{
	// parabolic jump (since v0.8.2)
	if (_target)
	{
		float frac = fmodf(t * _jumps, 1.0f);
		float y = _height * 4 * frac * (1 - frac);
		y += _delta.y * t;

		float x = _delta.x * t;
#if CC_ENABLE_STACKABLE_ACTIONS
		Vec2 currentPos = _target->getPosition();

		Vec2 diff = currentPos - _previousPos;
		_startPosition = diff + _startPosition;

		Vec2 newPos = _startPosition + Vec2(x, y);
		_target->setPosition(newPos);

		_previousPos = newPos;
#else
		_target->setPosition(_startPosition + Vec2(x, y));
#endif // !CC_ENABLE_STACKABLE_ACTIONS
	}

}

bool RuntimeJumpBy::initWithDuration(float duration, const Vec2& position, float height, int jumps)
{
	CCASSERT(jumps >= 0, "Number of jumps must be >= 0");
	if (jumps < 0)
	{
		log("JumpBy::initWithDuration error: Number of jumps must be >= 0");
		return false;
	}

	if (ActionInterval::initWithDuration(duration) && jumps >= 0)
	{
		_delta = position;
		_height = height;
		_jumps = jumps;

		return true;
	}

	return false;
}
