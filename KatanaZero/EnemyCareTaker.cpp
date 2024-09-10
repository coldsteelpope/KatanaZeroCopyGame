#include "pch.h"
#include "EnemyCareTaker.h"

CEnemyCareTaker* CEnemyCareTaker::m_pInstance = nullptr;

CEnemyCareTaker::CEnemyCareTaker()
{

}

CEnemyCareTaker::~CEnemyCareTaker()
{
	Release();
}
