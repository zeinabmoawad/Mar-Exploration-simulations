#include "Assign.h"
#include"MarsStation.h"

Assign::Assign(MarsStation*m)
{
	mtoassign=m;
}
void Assign::Execute(Rover* r, Mission* m)
{
	m->setAssigned_Rover(r);///////connect rover to mission
	r->IncrementNo_Of_Missions();//To know no of times it assigned to mission for checkup
	m->SetWaitingDays(mtoassign->getDay()-m->getFormulation_Day());///calculate waiting day
	m->setCompletionDay(mtoassign->getDay()+m->GetExcutionDay());///calculate ExcutionDays
	int x = m->getCompletionDay();
	mtoassign->AddInExecution(m,-1*x);///store InExecution list by priority ExcutionDays
}
Assign::~Assign(void)
{
}
