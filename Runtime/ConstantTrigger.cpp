#include "ConstantTrigger.h"


//False is available for event driven actions
ConstantTrigger::ConstantTrigger(bool isMatched)
	:_isMatched(isMatched)
{

}


bool ConstantTrigger::IsMatched(const EventContext& context)
{
	return _isMatched;
}

TriggerType ConstantTrigger::GetType() const
{
	return TriggerType::Constant;
}
