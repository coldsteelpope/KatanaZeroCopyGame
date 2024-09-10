#include "pch.h"
#include "Stage02.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "ObjMgr.h"
#include "TimeRewindMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "MouseMgr.h"
#include "LineMgr.h"
#include "UIMgr.h"
#include "SceneMgr.h"

#include "Grunt.h"
#include "Gangster.h"
#include "OilDrum.h"
#include "Door.h"

#include "Memento.h"
#include "CameraMemento.h"
#include "EnemyMemento.h"
#include "ItemMemento.h"
#include "PlayerCareTaker.h"
#include "EffectCareTaker.h"
#include "ItemCareTaker.h"
#include "EnemyCareTaker.h"
#include "CameraCareTaker.h"
#include "HighlightMgr.h"
#include "BloodCareTaker.h"
#include "DoorCareTaker.h"
#include "BloodMemento.h"
#include "DoorMemento.h"

#include "ReplayMgr.h"
#include "TimeSlowMgr.h"
#include "Pomp.h"
#include "ThunderBreathingMgr.h"

//#define STAGE02_WIDTH   1240
//#define STAGE02_HEIGHT  1994

#define STAGE02_WIDTH 1140
#define STAGE02_HEIGHT 1832

#define PLAYER_START_POS_FX		200
#define PLAYER_START_POS_FY		100

CStage02::CStage02()
{
}

CStage02::~CStage02()
{
	Release();
}

void CStage02::Initialize()
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_PLAYER, CAbstractFactory<CPlayer>::Create(PLAYER_START_POS_FX, PLAYER_START_POS_FY, PLAYER_IDLE_FCX, PLAYER_IDLE_FCY));
	m_pPlayer = CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_PLAYER).front();
	CMouseMgr::Get_Instance()->Set_Target(m_pPlayer);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/map/Stage02.bmp", L"Stage02");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/map/Stage02_slow.bmp", L"Stage02_Slow");
    CCamera::Get_Instance()->Set_LookAt(WINCX / 2.0f, WINCY / 2.0f);
	
	
	// 9층
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CGrunt>::Create(300, 320, GRUNT_IDLE_FCX, GRUNT_IDLE_FCY, OBJ_DIR::RIGHT, ENEMY_TYPE::WALK_TYPE, 200, 500));
	
	// 8
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CPomp>::Create(400, 440, POMP_IDLE_FCX, POMP_IDLE_FCY, OBJ_DIR::RIGHT, ENEMY_TYPE::WALK_TYPE, 300, 400));
	
	// 7
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CGrunt>::Create(450, 580, GRUNT_IDLE_FCX, GRUNT_IDLE_FCY, OBJ_DIR::RIGHT, ENEMY_TYPE::WALK_TYPE, 300, 500));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CGrunt>::Create(400, 580, GRUNT_IDLE_FCX, GRUNT_IDLE_FCY, OBJ_DIR::LEFT, ENEMY_TYPE::WALK_TYPE, 300, 500));	
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_EXPLOSIVE, CAbstractFactory<CExplosive>::Create(550, 560, EXPLOSIVE_TYPE::EXPLOSIVE_PICK_TYPE));

	// OIL DRUM
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_OIL_DRUM, CAbstractFactory<COilDrum>::Create(350, 680, OIL_DRUM_FCX, OIL_DRUM_FCY));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_OIL_DRUM, CAbstractFactory<COilDrum>::Create(375, 680, OIL_DRUM_FCX, OIL_DRUM_FCY));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_OIL_DRUM, CAbstractFactory<COilDrum>::Create(400, 680, OIL_DRUM_FCX, OIL_DRUM_FCY));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_OIL_DRUM, CAbstractFactory<COilDrum>::Create(425, 680, OIL_DRUM_FCX, OIL_DRUM_FCY));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_OIL_DRUM, CAbstractFactory<COilDrum>::Create(450, 680, OIL_DRUM_FCX, OIL_DRUM_FCY));


	// 6 (화염병 투척)
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CPomp>::Create(350, 680, POMP_IDLE_FCX, POMP_IDLE_FCY, OBJ_DIR::RIGHT, ENEMY_TYPE::WALK_TYPE, 300, 500));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CGrunt>::Create(450, 680, GRUNT_IDLE_FCX, GRUNT_IDLE_FCY, OBJ_DIR::LEFT, ENEMY_TYPE::WALK_TYPE, 300, 500));
	
	// 5
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CPomp>::Create(400, 800, POMP_IDLE_FCX, POMP_IDLE_FCY, OBJ_DIR::RIGHT, ENEMY_TYPE::WALK_TYPE, 450, 500));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CPomp>::Create(300, 800, POMP_IDLE_FCX, POMP_IDLE_FCY, OBJ_DIR::LEFT, ENEMY_TYPE::WALK_TYPE, 350, 500));
	
	// 4
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CGrunt>::Create(300, 920, GRUNT_IDLE_FCX, GRUNT_IDLE_FCY, OBJ_DIR::RIGHT, ENEMY_TYPE::WALK_TYPE, 300, 400));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CGrunt>::Create(400, 920, GRUNT_IDLE_FCX, GRUNT_IDLE_FCY, OBJ_DIR::LEFT, ENEMY_TYPE::WALK_TYPE, 300, 500));

	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CGrunt>::Create(400, 1120, GRUNT_IDLE_FCX, GRUNT_IDLE_FCY, OBJ_DIR::LEFT, ENEMY_TYPE::WALK_TYPE, 300, 500));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CGrunt>::Create(400, 1120, GRUNT_IDLE_FCX, GRUNT_IDLE_FCY, OBJ_DIR::RIGHT, ENEMY_TYPE::WALK_TYPE, 300, 500));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CGrunt>::Create(400, 1120, GRUNT_IDLE_FCX, GRUNT_IDLE_FCY, OBJ_DIR::LEFT, ENEMY_TYPE::WALK_TYPE, 300, 500));


	// Door
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_DOOR, CAbstractFactory<CDoor>::Create(840, 1510));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CPomp>::Create(910, 1530, POMP_IDLE_FCX, POMP_IDLE_FCY, OBJ_DIR::LEFT, ENEMY_TYPE::WALK_TYPE, 910, 920));


	CCamera::Get_Instance()->Set_Camera_Target(m_pPlayer);
    CCamera::Get_Instance()->Set_Limit_X(STAGE02_WIDTH);
    CCamera::Get_Instance()->Set_Limit_Y(STAGE02_HEIGHT);

	CUIMgr::Get_Instance()->Initialize();
	CUIMgr::Get_Instance()->Set_Player(m_pPlayer);

	backgroundMusic = L"katanabgm.wav";

	CLineMgr::Get_Instance()->Initialize();
}

int CStage02::Update()
{
	if (CTimeRewindMgr::Get_Instance()->Get_RewindTime() == false)
	{
		CCamera::Get_Instance()->Update();
		CObjMgr::Get_Instance()->Update();
		CLineMgr::Get_Instance()->Update();
	}
	return 0;
}

void CStage02::Late_Update()
{
	if (CTimeRewindMgr::Get_Instance()->Get_RewindTime() == false)
	{
		CCamera::Get_Instance()->Late_Update();
		CLineMgr::Get_Instance()->Late_Update();
		CObjMgr::Get_Instance()->Late_Update();

		Store_Mementos();

		++m_llFrameCount;
	}
}

void CStage02::Render(HDC _hDC)
{
	if (CTimeRewindMgr::Get_Instance()->Get_RewindTime() == false)
	{
		Vec2 vLookAt = CCamera::Get_Instance()->Get_LookAt();
		HDC hMapDC = CBmpMgr::Get_Instance()->Find_Img(L"Stage02");
		HDC hSlowDC = CBmpMgr::Get_Instance()->Find_Img(L"Stage02_Slow");
		
		if (CTimeSlowMgr::Get_Instance()->Get_Slow_Time())
		{
			BitBlt(_hDC, WINCX / 2.0f - vLookAt.fX, WINCY / 2.0f - vLookAt.fY, STAGE02_WIDTH, STAGE02_HEIGHT, hSlowDC, 0, 0, SRCCOPY);
		}
		else
		{
			BitBlt(_hDC, WINCX / 2.0f - vLookAt.fX, WINCY / 2.0f - vLookAt.fY, STAGE02_WIDTH, STAGE02_HEIGHT, hMapDC, 0, 0, SRCCOPY);
		}
		


		CObjMgr::Get_Instance()->Render(_hDC);
		CUIMgr::Get_Instance()->Render(_hDC);
		//CLineMgr::Get_Instance()->Render(_hDC);

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

		if (m_pPlayer->Get_Info().fX >= 1100)
		{
			CReplayMgr::Get_Instance()->Set_Full_Frame(m_llFrameCount);
			CReplayMgr::Get_Instance()->Set_Scene_Height(STAGE02_HEIGHT);
			CReplayMgr::Get_Instance()->Set_Scene_Width(STAGE02_WIDTH);
			
			CSceneMgr::Get_Instance()->Change_Scene(SCENE_ID::SC_REPLAY);
		}
	}
	else
	{
		Print_Store_Mementos(_hDC);
		--m_llFrameCount;
		if (m_llFrameCount == 0)
		{
			CSceneMgr::Get_Instance()->Renew_Scene(SCENE_ID::SC_STAGE_02);
		}
	}
}

void CStage02::Release()
{
	CCamera::Destroy_Instance();
	CLineMgr::Destroy_Instance();
	CUIMgr::Destroy_Instance();
	
}

void CStage02::Print_Store_Mementos(HDC _hDC)
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
	HDC hMapDC = CBmpMgr::Get_Instance()->Find_Img(L"Stage02");

	BitBlt(_hDC, WINCX / 2.0f - vLookAt.fX, WINCY / 2.0f - vLookAt.fY, STAGE02_WIDTH, STAGE02_HEIGHT, hMapDC, 0, 0, SRCCOPY);


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

void CStage02::Store_Mementos()
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
	list<CObj*> m_pObjThrownExplosiveList = CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_EXPLOSIVE_THROW);
	
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

	for (auto iter = m_pObjThrownExplosiveList.begin(); iter != m_pObjThrownExplosiveList.end(); ++iter)
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
