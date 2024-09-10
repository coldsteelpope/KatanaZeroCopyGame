#include "pch.h"
#include "CameraCareTaker.h"

CCameraCareTaker* CCameraCareTaker::m_pInstance = nullptr;

CCameraCareTaker::CCameraCareTaker()
{
}

CCameraCareTaker::~CCameraCareTaker()
{
	Release();
}
