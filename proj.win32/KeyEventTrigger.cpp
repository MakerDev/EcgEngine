#include "KeyEventTrigger.h"

KeyEventTrigger::KeyEventTrigger(KeyEventType keyEventType, EventKeyboard::KeyCode keycode)
	: _type(keyEventType), _keyCode(keycode)
{
}

bool KeyEventTrigger::isMatched(const EventContext& context)
{
	if (context.TriggerType != TriggerType::KeyboardEvent)
	{
		return false;
	}

	if (context.KeyCode == this->_keyCode && context.KeyEventType == this->_type)
	{
		return true;
	}

	return false;
}
