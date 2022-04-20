#include "UI.h"

#include"MarsStation.h"
UI::UI(MarsStation*s)
{
	ms=s;
	silent=false;
	output.open("Output.txt");
	if(output.fail())
	{
		cout<<"Error to open output file"<<endl;
		exit(1);
	}

}

void UI:: Read_Data()
{
	int mode;
	int RM,RE,RP;//No of rovers for each type
	float SM,SE,SP;//speed of rovers
	int N;//No of times rover can be used
	int CE,CP,CM;//check up duration of rovers
	int AutoP;//number of days after which a mountainous mission is automatically promoted to emergency mission
	int NO_Events;
	char c1,c2;//Type of Event and Type of mission
	ifstream readfile;
	readfile.open("Test.txt");
	if(readfile.fail())
	{
		cout<<"Error"<<endl;
		exit(1);
	}
	while(!readfile.eof())
	{
		readfile>>mode;//to read mode of output console
		readfile>>RM>>RP>>RE;
		readfile>>SM>>SP>>SE;
		readfile>>N>>CM>>CP>>CE;
		ms->setMod(mode);//setiing mode of console
		ms->Read_Rovers(RM,SM,N,CM,Mountainous);
		ms->Read_Rovers(RP,SP,N,CP,Polar);
		ms->Read_Rovers(RE,SE,N,CE,Emergency);
		readfile>>AutoP;///////mountinaus to emergency
		ms->SetPromote(AutoP);
		readfile>>NO_Events;
		int ID,ED,MDUR,SIG;
		float TLOC;
		for(int i=0;i<NO_Events;i++)
		{
			readfile>>c1;
			if(c1=='F')
			{
				readfile>>c2;
				readfile>>ED>>ID>>TLOC>>MDUR>>SIG;//read event data
			}
			else //X,P event
			{
				readfile>>ED>>ID;
			}
			ms->Read_Event(c1,ID,ED,TLOC,MDUR,SIG,c2);
		}

	}
}
void UI::Print_OutputFile()
{
	output<<"CD\tID\tFD\tWD\tED\n";

	ms->PrintCompltedMissions();

	output<<"Missions: "<<ms->getTotalMission() <<"\t[M: "<<ms->getM_MissionCounter()<<", P: "<<ms->getP_MissionCounter()<<", E: "<<ms->getE_MissionCounter()<<"]\n";
	output<<"Rovers:  "<<ms->getTotalRovers() <<"  \t[M: "<<ms->getM_RoverCounter()<<", P: "<<ms->getP_RoverCounter()<<", E: "<<ms->getE_RoverCounter()<<"]\n"; 
	output<<"Avg Wait = "<<ms->get_Avg_Waiting()<<", Avg Exec = "<<ms->get_Avg_Execution()<<endl;
	output<<"Auto-promoted: "<<ms->getAutoPromoted_percentage()<<"%\n";
	output.close();
}
void UI::PrintMission(Mission*mis)
{
	output<<mis->getCompletionDay()<<"\t"<<mis->getID()<<"\t"<<mis->getFormulation_Day()<<"\t"<<mis->GetWaitingDay()<<"\t"<<mis->GetExcutionDay()<<endl;
}
void UI:: PrintInteractive(Mode m)
{

	switch (m)
	{
	case 0:
		while(cin.get()!='\n')
		{}
		break;
	case 1:
		{
			auto start = chrono::steady_clock::now();
			auto end = chrono::steady_clock::now();
			while(chrono::duration_cast<chrono::milliseconds>(end - start).count()<1000)
			{
				end = chrono::steady_clock::now();
			}
			break;
		}
	case 2:
		if(!silent)
		{
			cout<<"Silent Mode"<<endl; 
			cout<<"Simulation Starts..."<<endl;
			silent =true;
		}
		return;
	}
	cout<<"Current Day:"<<ms->getDay()<<endl;
	cout<<ms->getWaitingMissions()<<" Waiting Missions:";

	cout<<"[";
	ms->Print_emergency_Mission_list();
	cout<<"]";

	cout<<" (";
	ms->Print_polar_Mission_list();
	cout<<")";

	cout<<" {";
	ms->Print_mountainous_Mission_list();
	cout<<"}"<<endl<<"----------------------------------------------------------------------"<<endl;


	cout<<ms->getInExeution_Counter()<<" In-Execution Missions/Rovers: [";
	ms->Print_InExecution_list(Emergency);
	cout<<"]";
	cout<<"(";
	ms->Print_InExecution_list(Polar);
	cout<<")";

	cout<<"{";
	ms->Print_InExecution_list(Mountainous);
	cout<<"}"<<endl<<"--------------------------------------------------------------------------"<<endl;

	cout<<ms->getavailable_Rovers()<<" Available Rovers: ";
	cout<<"[";
	ms->Print_emergency_Rover_list();
	cout<<"]";

	cout<<"(";
	ms->Print_polar_Rover_list();
	cout<<")";

	cout<<"{";
	ms->Print_mountainous_Rover_list();
	cout<<"}"<<endl<<"-----------------------------------------------------------------------------------------"<<endl;


	cout<<ms->getrovers_incheckup()<<" In-Checkup Rovers: ";

	cout<<"[";
	ms->PrintCheckup_Rovers(Emergency);
	cout<<"]"<<"   ";

	cout<<"(";
	ms->PrintCheckup_Rovers(Polar);
	cout<<")"<<"   ";

	cout<<"{";
	ms->PrintCheckup_Rovers(Mountainous);
	cout<<"}"<<"   "<<endl<<"-------------------------------------------------------------------------"<<endl;


	cout<<ms->getComplete_Counter()<<" Completed Missions: ";
	cout<<"[";
	ms->PrintTotalCompletedMissions(Emergency);
	cout<<"]";

	cout<<"(";
	ms->PrintTotalCompletedMissions(Polar);
	cout<<")";

	cout<<"{";
	ms->PrintTotalCompletedMissions(Mountainous);
	cout<<"}"<<endl<<"-------------------------------------------------------------------------"<<endl;
	cout<<endl;

}
void UI::Print(string c)
{
	cout<<c;
}


void UI::PrintSilent(Mode m)
{
	if(m==Silent)
		cout<<"Simulation ends, Output file created"<<endl;
}

UI::~UI(void)
{
}
