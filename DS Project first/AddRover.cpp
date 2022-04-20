#include "AddRover.h"
#include"MarsStation.h"

AddRover::AddRover(MarsStation*m)
{
	ms=m;
}

void AddRover::Execute(float s,int num,int c,Type T)
{
	Rover* r=new Rover(T,c,s,num);// RoverType,CheckupDuration,Speed,NumberOfMissions_BeforeCheck
	ms->AddRoverinlist(r);//add rover in lists  Mars
}
AddRover::~AddRover(void)
{
}
