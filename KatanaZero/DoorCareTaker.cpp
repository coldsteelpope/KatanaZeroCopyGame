#include "pch.h"
#include "DoorCareTaker.h"

CDoorCareTaker* CDoorCareTaker::m_pInstance = nullptr;

CDoorCareTaker::CDoorCareTaker()
{
}

CDoorCareTaker::~CDoorCareTaker()
{
	Release();
}
