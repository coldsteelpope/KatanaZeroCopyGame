#include "pch.h"
#include "ItemCareTaker.h"

CItemCareTaker* CItemCareTaker::m_pInstance = nullptr;

CItemCareTaker::CItemCareTaker()
{
}

CItemCareTaker::~CItemCareTaker()
{
	Release();
}
