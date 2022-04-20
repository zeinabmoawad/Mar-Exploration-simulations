#pragma once
#include"Event.h"
#include"Defs.h"
class MarsStation;
class FormulationEvent:public Event
{
	Type mission_type;
	float Target_Location;
	int Number_ToFulfill;
	int Significance;
public:
	FormulationEvent(int e,int m,Type t,float ta,int no,int s);
	virtual void Execute(MarsStation*);
	virtual ~FormulationEvent(void);
};

