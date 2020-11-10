#include "KeyEventTrigger.h"

KeyEventTrigger::KeyEventTrigger(KeyEventType keyEventType, EventKeyboard::KeyCode keycode) noexcept
	: _type(keyEventType), _keyCode(keycode)
{
}

bool KeyEventTrigger::IsMatched(const EventContext& context) const
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
