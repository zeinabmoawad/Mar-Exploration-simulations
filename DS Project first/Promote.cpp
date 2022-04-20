#include "Promote.h"
#include"MarsStation.h"

Promote::Promote(MarsStation*mars,Mission*m)
{
	mars_Promote=mars;
	mission_Promote=m;
}
void Promote::Execute()
{
	//Change type from Mountainous to Emergency
	mission_Promote->settype(Emergency);
	mars_Promote->AddMission(mission_Promote);
}


Promote::~Promote(void)
{
}
