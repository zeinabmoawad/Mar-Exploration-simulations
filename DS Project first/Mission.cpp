#include "Mission.h"

Mission::Mission(int Fd,Type Mt,float Tl,int Md,int S,int Id):Formulation_Day(Fd),Mission_Type(Mt),
	Target_Loaction(Tl), Mission_Duration(Md), Significance(S), ID(Id)
{
	WaitingDays=0;
	ExecutionDays=0;
	CompletionDay=0;
	Assigned_Rover=nullptr;
	
	//Priority is dirctlyproptional with Sig , Loc , Dur, and inverse with Form Day
	Priority=int((Significance*Target_Loaction*Mission_Duration)/Formulation_Day);
}

////////////////////////////////Gettres and Setters//////////////////////////////
int Mission::getFormulation_Day()const
{
	return Formulation_Day;
}

void Mission::SetWaitingDays(int d)
{
	WaitingDays=d;
}

int Mission:: GetWaitingDay() const
{
	return WaitingDays;
}

int Mission:: GetExcutionDay()const
{
	return ExecutionDays;
}

void Mission::setCompletionDay(int d)
{
	CompletionDay=d;
}

int Mission::getCompletionDay() const
{
	return CompletionDay;
}

void  Mission::settype(Type t1)
{
	Mission_Type=t1;
}

Type Mission::getMission_Type() const
{
	return Mission_Type;
}

float Mission::getTarget_Loaction() const
{
	return Target_Loaction;
}

int Mission::getMission_Duration()const
{
	return Mission_Duration;
}

int Mission:: getSignificance()const
{
	return Significance;
}

int Mission:: getID()const
{
	return ID;
}

void Mission::setAssigned_Rover(Rover*r)
{
	Assigned_Rover = r;
	if (r != nullptr)
	{
		//Mission_Duration: when mission will finish after reach target
		//Road Duartion *2
		ExecutionDays=int(Mission_Duration + ceil((Target_Loaction / r->getspeed()) * 2/ 25));//According to spped rover
	}
}

//get assigned rover 
Rover* Mission:: getAssigned_Rover()const
{
	return Assigned_Rover;
}

int Mission::Get_Priority() const
{
	return Priority;
}

//Destructor
Mission::~Mission(void)
{
}