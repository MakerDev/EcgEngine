#pragma once
#include "EventContext.h"
#include "TriggerTypes.h"

//TODO : consider to change this class to interface
class Trigger
{
public:
	virtual bool IsMatched(const EventContext& context) const = 0;
};

