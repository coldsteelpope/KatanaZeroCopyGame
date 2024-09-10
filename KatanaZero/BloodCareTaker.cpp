#include "pch.h"
#include "BloodCareTaker.h"

CBloodCareTaker* CBloodCareTaker::m_pInstance = nullptr;

CBloodCareTaker::CBloodCareTaker()
{
}

CBloodCareTaker::~CBloodCareTaker()
{
	Release();
}
