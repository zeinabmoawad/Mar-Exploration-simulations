#pragma once
#include<iostream>
#include<fstream>
#include<ostream>
#include<string>
#include"Defs.h"
#include"Mission.h"
#include <chrono>
using namespace std;
class MarsStation;
class UI
{
	MarsStation*ms;
	ofstream output;
	bool silent;
public:

	UI(MarsStation*);
	void Read_Data();
	void Print_OutputFile();
	void PrintMission(Mission*mis);
	void PrintInteractive(Mode m);
	void PrintSilent(Mode m);
	void Print(string);
	~UI(void);
};

