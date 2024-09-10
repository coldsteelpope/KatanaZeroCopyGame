#include "pch.h"
#include "EffectCareTaker.h"

CEffectCareTaker* CEffectCareTaker::m_pInstance = nullptr;

CEffectCareTaker::CEffectCareTaker()
{
}

CEffectCareTaker::~CEffectCareTaker()
{
	Release();
}
