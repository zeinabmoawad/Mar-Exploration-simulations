#pragma once
#include"Defs.h"
#include"Rover.h"
//class Rover;
class Mission
{
	int Formulation_Day;//Day Mission is formed
	int WaitingDays;//Days Waiting in Waiting list
	int ExecutionDays;//Days for mision to be exceuted in Execusion list
	int CompletionDay; //Day at which Mission in completed

	Type Mission_Type;
	float Target_Loaction;
	int Mission_Duration;
	int Significance;
	int ID;//Missions's ID
	int Priority;
	Rover* Assigned_Rover;//Rover for performing mission

public:
	Mission(int,Type,float,int,int,int);

	//DaysFunctions
	int getFormulation_Day()const;
	void SetWaitingDays(int);
	int GetWaitingDay() const;
	int GetExcutionDay()const;
	void setCompletionDay(int);
	int getCompletionDay() const;

	//getters and Setters
	void settype(Type);
	Type getMission_Type() const;
	float getTarget_Loaction() const;
	int getMission_Duration()const;
	int getSignificance()const;
	int getID()const;

	//Rover
	void setAssigned_Rover(Rover*);
	Rover* getAssigned_Rover()const;


	int Get_Priority() const;

	~Mission(void);	
};

