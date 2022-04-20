#include "DeAssign.h"
#include"MarsStation.h"

DeAssign::DeAssign(MarsStation*mars,Mission*mission)
{
	mars_DeAssign=mars;
	mission_DeAssign=mission;
}
void DeAssign::Execute()
{
	Rover*rover=mission_DeAssign->getAssigned_Rover();//disconnect rover from mission
	mission_DeAssign->setAssigned_Rover(nullptr);
	mars_DeAssign->AddInCompletionList(mission_DeAssign,-1*mission_DeAssign->GetExcutionDay());///store In Completed list by priority ExcutionDays
	mars_DeAssign->IncrementCompleteCount();
	CheckUp*check=new CheckUp(mars_DeAssign,rover);
	check->Execute();
	delete check;
}

DeAssign::~DeAssign(void)
{
}

