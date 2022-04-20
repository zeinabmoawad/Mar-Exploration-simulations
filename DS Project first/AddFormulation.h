#pragma once
#include"AddEvent.h"
#include"FormulationEvent.h"
class MarsStation;
class AddFormulation:public AddEvent
{

public:
	AddFormulation(MarsStation*m);
	virtual void Excute(int id,int ed,float tl=0,int noday=0,int sf=0,char t=0 );
	virtual~AddFormulation(void);
};

