#include"Mission.h"
#include"Rover.h"
#include"Defs.h"
#include"MarsStation.h"
#include"UI.h"
int main()
{
	try{
		//Creating an instance of MarsStation
		MarsStation s;
		s.Read_Data_UI();

		while(s.EveryDay())//loop while not end of days to execute evreyday()
		{}


		//Dummy
		int c;
		cin>>c;
	}
	catch(...){
		cout<<"Exception";
	}
}