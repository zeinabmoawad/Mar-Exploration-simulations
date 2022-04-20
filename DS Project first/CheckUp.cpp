#include "CheckUp.h"
#include"MarsStation.h"

CheckUp::CheckUp(MarsStation*m,Rover*r)
{
	m_checkup=m;
	r_checkup=r;
}
void CheckUp::Execute()
{
	//if rover has performed no of mission % limit of missions before check up
	if((r_checkup->getPerformed_Mission_NO())%(r_checkup->GetNumberOfMissions_BeforeCheck())==0)
	{
		//Calc Day required to become avalible again 
		r_checkup->SetOutFromCheckupDay(m_checkup->getDay()+r_checkup->GetCheckupDuration());
		m_checkup->AddRoverinCheckup(r_checkup);
	}
	else
		m_checkup->AddRoverinlist(r_checkup);
}

CheckUp::~CheckUp(void)
{
}
