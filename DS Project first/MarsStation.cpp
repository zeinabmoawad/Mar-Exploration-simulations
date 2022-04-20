#include "MarsStation.h"
#include"Event.h"
#include"FormulationEvent.h"
#include"CancelEvent.h"
#include"UI.h"
#include"AddRover.h"
#include"AddEvent.h"
#include"AddFormulation.h"
#include"AddCancelation.h"
#include"AddPromotion.h"
#include"Assign.h"
#include"Promote.h"
#include"DeAssign.h"

//////////////////constuctor
MarsStation::MarsStation():Total_Waiting_Time(0),Total_Execution_Time(0),AutoPromoted_Counter(0),InExeution_Counter(0),rovers_incheckup(0),Complete_Counter(0)
{
	day=1;
	Interface=new UI(this);
	M_MissionCounter=0;
	E_MissionCounter=0;
	P_MissionCounter=0;
	M_RoverCounter=0;
	E_RoverCounter=0;
	P_RoverCounter=0;
}
/////////////////////Read Data from UI
void MarsStation::Read_Data_UI()//Function to call UI class to read data from file
{
	Interface->Read_Data();
}
/////////////////////////set mode of console
void MarsStation::setMod(int m)
{
	switch (m)
	{
	case 0://interacive
		mode=Interactive;
		break;
	case 1:///stepbystep
		mode=Stepbystep;
		break;
	case 2://silent
		mode=Silent;
		break;
	}
}
///////////////////get Data of Each rover from UI
void MarsStation::Read_Rovers(int num,float s,int nummission,int check,Type T)
{
	for(int i=0;i<num;i++)
	{
		AddRover*ptr=new AddRover(this);
		ptr->Execute(s,nummission,check,T);
		switch(T)
		{
		case 0:
			E_RoverCounter++;
			break;
		case 1:
			M_RoverCounter++;
			break;
		case 2:
			P_RoverCounter++;
		}
		delete ptr;
	}
}
//////////////////////////get Data of Each Event from UI
void MarsStation::Read_Event(char etype,int id,int ed,float tl,int noday,int sf,char t )
{
	AddEvent *ptr;
	if(etype=='F')
		ptr=new AddFormulation(this);
	else if(etype=='X')
		ptr=new AddCancelation(this);
	else if(etype=='P')
		ptr=new AddPromotion(this);
	ptr->Excute(id,ed,tl,noday,sf,t);
	delete ptr;
}
//////////////////////////////////////To add event in the list 
void  MarsStation::AddEventinList(Event*ptr)
{
	Event_list.enqueue(ptr);
}
//////////////////////////////////Add Rover in its suitable list of avaliable rovers
void MarsStation::AddRoverinlist(Rover* R)
{
	if(R->GetType()==0)//emergency
		EmergencyRover_list.enqueue(R);
	else if(R->GetType()==1)//mountainous
		MounainousRover_list.enqueue(R);
	else if(R->GetType()==2) //polar
		PolarRover_list.enqueue(R);
}
//////////////////////////////////////Add Mission in its suitable list of waiting
void MarsStation::AddMission(Mission*m)
{
	Type t=m->getMission_Type();
	if(t==0)
	{
		emergency_Mission_list.enqueue(m,m->Get_Priority());
		E_MissionCounter++;
	}
	else if(t==1)
	{
		mountainous_Mission_list.insert(mountainous_Mission_list.getLength()+1,m);
		M_MissionCounter++;
	}
	else if(t==2)
	{
		polar_Mission_list.enqueue(m);
		P_MissionCounter++;
	}
}
/////////////////////////////////Add mission in In-Execusion list given its priority 
void MarsStation::AddInExecution(Mission*mtoexecute,int priority)
{
	InExecution_list.enqueue(mtoexecute, priority);
}
//////////////////////////////////////Add mission in Completed list given its priority 
void MarsStation::AddInCompletionList(Mission*m,int p)
{
	Completed_list.enqueue(m,p);
}
////////to make mission that complete in same day be first in list before the next day completed mission
void MarsStation::AddInTotalCompletedMissions()
{
	Mission*m;
	while(!Completed_list.isEmpty())
	{
		Completed_list.dequeue(m);
		TotalCompletedMissions.enqueue(m);
	}

}
//////////////////////////////Add Rovers in the =suitable checkup list
void MarsStation::AddRoverinCheckup(Rover* R)
{
	if(R->GetType()==0)//Emergency
		EmergencyRover_checkuplist.enqueue(R);
	else if(R->GetType()==1)//Mountainous
		MountaionousRover_checkuplist.enqueue(R);
	else if(R->GetType()==2)//polar 
		PolarRover_checkuplist.enqueue(R);
	rovers_incheckup++;
}
//////////////////////////////////////////Gets mountainous mission of given id
Mission* MarsStation:: Find_in_mountainous_mission(int id,int &x)
{
	x=0;
	Mission*mtemp;
	Mission* ptr=nullptr;
	for(int i=1;i<=mountainous_Mission_list.getLength();i++)
	{
		mtemp=mountainous_Mission_list.getEntry(i);
		if(id==mtemp->getID())
		{
			ptr=mtemp;
			x=i;
		}
	}
	return ptr;
}
/////////////////////////////////////Tto Delete Mountanious Mission
void MarsStation::DeleteMountMission(Mission*m,int x)
{
	mountainous_Mission_list.remove(x);
	M_MissionCounter--;
	delete m;
}
///////////////////////////////////////remove Mounatoinous mission from mountainous_Mission List given its ID
void MarsStation::Remove_From_Mountanious(int x)
{
	mountainous_Mission_list.remove(x);
	M_MissionCounter--;
}
//ckeck if no waiting missions or unexeuted events or uncompleted mission or rovers in checkuplists
bool MarsStation::End_of_Days()
{
	if(mountainous_Mission_list.isEmpty()&&polar_Mission_list.isEmpty()&&emergency_Mission_list.isEmpty()&&Event_list.isEmpty()&&InExecution_list.isEmpty()&&MountaionousRover_checkuplist.isEmpty()&&EmergencyRover_checkuplist.isEmpty()&&PolarRover_checkuplist.isEmpty())
		return true;
	return false;
}

//Every Day Work 
bool MarsStation::EveryDay()
{
	Check_EventList();//Check Events for Today
	Check_CompletedMissions();//Check completed Missions Today
	Check_CompletedRovers();//Check Rovers to become Available again 
	Assign_Mission_To_Rover();//Assigning Waiting Missions To avaliable Rovers
	AutoP();//Check Mountainous Missions To be Auto Promoted
	Interface->PrintInteractive(mode);//Print Console According to Mode
	if(End_of_Days()) //if end of Exploration ==>Print Output file 
	{
		Interface->PrintSilent(mode);//Silent Mode
		Interface->Print_OutputFile();//Output File
	}
	day++;//go to next day
	return(!End_of_Days());//return if end of Exploration
}
////////////////////////////////////////////////set AutoP read from UI
void MarsStation::SetPromote(int p)
{
	promote = p;
}
///////////////Return counter of mounatnious mission
int MarsStation::getM_MissionCounter() const
{
	return M_MissionCounter;
}
///////////////Return counter of polar mission
int MarsStation::getP_MissionCounter() const
{
	return P_MissionCounter;
}
///////////////Return counter of emergency mission
int MarsStation::getE_MissionCounter() const
{
	return E_MissionCounter;
}
//////////////Return counter of all missions
int MarsStation::getTotalMission() const
{
	return (E_MissionCounter+P_MissionCounter+M_MissionCounter);
}
//
int MarsStation::getInExeution_Counter()const
{
	return InExeution_Counter;
}
///////increase Complete
void MarsStation::IncrementCompleteCount()
{
	Complete_Counter++;
}
///////get total no of Completed Missions
int MarsStation::getComplete_Counter() const
{
	return Complete_Counter;
}
int MarsStation::getWaitingMissions()const
{
	return (getTotalMission()-InExeution_Counter-Complete_Counter);
}
/////////////////////Return counter of mountanious rover
int MarsStation::getM_RoverCounter() const
{
	return M_RoverCounter;
}
//////////////////////Return counter of emergency rover
int MarsStation:: getE_RoverCounter() const
{
	return E_RoverCounter;
}
////////////////////////Return counter of polar rover
int MarsStation:: getP_RoverCounter() const
{
	return P_RoverCounter;
}
/////////////////////////Return counter of Rovers in check up
int MarsStation::getrovers_incheckup() const
{
	return rovers_incheckup;
}
//////////////////////////Return counter of Avaliavble Rovers
int MarsStation::getavailable_Rovers()const
{
	return getTotalRovers()-rovers_incheckup-InExeution_Counter;//total rovers-rovers in checkup-no of rovers assigned to in execution missions
}

////////////////////////Return counter of all rover
int MarsStation:: getTotalRovers() const
{
	return (M_RoverCounter+P_RoverCounter+E_RoverCounter);
}

//cal Average waiting 
float MarsStation::get_Avg_Waiting()const
{
	return (float(Total_Waiting_Time)/getTotalMission());
}
//cal Average Execution
float MarsStation::get_Avg_Execution()const
{
	return (float(Total_Execution_Time)/getTotalMission());
}

/////////////get pecentage of autopromoted Mountainous missions
float MarsStation::getAutoPromoted_percentage()const
{
	return(float(AutoPromoted_Counter)*100/(M_MissionCounter+AutoPromoted_Counter));
}
///////////////////////////////Return Day
int MarsStation::getDay()const
{
	return day;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////Print Functions///////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Print Waiting emergency Missions
void MarsStation::Print_emergency_Mission_list()
{
	PrintPriorityQueue(emergency_Mission_list);
}
////////////Print Waiting Polar Missions
void MarsStation:: Print_polar_Mission_list()
{
	PrintQueue(polar_Mission_list);
}
////////////Print Waiting _mountainous Missions
void MarsStation::Print_mountainous_Mission_list()
{
	PrintLinkedList(mountainous_Mission_list);
}
/////////////////////////////Print Avaliable Emergency Rovers 
void MarsStation::Print_emergency_Rover_list()
{
	PrintQueue(EmergencyRover_list);
}
//////Print Avaliable Polar Rovers 
void MarsStation::Print_polar_Rover_list()
{
	PrintQueue(PolarRover_list);
}
//////Print Avaliable Mountainous Rovers 
void MarsStation::Print_mountainous_Rover_list()
{
	PrintQueue(MounainousRover_list);
}
///////////////////////////////Print Missions in execution and their rovers
void MarsStation::Print_InExecution_list(Type t)
{
	Mission* x;
	LinkedPriorityQueue<Mission*>ids;
	int count=0;
	LinkedPriorityQueue<Mission*>temp;
	while(!InExecution_list.isEmpty())
	{
		InExecution_list.dequeue(x);
		if(x->getMission_Type()==t)
		{
			ids.enqueue(x,-1*x->getID());
			count++;
		}
		temp.enqueue(x,-1*x->getCompletionDay());
	}
	InExecution_list=temp;
	Mission* id;

	while(!ids.isEmpty())
	{
		bool col=true;
		ids.dequeue(id);
		count--;
		Interface->Print(to_string(id->getID()));
		Interface->Print("/");
		Interface->Print(to_string((id->getAssigned_Rover())->getID()));
		if(count!=0)
			Interface->Print(",");
	}
}
///All completed missions from start of Simulatiopn
void MarsStation::PrintTotalCompletedMissions(Type type)
{
	
	Mission* x;
	LinkedQueue<Mission*>temp;
	LinkedQueue<Mission*>temp_print;
	while (!TotalCompletedMissions.isEmpty())
	{
		TotalCompletedMissions.dequeue(x);
		if(x->getMission_Type()==type)
		{
			temp_print.enqueue(x);
		}
		temp.enqueue(x);
	}
	TotalCompletedMissions=temp;
	PrintQueue(temp_print);
}
//Print Rovers in checkup List
void MarsStation::PrintCheckup_Rovers(Type type)
{
	if(type==0)//take copy of it not itself
		PrintQueue(EmergencyRover_checkuplist);
	else if(type==1)
		PrintQueue(MountaionousRover_checkuplist);
	else if(type==2)
		PrintQueue(PolarRover_checkuplist);
}
MarsStation::~MarsStation(void)
{
	deleteRoverList();
	deletecompletedMissionslist();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////PrivateFunctions/////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////To Check EventList
void MarsStation::Check_EventList()
{ 
	Event*x;
	if(Event_list.peek(x))
	{
		while(day==x->getEvent_Day())
		{
			Event_list.dequeue(x);
			x->Execute(this);
			if(!Event_list.peek(x))
				break;
		}
	}
}
///////////////////////////////////To Check completeMission list
void MarsStation::Check_CompletedMissions()
{
	Mission*x;

	while((InExecution_list.peek(x))&&(x->getCompletionDay()==day))
	{

		InExecution_list.dequeue(x);
		DeAssign*d=new DeAssign(this,x);
		d->Execute();
		Total_Execution_Time+=x->GetExcutionDay();
		InExeution_Counter--;
		delete d; 
	}
	//insert soreted by ED
	AddInTotalCompletedMissions();
}
//////////////////////////////////////To Check completeRover list
void MarsStation::Check_CompletedRovers()
{
	Rover*r;
	//mountainnous
	while(MountaionousRover_checkuplist.peek(r)&&(r->GetOutFromCheckupDay()==day))
	{
		MountaionousRover_checkuplist.dequeue(r);
		rovers_incheckup--;
		AddRoverinlist(r);
	}

	//Emergency
	while(EmergencyRover_checkuplist.peek(r)&&(r->GetOutFromCheckupDay()==day))
	{
		EmergencyRover_checkuplist.dequeue(r);
		rovers_incheckup--;
		AddRoverinlist(r);
	}

	//polar
	while(PolarRover_checkuplist.peek(r)&&(r->GetOutFromCheckupDay()==day))
	{
		PolarRover_checkuplist.dequeue(r);
		rovers_incheckup--;
		AddRoverinlist(r);
	}
}
//////////////////////////////To Assign Mission To Rover
void MarsStation::Assign_Mission_To_Rover()
{
	Rover* r;
	Mission* m;
	Assign*toassign;
	//check waiting lists
	while (!emergency_Mission_list.isEmpty())
	{
		if (!EmergencyRover_list.isEmpty())
			EmergencyRover_list.dequeue(r);

		else if (!MounainousRover_list.isEmpty())
			MounainousRover_list.dequeue(r);

		else if (!PolarRover_list.isEmpty())
			PolarRover_list.dequeue(r);

		else
			return;
		//Suitable rover==>r
		emergency_Mission_list.dequeue(m);
		toassign=new Assign(this);
		toassign->Execute(r,m);
		Total_Waiting_Time+=m->GetWaitingDay();
		InExeution_Counter++;
		delete toassign;
	}
	while (!polar_Mission_list.isEmpty())
	{
		if (!PolarRover_list.isEmpty())
			PolarRover_list.dequeue(r);

		else
			break;
		polar_Mission_list.dequeue(m);
		toassign=new Assign(this);
		toassign->Execute(r,m);
		Total_Waiting_Time+=m->GetWaitingDay();
		InExeution_Counter++;
		delete toassign;
	}
	while (!mountainous_Mission_list.isEmpty())
	{
		if (!MounainousRover_list.isEmpty())
			MounainousRover_list.dequeue(r);

		else if (!EmergencyRover_list.isEmpty())
			EmergencyRover_list.dequeue(r);

		else
			return;
		m=mountainous_Mission_list.getEntry(1);
		mountainous_Mission_list.remove(1);
		toassign=new Assign(this);
		toassign->Execute(r,m);
		Total_Waiting_Time+=m->GetWaitingDay();
		InExeution_Counter++;
		delete toassign;
	}
}
/////////////////////////////To Delete Rover
void MarsStation::deleteRoverList()
{
	Rover*r;
	while(!MounainousRover_list.isEmpty())
	{
		MounainousRover_list.dequeue(r);
		delete r;
	}
	while(!EmergencyRover_list.isEmpty())
	{
		EmergencyRover_list.dequeue(r);
		delete r;
	}
	while(!PolarRover_list.isEmpty())
	{
		PolarRover_list.dequeue(r);
		delete r;
	}
}

//////////////////////////////Delete Completed missions list
void MarsStation::deletecompletedMissionslist()
{
	Mission*m;
	while(!TotalCompletedMissions.isEmpty())
	{
		TotalCompletedMissions.dequeue(m);
		delete m;
	}
}
///////////////////////////////To Promote Mountainous Mission Automatic
void MarsStation::AutoP()
{
	Mission* m;
	for(int i=1;i<=mountainous_Mission_list.getLength();i++)
	{
		m=mountainous_Mission_list.getEntry(i);
		if((day-m->getFormulation_Day())==promote)
		{
			Promote*p=new Promote(this,m);
			p->Execute();
			mountainous_Mission_list.remove(i);
			M_MissionCounter--;
			AutoPromoted_Counter++;
			delete p;
		}
	}
}
////////////////////////////////////Call UI to print details of each completed missions
void MarsStation::PrintCompltedMissions()
{
	while(!TotalCompletedMissions.isEmpty())
	{
		Mission*m;
		TotalCompletedMissions.dequeue(m);
		Interface->PrintMission(m);
		delete m;
	}
}
/////////////////////////////////////////////Print Priority Queue 
template<class T>
void MarsStation::PrintPriorityQueue(LinkedPriorityQueue<T> ptr)
{
	T x;
	LinkedPriorityQueue<int>ids;
	int count=0;
	LinkedPriorityQueue<T>temp;
	while(!ptr.isEmpty())
	{
		ptr.dequeue(x);
		ids.enqueue(x->getID(),-1*x->getID());
		count++;
		temp.enqueue(x,x->Get_Priority());
	}
	ptr=temp;
	int id;
	while(!ids.isEmpty())
	{
		bool col=true;
		ids.dequeue(id);
		count--;
		Interface->Print(to_string(id));
		if(count!=0)
			Interface->Print(",");
	}
}
///////////////////////////////////////////Print Linked List
template<class T>
void MarsStation::PrintLinkedList(LinkedList<T> L)
{
	T m;
	LinkedPriorityQueue<int>ids;
	int count=0;
	LinkedList<T>temp;
	while(!L.isEmpty())
	{
		m=L.getEntry(1);
		L.remove(1);
		ids.enqueue(m->getID(),-1*m->getID());
		count++;
		temp.insert(mountainous_Mission_list.getLength()+1,m);
	}
	L=temp;
	int id;
	while(!ids.isEmpty())
	{
		bool col=true;
		ids.dequeue(id);
		count--;
		Interface->Print(to_string(id));
		if(count!=0)
			Interface->Print(",");
	}
}
/////////////////////////////////////////////Linked Queue
template<class T>
void  MarsStation::PrintQueue(LinkedQueue<T>ptr)
{
	T x;
	LinkedPriorityQueue<int>ids;
	int count=0;
	LinkedQueue<T>temp;
	while(!ptr.isEmpty())
	{
		ptr.dequeue(x);
		ids.enqueue(x->getID(),-1*x->getID());
		count++;
		temp.enqueue(x);
	}
	ptr=temp;
	int id;
	while(!ids.isEmpty())
	{
		bool col=true;
		ids.dequeue(id);
		Interface->Print(to_string(id));
		count--;
		if(count!=0)
			Interface->Print(",");
	}
}