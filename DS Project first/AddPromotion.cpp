#include "AddPromotion.h"
#include"MarsStation.h"

AddPromotion::AddPromotion(MarsStation*m):AddEvent(m)
{
}

void AddPromotion::Excute(int id,int ed,float tl,int noday,int sf,char t )
{
	Event*ptr=new PrompteEvent(ed,id);
	ms->AddEventinList(ptr);
}
AddPromotion::~AddPromotion(void)
{
}
