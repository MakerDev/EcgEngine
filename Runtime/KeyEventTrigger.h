#pragma once
#include <rapidjson/document.h>

#include "Trigger.h"
#include "KeyEventTypes.h"
#include "cocos2d.h"

using namespace cocos2d;

class KeyEventTrigger : public Trigger
{
public:
	static std::unique_ptr<KeyEventTrigger> CreateFromJsonValue(const rapidjson::Value& keyEventTrigger);
	KeyEventTrigger(KeyEventType keyEventType, EventKeyboard::KeyCode keycode) noexcept;

	bool IsMatched(const EventContext& context) const;

private:
	KeyEventType _type;
	EventKeyboard::KeyCode _keyCode;
};

