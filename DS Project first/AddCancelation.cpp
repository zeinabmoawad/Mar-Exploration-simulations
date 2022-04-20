#include "AddCancelation.h"
#include"MarsStation.h"

AddCancelation::AddCancelation(MarsStation*m):AddEvent(m)
{

}

void AddCancelation::Excute(int id,int ed,float tl,int noday,int sf,char t )
{
	Event*ptr=new CancelEvent(ed,id);
	ms->AddEventinList(ptr);
}
AddCancelation::~AddCancelation(void)
{
}
