#pragma once
#include <rapidjson/document.h>

#include "Trigger.h"
#include "KeyEventType.h"
#include "cocos2d.h"

using namespace cocos2d;

class KeyEventTrigger : public Trigger
{
public:
	static std::unique_ptr<KeyEventTrigger> CreateFromJsonValue(const rapidjson::Value& keyEventTrigger);
	KeyEventTrigger(KeyEventType keyEventType, EventKeyboard::KeyCode keycode) noexcept;
	virtual TriggerType GetType() const override;
	bool IsMatched(const EventContext& context) override;

	KeyEventType GetKeyEventType() const;

private:
	KeyEventType _type;
	EventKeyboard::KeyCode _keyCode;
};

