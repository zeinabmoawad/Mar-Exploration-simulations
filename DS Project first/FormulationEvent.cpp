#include "FormulationEvent.h"
#include"MarsStation.h"

FormulationEvent::FormulationEvent(int e,int m,Type t,float ta,int no,int s):Event(e,m)
{
	mission_type=t;
	Target_Location=ta;
	Number_ToFulfill=no;
	Significance=s;
}

void FormulationEvent::Execute(MarsStation*s1)
{
	//create a new mission
	Mission*m1=new Mission(Event_Day,mission_type,Target_Location,Number_ToFulfill,Significance,Mission_Id);
	// add the new mission in waiting list of marsstation
	s1->AddMission(m1);
	
}

FormulationEvent::~FormulationEvent(void)
{
}
