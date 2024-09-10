#include "pch.h"
#include "ReplayMgr.h"

#include "PlayerCareTaker.h"
#include "EffectCareTaker.h"
#include "CameraCareTaker.h"
#include "EnemyCareTaker.h"
#include "ItemCareTaker.h"

CReplayMgr* CReplayMgr::m_pInstance = nullptr;

CReplayMgr::CReplayMgr()
{
}

CReplayMgr::~CReplayMgr()
{
	Release();
}

void CReplayMgr::Copy_Player_Mementos()
{
	while (CPlayerCareTaker::Get_Instance()->Get_Memento_Size() != 0)
	{
		m_vPlayerMementos.push_back(CPlayerCareTaker::Get_Instance()->Roll_Front());
	}
}

void CReplayMgr::Copy_Effect_Mementos()
{
	while (CEffectCareTaker::Get_Instance()->Get_Memento_Size() != 0)
	{
		m_vEffectMementos.push_back(CEffectCareTaker::Get_Instance()->Roll_Front());
	}
}

void CReplayMgr::Copy_Camera_Mementos()
{
	while (CCameraCareTaker::Get_Instance()->Get_Memento_Size() != 0)
	{
		m_vCameraMementos.push_back(CCameraCareTaker::Get_Instance()->Roll_Front());
	}
}

void CReplayMgr::Copy_Enemy_Mementos()
{
	while (CEnemyCareTaker::Get_Instance()->Get_Memento_Size() != 0)
	{
		m_vEnemyMementos.push_back(CEnemyCareTaker::Get_Instance()->Roll_Front());
	}
}

void CReplayMgr::Copy_Item_Mementos()
{
	while (CItemCareTaker::Get_Instance()->Get_Memento_Size() != 0)
	{
		m_vItemMementos.push_back(CItemCareTaker::Get_Instance()->Roll_Front());
	}
}

void CReplayMgr::Release()
{
	for_each(m_vPlayerMementos.begin(), m_vPlayerMementos.end(), Safe_Delete<CMemento*>);
	for_each(m_vEffectMementos.begin(), m_vEffectMementos.end(), Safe_Delete<CMemento*>);
	for_each(m_vCameraMementos.begin(), m_vCameraMementos.end(), Safe_Delete<CCameraMemento*>);
	for_each(m_vEnemyMementos.begin(), m_vEnemyMementos.end(), Safe_Delete<CEnemyMemento*>);
	for_each(m_vItemMementos.begin(), m_vItemMementos.end(), Safe_Delete<CItemMemento*>);

	m_vPlayerMementos.clear();
	m_vEffectMementos.clear();
	m_vCameraMementos.clear();
	m_vEnemyMementos.clear();
	m_vItemMementos.clear();
}
