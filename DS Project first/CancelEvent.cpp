#include "CancelEvent.h"
#include"MarsStation.h"

CancelEvent::CancelEvent(int e,int m):Event(e,m)
{
}
void CancelEvent::Execute(MarsStation*m1)
{
	int x;
	Mission*ToDeleteMission=m1->Find_in_mountainous_mission(Mission_Id,x);
	if(ToDeleteMission)
		m1->DeleteMountMission(ToDeleteMission,x);
}
CancelEvent::~CancelEvent(void)
{
}
