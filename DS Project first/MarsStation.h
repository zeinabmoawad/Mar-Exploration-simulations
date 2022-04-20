#pragma once
#include"LinkedQueue.h"
#include"Mission.h"
#include"Rover.h"
#include"LinkedPriorityQueue.h"
#include"Defs.h"
#include"LinkedList.h"
#include<string>

//////////////forward declerations
class AddRover;
class Event;
class FormulationEvent;
class CancelEvent;
class UI;
class AddEvent;
class AddFormulation;
class AddCancelation;
class AddPromotion;
class Assign;
class Promote;
class DeAssign;
class MarsStation
{
	//Events List
	LinkedQueue<Event*> Event_list;

	//waiting Missions
	LinkedQueue<Mission*>polar_Mission_list;
	LinkedList<Mission*>mountainous_Mission_list;
	LinkedPriorityQueue<Mission*>emergency_Mission_list;

	//Avaliable Rovers
	LinkedQueue<Rover*>PolarRover_list;
	LinkedQueue<Rover*>MounainousRover_list;
	LinkedQueue<Rover*>EmergencyRover_list;

	LinkedPriorityQueue<Mission*>InExecution_list;//In execution missions list
	LinkedPriorityQueue<Mission*>Completed_list;//Completed Today
	LinkedQueue<Mission*>TotalCompletedMissions;//Completed from start of simulation

	//Roveers checkup Lists
	LinkedQueue<Rover*>EmergencyRover_checkuplist;
	LinkedQueue<Rover*>MountaionousRover_checkuplist;
	LinkedQueue<Rover*>PolarRover_checkuplist;



	UI*Interface;
	Mode mode;//Mode of Console
	int day;//Current Day
	int promote;//Auto promote limit

	////////////Counters to get no of missions for each type
	int M_MissionCounter;//mountanious mission counter
	int E_MissionCounter;//emergency mission counter
	int P_MissionCounter;//polar mission counter
	int AutoPromoted_Counter;

	int InExeution_Counter;
	int Complete_Counter;

	////////////Counter to get no of rovers for each type
	int M_RoverCounter;//mountanious rover counter
	int E_RoverCounter;//emergency rover counter
	int P_RoverCounter;//polar rover counter
	int rovers_incheckup;


	//time counters
	int Total_Waiting_Time;
	int Total_Execution_Time;

	//Private Functions
	void Check_EventList();
	void Check_CompletedMissions();
	void Check_CompletedRovers();
	void AddInTotalCompletedMissions();
	void Assign_Mission_To_Rover();

	void deleteRoverList();
	void deletecompletedMissionslist();
	void AutoP();
	bool End_of_Days();


	//printing Functions
	template<class T>
	void PrintPriorityQueue(LinkedPriorityQueue<T>);

	template<class T>
	void PrintLinkedList(LinkedList<T>);

	template<class T>
	void PrintQueue(LinkedQueue<T>);

public:
	MarsStation();

	//setting mode of Console
	void setMod(int m);

	//Read Data From UI
	void Read_Data_UI();
	void Read_Rovers(int num,float s,int nummission,int check,Type T);
	void Read_Event(char etype,int id,int ed,float tl=0,int noday=0,int sf=0,char t=0 );

	//Add in lists
	void AddEventinList(Event*ptr);
	void AddRoverinlist(Rover* R);

	void AddMission(Mission*);
	void AddInExecution(Mission*,int);
	void AddInCompletionList(Mission*,int);
	void AddRoverinCheckup(Rover* R);

	//Mountainous Functions
	Mission* Find_in_mountainous_mission(int id,int &x);
	void DeleteMountMission(Mission*,int);
	void Remove_From_Mountanious(int);


	//Every Day Executed Functions
	bool EveryDay();

	int getDay()const;
	void SetPromote(int);

	//get mission counters 
	int getM_MissionCounter() const;
	int getE_MissionCounter() const;
	int getP_MissionCounter() const;
	int getTotalMission() const;
	int getWaitingMissions()const;
	int getInExeution_Counter()const;
	void IncrementCompleteCount();
	int getComplete_Counter() const;

	//get rovers counter
	int getM_RoverCounter() const;
	int getE_RoverCounter() const;
	int getP_RoverCounter() const;
	int getTotalRovers() const;


	int getrovers_incheckup() const;
	int getavailable_Rovers()const;
	float get_Avg_Waiting()const;
	float get_Avg_Execution()const;
	float getAutoPromoted_percentage()const;



	//print Missions List waiting
	void Print_emergency_Mission_list();
	void Print_polar_Mission_list();
	void Print_mountainous_Mission_list();

	//print Rovers List waiting
	void Print_emergency_Rover_list();
	void Print_polar_Rover_list();
	void Print_mountainous_Rover_list();

	void Print_InExecution_list(Type);
	void PrintTotalCompletedMissions(Type);

	void PrintCheckup_Rovers(Type type);
	//print completed missions
	void PrintCompltedMissions();


	~MarsStation(void);	
};

