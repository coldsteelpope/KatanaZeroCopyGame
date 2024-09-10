#include "pch.h"
#include "BossCareTaker.h"

CBossCareTaker* CBossCareTaker::m_pInstance = nullptr;

CBossCareTaker::CBossCareTaker()
{
}

CBossCareTaker::~CBossCareTaker()
{
	Release();
}
