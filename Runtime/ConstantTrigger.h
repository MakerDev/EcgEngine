#pragma once
#include "Trigger.h"

class ConstantTrigger : public Trigger
{
public:
	ConstantTrigger(bool isMatched);
	
	virtual bool IsMatched(const EventContext& context) override;
	virtual TriggerType GetType() const override;

private:
	bool _isMatched = true;
};

