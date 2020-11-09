#include "EventContext.h"


EventContext* EventContext::CreateKeyboardContext(
	::KeyEventType keyEventype, cocos2d::EventKeyboard::KeyCode keyCode)
{
	auto context = new EventContext();

	context->TriggerType = TriggerType::KeyboardEvent;
	context->KeyEventType = keyEventype;
	context->KeyCode = keyCode;

	return context;
}
