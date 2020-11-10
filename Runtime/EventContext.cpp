#include "EventContext.h"

EventContext::EventContext(::KeyEventType keyEventype, cocos2d::EventKeyboard::KeyCode keyCode)
	:TriggerType(TriggerType::KeyboardEvent), KeyEventType(keyEventype), KeyCode(keyCode)
{
}
