#pragma once

#include "Trigger.h"
#include "KeyEventTypes.h"
#include "cocos2d.h"

using namespace cocos2d;

class KeyEventTrigger : public Trigger
{
public:
	KeyEventTrigger(KeyEventType keyEventType, EventKeyboard::KeyCode keycode);
	
	virtual bool isMatched(const EventContext& context) override;

private:
	KeyEventType _type;
	EventKeyboard::KeyCode _keyCode;

};

