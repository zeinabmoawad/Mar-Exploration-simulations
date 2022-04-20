#include "PrompteEvent.h"
#include"MarsStation.h"

PrompteEvent::PrompteEvent(int e,int m):Event(e,m)
{
}
void PrompteEvent::Execute(MarsStation*m1)
{
	Mission *m;
	int x=0;
	m=m1->Find_in_mountainous_mission(Mission_Id,x);
	if (m != nullptr)
	{
		Promote*p=new Promote(m1,m);
		p->Execute();
		m1->Remove_From_Mountanious(x);
		delete p;
	}
	else
		return;
}
PrompteEvent::~PrompteEvent(void)
{
}
