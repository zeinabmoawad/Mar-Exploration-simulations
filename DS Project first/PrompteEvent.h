#pragma once
#include"Event.h"
#include"Promote.h"
class MarsStation;
class PrompteEvent:public Event
{
public:
	PrompteEvent(int e,int m);
	virtual void Execute(MarsStation*);
	virtual ~PrompteEvent(void);
};

