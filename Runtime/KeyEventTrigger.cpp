#include "KeyEventTrigger.h"

using namespace std;

unique_ptr<KeyEventTrigger> KeyEventTrigger::CreateFromJsonValue(const rapidjson::Value& keyEventTrigger)
{
	KeyEventType keyEventType = static_cast<KeyEventType>(keyEventTrigger["KeyEventType"].GetInt());
	EventKeyboard::KeyCode keycode = static_cast<EventKeyboard::KeyCode>(keyEventTrigger["Key"].GetInt());

	return make_unique<KeyEventTrigger>(keyEventType, keycode);
}

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
