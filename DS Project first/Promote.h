#pragma once
class MarsStation;
#include"Mission.h"
class Promote
{
	MarsStation*mars_Promote;
	Mission*mission_Promote;
public:
	Promote(MarsStation*,Mission*);
	void Execute();
	~Promote(void);
};

