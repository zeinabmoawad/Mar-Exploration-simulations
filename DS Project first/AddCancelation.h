#pragma once
#include"AddEvent.h"
#include"CancelEvent.h"
class MarsStation;
class AddCancelation: public AddEvent
{
public:
	AddCancelation(MarsStation*m);
	void Excute(int id,int ed,float tl=0,int noday=0,int sf=0,char t=0 );
	~AddCancelation(void);
};

