#pragma once
#include"Event.h"
class MarsStation;
class CancelEvent:public Event
{
public:
	CancelEvent(int e,int m);
	virtual void Execute(MarsStation*);
	virtual ~CancelEvent(void);
};

