#include "pch.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "TimeRewindMgr.h"
#include "Stage01.h"
#include "Stage02.h"
#include "Stage03.h"
#include "Replay.h"
#include "ObjMgr.h"
#include "BossStage01.h"
#include "BossStage02.h"
#include "EndingScene.h"
#include "MainMenuScene.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_pActiveScene(nullptr)
	, m_ePreScene(SCENE_ID::SC_END)
	, m_eCurScene(SCENE_ID::SC_END)
{

}

CSceneMgr::~CSceneMgr()
{
	Release();
}

int CSceneMgr::Update()
{
	m_pActiveScene->Update();
	return 0;
}

void CSceneMgr::Late_Update()
{
	m_pActiveScene->Late_Update();
}

void CSceneMgr::Render(HDC _hDC)
{
	m_pActiveScene->Render(_hDC);
}

void CSceneMgr::Release()
{
	Safe_Delete<CScene*>(m_pActiveScene);
}

void CSceneMgr::Change_Scene(SCENE_ID _eScene)
{
	m_eCurScene = _eScene;
	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete<CScene*>(m_pActiveScene);
		
		switch (m_eCurScene)
		{
		case SCENE_ID::SC_MAIN_MENU:
		{
			m_pActiveScene = new CMainMenuScene;
			break;
		}
		case SCENE_ID::SC_STAGE_01:
		{
			m_pActiveScene = new CStage01;
			break;
		}
		case SCENE_ID::SC_REPLAY:
		{
			m_pActiveScene = new CReplay;
			break;
		}
		case SCENE_ID::SC_STAGE_02:
		{
			m_pActiveScene = new CStage02;
			break;
		}
		case SCENE_ID::SC_STAGE_03:
		{
			m_pActiveScene = new CStage03;
			break;
		}
		case SCENE_ID::SC_BOSS_01:
		{
			m_pActiveScene = new CBossStage01;
			break;
		}
		case SCENE_ID::SC_BOSS_02:
		{
			m_pActiveScene = new CBossStage02;
			break;
		}
		}
		
		CObjMgr::Get_Instance()->Clear_All_Object_List();
		m_pActiveScene->Initialize();
		m_ePreScene = m_eCurScene;
	}
}

void CSceneMgr::Renew_Scene(SCENE_ID _eScene)
{
	Safe_Delete<CScene*>(m_pActiveScene);
	CObjMgr::Get_Instance()->Clear_All_Object_List();

	switch (m_eCurScene)
	{
	case SCENE_ID::SC_MAIN_MENU:
	{
		m_pActiveScene = new CMainMenuScene;
		break;
	}
	case SCENE_ID::SC_STAGE_01:
	{
		m_pActiveScene = new CStage01;
		break;
	}
	case SCENE_ID::SC_STAGE_02:
	{
		m_pActiveScene = new CStage02;
		break;
	}
	case SCENE_ID::SC_STAGE_03:
	{
		m_pActiveScene = new CStage03;
		break;
	}
	case SCENE_ID::SC_BOSS_01:
	{
		m_pActiveScene = new CBossStage01;
		break;
	}
	case SCENE_ID::SC_BOSS_02:
	{
		m_pActiveScene = new CBossStage02;
		break;
	}
	}
	m_pActiveScene->Initialize();
	CTimeRewindMgr::Get_Instance()->Set_RewindTime(false);
}
