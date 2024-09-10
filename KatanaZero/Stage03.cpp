#include "pch.h"
#include "Stage03.h"
#include "TileMgr.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "LineMgr.h"
#include "ObjMgr.h"
#include "MouseMgr.h"
#include "Player.h"
#include "UIMgr.h"
#include "AbstractFactory.h"

#include "Gangster.h"
#include "Grunt.h"
#include "TimeRewindMgr.h"
#include "ReplayMgr.h"
#include "SceneMgr.h"

#include "ItemCareTaker.h"
#include "CameraCareTaker.h"
#include "EffectCareTaker.h"
#include "EnemyCareTaker.h"
#include "PlayerCareTaker.h"

#include "Memento.h"
#include "EnemyMemento.h"
#include "CameraMemento.h"
#include "ItemMemento.h"
#include "HighlightMgr.h"
#include "Door.h"
#include "BloodCareTaker.h"
#include "BloodMemento.h"
#include "DoorCareTaker.h"
#include "DoorMemento.h"
#include "TimeSlowMgr.h"
#include "ThunderBreathingMgr.h"


#define STAGE03_WIDTH		2286
#define STAGE03_HEIGHT		640

#define PLAYER_START_POS_FX		100
#define PLAYER_START_POS_FY		375


CStage03::CStage03()
{
	
}

CStage03::~CStage03()
{
	Release();
}

void CStage03::Initialize()
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_PLAYER, CAbstractFactory<CPlayer>::Create(PLAYER_START_POS_FX, PLAYER_START_POS_FY, PLAYER_IDLE_FCX, PLAYER_IDLE_FCY));
	m_pPlayer = CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_PLAYER).front();
	CMouseMgr::Get_Instance()->Set_Target(m_pPlayer);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/map/Stage03.bmp", L"Stage03");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/map/Stage03_slow.bmp", L"Stage03_Slow");
	CTileMgr::Get_Instance()->Set_Height(STAGE03_HEIGHT);
	CTileMgr::Get_Instance()->Set_Width(STAGE03_WIDTH);
	CTileMgr::Get_Instance()->Initialize();

	CCamera::Get_Instance()->Set_LookAt(WINCX / 2.0f, WINCY / 2.0f);
	CCamera::Get_Instance()->Set_Camera_Target(m_pPlayer);
	CCamera::Get_Instance()->Set_Limit_X(STAGE03_WIDTH);
	CCamera::Get_Instance()->Set_Limit_Y(STAGE03_HEIGHT);

	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CGrunt>::Create(280, 400, GRUNT_IDLE_FCX, GRUNT_IDLE_FCY, OBJ_DIR::LEFT, ENEMY_TYPE::WALK_TYPE, 250, 350));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CGangster>::Create(390, 400, GANGSTER_IDLE_FCX, GANGSTER_IDLE_FCY, OBJ_DIR::RIGHT, ENEMY_TYPE::WALK_TYPE, 350, 500));

	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CGangster>::Create(670, 400, GANGSTER_IDLE_FCX, GANGSTER_IDLE_FCY, OBJ_DIR::LEFT, ENEMY_TYPE::WALK_TYPE, 650, 850));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CGangster>::Create(873, 400, GANGSTER_IDLE_FCX, GANGSTER_IDLE_FCY, OBJ_DIR::RIGHT, ENEMY_TYPE::WALK_TYPE, 850, 1050));

	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CGangster>::Create(873, 400, GANGSTER_IDLE_FCX, GANGSTER_IDLE_FCY, OBJ_DIR::RIGHT, ENEMY_TYPE::WALK_TYPE, 850, 1050));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CGangster>::Create(873, 400, GANGSTER_IDLE_FCX, GANGSTER_IDLE_FCY, OBJ_DIR::RIGHT, ENEMY_TYPE::WALK_TYPE, 850, 1050));

	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CGrunt>::Create(1220, 270, GRUNT_IDLE_FCX, GRUNT_IDLE_FCX, OBJ_DIR::LEFT, ENEMY_TYPE::WALK_TYPE, 1030, 1300));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CGangster>::Create(1700, 270, GANGSTER_IDLE_FCX, GANGSTER_IDLE_FCX, OBJ_DIR::LEFT, ENEMY_TYPE::WALK_TYPE, 1640, 1750));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CGrunt>::Create(1400, 270, GRUNT_IDLE_FCX, GRUNT_IDLE_FCX, OBJ_DIR::RIGHT, ENEMY_TYPE::WALK_TYPE, 1200, 1750));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CGrunt>::Create(2050, 270, GRUNT_IDLE_FCX, GRUNT_IDLE_FCX, OBJ_DIR::LEFT, ENEMY_TYPE::WALK_TYPE, 2000, 2100));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CGrunt>::Create(2150, 270, GRUNT_IDLE_FCX, GRUNT_IDLE_FCX, OBJ_DIR::LEFT, ENEMY_TYPE::WALK_TYPE, 2000, 2100));


	// 문 설치
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_DOOR, CAbstractFactory<CDoor>::Create(210, 380));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_DOOR, CAbstractFactory<CDoor>::Create(595, 380));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_DOOR, CAbstractFactory<CDoor>::Create(1805, 380));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_DOOR, CAbstractFactory<CDoor>::Create(1415, 243));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_DOOR, CAbstractFactory<CDoor>::Create(1805, 243));


	CLineMgr::Get_Instance()->Initialize();
	CUIMgr::Get_Instance()->Initialize();
	CUIMgr::Get_Instance()->Set_Player(m_pPlayer);

	backgroundMusic = L"katanabgm.wav";
}

int CStage03::Update()
{
	if (CTimeRewindMgr::Get_Instance()->Get_RewindTime() == false)
	{
		CTileMgr::Get_Instance()->Update();
		CLineMgr::Get_Instance()->Update();
		CCamera::Get_Instance()->Update();
		CObjMgr::Get_Instance()->Update();
	}
	return 0;
}

void CStage03::Late_Update()
{
	if (CTimeRewindMgr::Get_Instance()->Get_RewindTime() == false)
	{
		CTileMgr::Get_Instance()->Late_Update();
		CLineMgr::Get_Instance()->Late_Update();
		CCamera::Get_Instance()->Late_Update();
		CObjMgr::Get_Instance()->Late_Update();
		Store_Mementos();
		++m_llFrameCount;
	}
}

void CStage03::Render(HDC _hDC)
{
	if (CTimeRewindMgr::Get_Instance()->Get_RewindTime() == false)
	{
		Vec2 vLookAt = CCamera::Get_Instance()->Get_LookAt();
		HDC hMapDC = CBmpMgr::Get_Instance()->Find_Img(L"Stage03");
		HDC hSlowMapDC = CBmpMgr::Get_Instance()->Find_Img(L"Stage03_Slow");

		if (CTimeSlowMgr::Get_Instance()->Get_Slow_Time())
		{
			BitBlt(_hDC, WINCX / 2.0f - vLookAt.fX, WINCY / 2.0f - vLookAt.fY, STAGE03_WIDTH, STAGE03_HEIGHT, hSlowMapDC, 0, 0, SRCCOPY);
		}
		else
		{
			BitBlt(_hDC, WINCX / 2.0f - vLookAt.fX, WINCY / 2.0f - vLookAt.fY, STAGE03_WIDTH, STAGE03_HEIGHT, hMapDC, 0, 0, SRCCOPY);
		}
		

		CObjMgr::Get_Instance()->Render(_hDC);
		CUIMgr::Get_Instance()->Render(_hDC);

		if (CThunderBreathingMgr::Get_Instance()->Get_ThunderBreathing_Mode())
		{
			CHighlightMgr::Get_Instance()->Print_Highlight_For_ThunderBreathing(
				_hDC,
				m_pPlayer->Get_Info().fX,
				m_pPlayer->Get_Info().fY,
				CThunderBreathingMgr::Get_Instance()->Get_Player_Thunder_Breathing_Motion()
			);
		}
		else if (m_bHighlightEvent)
		{
			//CHighlightMgr::Get_Instance()->Print_Highlight(_hDC, m_Highlight_Target_fX, m_Highlight_Target_fY);
			CHighlightMgr::Get_Instance()->Print_Highlight(_hDC, m_Highlight_Target_fX, m_Highlight_Target_fY, 500.f, true);
		}


		if (m_pPlayer->Get_Info().fX >= 2280)
		{
			CReplayMgr::Get_Instance()->Set_Full_Frame(m_llFrameCount);
			CReplayMgr::Get_Instance()->Set_Scene_Height(STAGE03_HEIGHT);
			CReplayMgr::Get_Instance()->Set_Scene_Width(STAGE03_WIDTH);

			CSceneMgr::Get_Instance()->Change_Scene(SCENE_ID::SC_REPLAY);
		}
	}
	else
	{
		Print_Store_Mementos(_hDC);
		--m_llFrameCount;
		if (m_llFrameCount == 0)
		{
			CSceneMgr::Get_Instance()->Renew_Scene(SCENE_ID::SC_STAGE_03);
		}
	}
}

void CStage03::Release()
{
	//CTileMgr::Destroy_Instance();
	CLineMgr::Destroy_Instance();
	CCamera::Destroy_Instance();
	
}

void CStage03::Print_Store_Mementos(HDC _hDC)
{
	// Camera Memento 꺼내기
	if (CCameraCareTaker::Get_Instance()->Get_Memento_Size() != 0)
	{
		CCameraMemento* pCameraMemento = CCameraCareTaker::Get_Instance()->Get_Back();
		while (pCameraMemento->Get_Frame_Count() == m_llFrameCount)
		{
			pCameraMemento = CCameraCareTaker::Get_Instance()->Roll_Back();
			CCamera::Get_Instance()->Set_LookAt(pCameraMemento->Get_Look_At());
			CCamera::Get_Instance()->Set_PrevLookAt(pCameraMemento->Get_Prev_Look_At());
			CCamera::Get_Instance()->Set_m_vDiff(pCameraMemento->Get_Diff());
			Safe_Delete<CCameraMemento*>(pCameraMemento);

			if (CCameraCareTaker::Get_Instance()->Get_Memento_Size() != 0)
			{
				pCameraMemento = CCameraCareTaker::Get_Instance()->Get_Back();
			}
			else
			{
				break;
			}
		}
	}


	Vec2 vLookAt = CCamera::Get_Instance()->Get_LookAt();
	HDC hMapDC = CBmpMgr::Get_Instance()->Find_Img(L"Stage03");
	
	BitBlt(_hDC, WINCX / 2.0f - vLookAt.fX, WINCY / 2.0f - vLookAt.fY, STAGE03_WIDTH, STAGE03_HEIGHT, hMapDC, 0, 0, SRCCOPY);


	// Player Care Taker 가져오기
	if (CPlayerCareTaker::Get_Instance()->Get_Memento_Size() != 0)
	{
		CMemento* pLastMemento = CPlayerCareTaker::Get_Instance()->Back();
		while (pLastMemento->Get_Frame_Count() == m_llFrameCount)
		{
			pLastMemento = CPlayerCareTaker::Get_Instance()->Roll_Back();
			pLastMemento->Print_Memento(_hDC);
			Safe_Delete<CMemento*>(pLastMemento);

			if (CPlayerCareTaker::Get_Instance()->Get_Memento_Size() != 0)
			{
				pLastMemento = CPlayerCareTaker::Get_Instance()->Back();
			}
			else
			{
				break;
			}
		}
	}


	if (CEffectCareTaker::Get_Instance()->Get_Memento_Size() != 0)
	{
		CMemento* pLastMemento = CEffectCareTaker::Get_Instance()->Back();
		while (pLastMemento->Get_Frame_Count() == m_llFrameCount)
		{
			pLastMemento = CEffectCareTaker::Get_Instance()->Roll_Back();
			pLastMemento->Print_Memento(_hDC);
			Safe_Delete<CMemento*>(pLastMemento);

			if (CEffectCareTaker::Get_Instance()->Get_Memento_Size() != 0)
			{
				pLastMemento = CPlayerCareTaker::Get_Instance()->Back();
			}
			else
			{
				break;
			}
		}
	}


	// Enemy Care Taker 가져오기
	if (CEnemyCareTaker::Get_Instance()->Get_Memento_Size() != 0)
	{
		CEnemyMemento* pLastMemento = CEnemyCareTaker::Get_Instance()->Back();
		while (pLastMemento->Get_Frame_Count() == m_llFrameCount)
		{
			pLastMemento = CEnemyCareTaker::Get_Instance()->Roll_Back();
			pLastMemento->Print_Memento(_hDC);
			Safe_Delete<CEnemyMemento*>(pLastMemento);

			if (CEnemyCareTaker::Get_Instance()->Get_Memento_Size() != 0)
			{
				pLastMemento = CEnemyCareTaker::Get_Instance()->Back();
			}
			else
			{
				break;
			}
		}
	}


	// Item 가져오기
	if (CItemCareTaker::Get_Instance()->Get_Memento_Size() != 0)
	{
		CItemMemento* pLastMemento = CItemCareTaker::Get_Instance()->Back();
		while (pLastMemento->Get_Frame_Count() == m_llFrameCount)
		{
			pLastMemento = CItemCareTaker::Get_Instance()->Roll_Back();
			pLastMemento->Print_Memento(_hDC);
			Safe_Delete<CItemMemento*>(pLastMemento);

			if (CItemCareTaker::Get_Instance()->Get_Memento_Size() != 0)
			{
				pLastMemento = CItemCareTaker::Get_Instance()->Back();
			}
			else
			{
				break;
			}
		}
	}

	// Blood 가져오기
	if (CBloodCareTaker::Get_Instance()->Get_Memento_Size() != 0)
	{
		CBloodMemento* pLastMemento = CBloodCareTaker::Get_Instance()->Back();
		while (pLastMemento->Get_Frame_Count() == m_llFrameCount)
		{
			pLastMemento = CBloodCareTaker::Get_Instance()->Roll_Back();
			pLastMemento->Print_Memento(_hDC);
			Safe_Delete<CBloodMemento*>(pLastMemento);
			if (CBloodCareTaker::Get_Instance()->Get_Memento_Size() != 0)
			{
				pLastMemento = CBloodCareTaker::Get_Instance()->Back();
			}
			else
			{
				break;
			}
		}
	}

	// Door 가져오기
	if (CDoorCareTaker::Get_Instance()->Get_Memento_Size() != 0)
	{
		CDoorMemento* pLastMemento = CDoorCareTaker::Get_Instance()->Back();
		while (pLastMemento->Get_Frame_Count() == m_llFrameCount)
		{
			pLastMemento = CDoorCareTaker::Get_Instance()->Roll_Back();
			pLastMemento->Print_Memento(_hDC);
			Safe_Delete<CDoorMemento*>(pLastMemento);
			if (CDoorCareTaker::Get_Instance()->Get_Memento_Size() != 0)
			{
				pLastMemento = CDoorCareTaker::Get_Instance()->Back();
			}
			else
			{
				break;
			}
		}
	}
}

void CStage03::Store_Mementos()
{

	CMemento* pCurrentMemento = new CMemento(
		m_pPlayer->Get_Frame(),
		m_pPlayer->Get_Frame_Key(),
		m_pPlayer->Get_Render_Rect(),
		m_pPlayer->Get_Info(),
		m_pPlayer->Get_Obj_Cur_Dir(),
		m_llFrameCount
	);

	CPlayerCareTaker::Get_Instance()->Add_Memento(pCurrentMemento);

	CCameraMemento* pCurrentCameraMemento = new CCameraMemento(
		CCamera::Get_Instance()->Get_LookAt(),
		CCamera::Get_Instance()->Get_PrevLookAt(),
		CCamera::Get_Instance()->Get_Diff(),
		m_llFrameCount
	);
	CCameraCareTaker::Get_Instance()->Add_Memento(pCurrentCameraMemento);


	// Effect 저장
	list<CObj*> m_pObjEffectList = CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_EFFECT);
	for (auto iter = m_pObjEffectList.begin(); iter != m_pObjEffectList.end(); ++iter)
	{
		CObj* pEffectObj = (*iter);
		CMemento* pCurentEffectMemento = new CMemento(
			pEffectObj->Get_Frame(),
			pEffectObj->Get_Frame_Key(),
			pEffectObj->Get_Render_Rect(),
			pEffectObj->Get_Info(),
			pEffectObj->Get_Obj_Cur_Dir(),
			m_llFrameCount
		);
		CEffectCareTaker::Get_Instance()->Add_Memento(pCurentEffectMemento);
	}


	// Enemy 저장
	list<CObj*> m_pObjEnemyList = CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_ENEMY);
	for (auto iter = m_pObjEnemyList.begin(); iter != m_pObjEnemyList.end(); ++iter)
	{
		CObj* pEnemyObj = (*iter);
		CEnemyMemento* pCurrentEnemyMemento = new CEnemyMemento(
			pEnemyObj->Get_Frame(),
			pEnemyObj->Get_Frame_Key(),
			pEnemyObj->Get_Render_Rect(),
			pEnemyObj->Get_Info(),
			pEnemyObj->Get_Obj_Cur_Dir(),
			m_llFrameCount
		);
		CEnemyCareTaker::Get_Instance()->Add_Memento(pCurrentEnemyMemento);
	}


	// Item 저장
	list<CObj*> m_pObjExplosiveList = CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_EXPLOSIVE);
	list<CObj*> m_pObjOilDrumList = CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_OIL_DRUM);
	list<CObj*> m_pExplosionList = CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_EXPLOSION);

	for (auto iter = m_pObjExplosiveList.begin(); iter != m_pObjExplosiveList.end(); ++iter)
	{
		CObj* pObj = (*iter);
		CItemMemento* pCurrentMemento = new CItemMemento(
			pObj->Get_Frame(),
			pObj->Get_Frame_Key(),
			pObj->Get_Render_Rect(),
			pObj->Get_Info(),
			pObj->Get_Obj_Cur_Dir(),
			m_llFrameCount
		);
		CItemCareTaker::Get_Instance()->Add_Memento(pCurrentMemento);
	}

	for (auto iter = m_pObjOilDrumList.begin(); iter != m_pObjOilDrumList.end(); ++iter)
	{
		CObj* pObj = (*iter);
		CItemMemento* pCurrentMemento = new CItemMemento(
			pObj->Get_Frame(),
			pObj->Get_Frame_Key(),
			pObj->Get_Render_Rect(),
			pObj->Get_Info(),
			pObj->Get_Obj_Cur_Dir(),
			m_llFrameCount
		);
		CItemCareTaker::Get_Instance()->Add_Memento(pCurrentMemento);
	}

	for (auto iter = m_pExplosionList.begin(); iter != m_pExplosionList.end(); ++iter)
	{
		CObj* pObj = (*iter);
		CItemMemento* pCurrentMemento = new CItemMemento(
			pObj->Get_Frame(),
			pObj->Get_Frame_Key(),
			pObj->Get_Render_Rect(),
			pObj->Get_Info(),
			pObj->Get_Obj_Cur_Dir(),
			m_llFrameCount
		);
		CItemCareTaker::Get_Instance()->Add_Memento(pCurrentMemento);
	}

	// 피 저장
	list<CObj*> m_pObjBloodList = CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_BLOOD);
	for (auto iter = m_pObjBloodList.begin(); iter != m_pObjBloodList.end(); ++iter)
	{
		CObj* pObj = (*iter);

		CBloodMemento* pCurrentMemento = new CBloodMemento(
			pObj->Get_Frame(),
			pObj->Get_Frame_Key(),
			pObj->Get_Render_Rect(),
			pObj->Get_Info(),
			pObj->Get_Obj_Cur_Dir(),
			m_llFrameCount
		);
		CBloodCareTaker::Get_Instance()->Add_Memento(pCurrentMemento);
	}


	// 문 저장
	list<CObj*> m_pObjDoorList = CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_DOOR);
	for (auto iter = m_pObjDoorList.begin(); iter != m_pObjDoorList.end(); ++iter)
	{
		CObj* pObj = (*iter);
		CDoorMemento* pCurrentMemento = new CDoorMemento(
			pObj->Get_Frame(),
			pObj->Get_Frame_Key(),
			pObj->Get_Render_Rect(),
			pObj->Get_Info(),
			pObj->Get_Obj_Cur_Dir(),
			m_llFrameCount
		);
		CDoorCareTaker::Get_Instance()->Add_Memento(pCurrentMemento);
	}
}
