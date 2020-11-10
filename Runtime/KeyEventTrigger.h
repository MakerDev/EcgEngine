#pragma once

#include "Trigger.h"
#include "KeyEventTypes.h"
#include "cocos2d.h"

using namespace cocos2d;

class KeyEventTrigger : public Trigger
{
public:
	KeyEventTrigger(KeyEventType keyEventType, EventKeyboard::KeyCode keycode) noexcept;

	bool IsMatched(const EventContext& context) const;
	
private:
	KeyEventType _type;
	EventKeyboard::KeyCode _keyCode;
};

