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

bool KeyEventTrigger::IsMatched(const EventContext& context)
{
	if (context.TriggerType != TriggerType::KeyboardEvent || context.KeyCode != _keyCode)
	{
		return false;
	}

	bool result = false;

	if (_type == KeyEventType::Down)
	{
		if (context.KeyEventType == KeyEventType::Down)
		{			
			result = true;
		}
		else if (context.KeyEventType != KeyEventType::Released)
		{
			result = false;
		}
	}

	SetLastMatchResult(result);

	return result;
}

KeyEventType KeyEventTrigger::GetKeyEventType() const
{
	return _type;
}

TriggerType KeyEventTrigger::GetType() const
{
	return TriggerType::KeyboardEvent;
}
