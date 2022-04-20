#pragma once
class MarsStation;
#include"Rover.h"
#include"Mission.h"
#include"CheckUp.h"
class DeAssign
{
	MarsStation*mars_DeAssign;
	Mission*mission_DeAssign;
public:
	DeAssign(MarsStation*,Mission*);
	void Execute();
	~DeAssign(void);
};

