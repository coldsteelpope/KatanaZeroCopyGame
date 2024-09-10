#include "pch.h"
#include "PlayerCareTaker.h"

CPlayerCareTaker* CPlayerCareTaker::m_pInstance = nullptr;

CPlayerCareTaker::CPlayerCareTaker()
{
}

CPlayerCareTaker::~CPlayerCareTaker()
{
	Release();
}
