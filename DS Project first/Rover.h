#pragma once
#include"Defs.h"
#include<iostream>
using namespace std;

class Rover
{
private:
	Type RoverType;//Mounationus,Emergency,Polar
	int Rover_ID;

	int CheckupDuration;//Duartion for Rover in Checkup
	int OutFromCheckupDay;//Day of geting out from checkup list
	
	int NumberOfMissions_BeforeCheck;//no of missions for rover to need check up
	int Performed_Mission_NO;//counter of performed missions till now

	float Speed;


	//Staic Data member for Id of Riovers
	static int id;//0 1 2
public:
	Rover(Type, int, float,int);

	//Getters and Setters
	Type GetType()const;
	int getID()const;

	float getspeed()const;

	int GetCheckupDuration()const;
	int GetNumberOfMissions_BeforeCheck()const;
	
	//used for checking checkup need
	int getPerformed_Mission_NO() const;
	void IncrementNo_Of_Missions();//increament no of performed missions till now

	//Check up Duration in Check up lisys 
	void SetOutFromCheckupDay(int);
	int GetOutFromCheckupDay()const;

	~Rover();
};