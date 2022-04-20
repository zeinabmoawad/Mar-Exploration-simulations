#pragma once
#include"Rover.h"
#include"Mission.h"
class MarsStation;
class Assign
{
	MarsStation*mtoassign;
public:
	Assign(MarsStation*);
	void Execute(Rover* r, Mission* m);
	~Assign(void);
};

