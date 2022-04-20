#pragma once
class MarsStation;
#include"Rover.h"
class AddRover
{
	MarsStation*ms;
public:
	AddRover(MarsStation*m);
	void Execute(float s,int num,int c,Type T);
	~AddRover(void);
};

