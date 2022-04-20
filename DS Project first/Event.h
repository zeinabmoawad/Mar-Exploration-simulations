#pragma once
class MarsStation;
class Event
{
protected:
	int Event_Day;
	int Mission_Id;
public:
	Event(int event,int m):Event_Day(event),Mission_Id(m)
	{}
	virtual void Execute(MarsStation*)=0;
	int getEvent_Day(){ return Event_Day;}
	virtual ~Event(void){}
};

