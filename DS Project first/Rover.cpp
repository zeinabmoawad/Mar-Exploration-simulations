#include "Rover.h"

Rover::Rover(Type type, int chd, float s,int c):RoverType(type),CheckupDuration(chd),Speed(s),NumberOfMissions_BeforeCheck(c)
{
	//intializng
	Performed_Mission_NO=0;
	OutFromCheckupDay=0;
	Rover_ID=++id;//ID
}

//Setters and Getters
Type Rover::GetType()const
{
	return RoverType;
}

int Rover::getID()const
{
	return Rover_ID;
}

float Rover::getspeed()const
{
	return Speed;
}

int Rover::GetCheckupDuration()const
{
	return CheckupDuration;
}

int Rover::GetNumberOfMissions_BeforeCheck()const// To Know No.of Missions Performed By This Rover
{
	return NumberOfMissions_BeforeCheck;
}


//get no of performed missions by rover till no 
int Rover::getPerformed_Mission_NO() const
{
	return Performed_Mission_NO;
}

//increment no of performmed
void Rover::IncrementNo_Of_Missions()
{
	Performed_Mission_NO++;
}

//setting day required toget out from Chechup list
void Rover::SetOutFromCheckupDay(int d)
{
	OutFromCheckupDay=d;
}

int Rover::GetOutFromCheckupDay()const
{
	return OutFromCheckupDay;
}

Rover::~Rover()
{
}
//Static Data member intialization
int Rover::id=0;