#pragma once

#include "SceneMgr.h"
#include "Scene.h"


class CComboMgr
{
private:
	CComboMgr();
	virtual ~CComboMgr();

public:
	void Kill_Enemy(float _fX, float _fY)
	{
		++iCombo;
		if (iCombo >= 7)
		{
			CSceneMgr::Get_Instance()->Get_Active_Scene()->Set_Highlight_Event(true);
			CSceneMgr::Get_Instance()->Get_Active_Scene()->Set_Highlight_Target_Pos(_fX, _fY);
			iCombo = 0;
		}
	}

	

public:
	static CComboMgr* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CComboMgr;
		}
		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CComboMgr* m_pInstance;
	int iCombo = 0;
	
};

