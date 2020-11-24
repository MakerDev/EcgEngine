#pragma once
#include <vector>

#include "cocos2d.h"
#include "TriggerType.h"
#include "KeyEventType.h"

//This class is aggregator of all posible event context infomation
class EventContext
{
public:
	EventContext(::KeyEventType keyEventype,
		cocos2d::EventKeyboard::KeyCode keyCode);

public:
	TriggerType TriggerType;

	//Keyboard event related fields
	KeyEventType KeyEventType;
	cocos2d::EventKeyboard::KeyCode KeyCode;

	float TimeDelta = 0.33F;
};

