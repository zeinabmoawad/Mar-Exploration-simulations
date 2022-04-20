#pragma once
class MarsStation;
class AddEvent
{
protected:
	MarsStation*ms;
public:
	AddEvent(MarsStation*m)
	{
		ms=m;
	}
	virtual void Excute(int id,int ed,float tl=0,int noday=0,int sf=0,char t=0 )=0;
	virtual~AddEvent(void){}
};

