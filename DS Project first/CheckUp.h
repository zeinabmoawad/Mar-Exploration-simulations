#pragma once
class MarsStation;
#include"Rover.h"
class CheckUp
{
	MarsStation*m_checkup;
	Rover*r_checkup;
public:
	CheckUp(MarsStation*,Rover*);
	void Execute();
	~CheckUp(void);
};

