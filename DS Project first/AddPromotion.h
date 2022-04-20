#pragma once
#include"AddEvent.h"
#include"PrompteEvent.h"
class MarsStation;
class AddPromotion:public AddEvent
{
public:
	AddPromotion(MarsStation*m);
	virtual void Excute(int id,int ed,float tl=0,int noday=0,int sf=0,char t=0 );
	~AddPromotion(void);
};

