#include "AddFormulation.h"
#include"MarsStation.h"
AddFormulation::AddFormulation(MarsStation *m):AddEvent(m)
{

}

void AddFormulation::Excute(int id,int ed,float tl,int noday,int sf,char t)
{
	Type t1;
	if(t=='M')
		t1=Mountainous;
	else if(t=='P')
		t1=Polar;
	else if(t=='E')
		t1=Emergency;
	Event*ptr=new FormulationEvent(ed,id,t1,tl,noday,sf);
	ms->AddEventinList(ptr);
}
AddFormulation::~AddFormulation(void)
{
}
