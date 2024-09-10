#include "pch.h"
#include "BmpMgr.h"
#include "Stage01.h"
#include "Camera.h"
#include "ObjMgr.h"
#include "Player.h"
#include "LineMgr.h"
#include "Tile.h"
#include "AbstractFactory.h"
#include "TimeRewindMgr.h"
#include "Memento.h"
#include "CameraMemento.h"
#include "PlayerCareTaker.h"
#include "CameraCareTaker.h"
#include "EffectCareTaker.h"
#include "SceneMgr.h"
#include "Grunt.h"
#include "Gangster.h"
#include "MouseMgr.h"
#include "OilDrum.h"
#include "EnemyCareTaker.h"
#include "EnemyMemento.h"
#include "ItemMemento.h"
#include "ItemCareTaker.h"
#include "ReplayMgr.h"
#include "UIMgr.h"
#include "SoundMgr.h"
#include "Pomp.h"
#include "HighlightMgr.h"
#include "BulletEffect.h"
#include "TimeSlowMgr.h"
#include "BloodMemento.h"
#include "DoorMemento.h"
#include "BloodCareTaker.h"
#include "DoorCareTaker.h"
#include "SoundMgr.h"
#include "ThunderBreathingMgr.h"
#include "Bullet.h"
#include "BulletMemento.h"
#include "BulletCareTaker.h"

#include "SkillEffect.h"

#define STAGE01_WIDTH		1280
#define STAGE01_HEIGHT		640

#define PLAYER_START_POS_FX		200
#define PLAYER_START_POS_FY		525

float		g_fVolume = 1.f;

#define GAS_ROOM_POS_FY		295

CStage01::CStage01()
{
}

CStage01::~CStage01()
{
	Release();
}

void CStage01::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/map/Stage01.bmp", L"Stage01");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/explosion/EXPLOSION.bmp", L"EXPLOSION");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/item/oil_drum.bmp", L"OIL_DRUM");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/item/explosive.bmp", L"EXPLOSIVE");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/map/Stage01_slow.bmp", L"Stage01Slow");
	


	// Player
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_PLAYER, CAbstractFactory<CPlayer>::Create(PLAYER_START_POS_FX, PLAYER_START_POS_FY, PLAYER_IDLE_FCX, PLAYER_IDLE_FCY));
	m_pPlayer = CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_PLAYER).front();
	CMouseMgr::Get_Instance()->Set_Target(m_pPlayer);

	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_EXPLOSIVE, CAbstractFactory<CExplosive>::Create(500, 295, EXPLOSIVE_TYPE::EXPLOSIVE_PICK_TYPE));
	
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CPomp>::Create(PLAYER_START_POS_FX + 250, PLAYER_START_POS_FY, POMP_IDLE_FCX, POMP_IDLE_FCY, OBJ_DIR::RIGHT, ENEMY_TYPE::WALK_TYPE, PLAYER_START_POS_FX + 200, PLAYER_START_POS_FX + 400));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CGrunt>::Create(PLAYER_START_POS_FX + 270, PLAYER_START_POS_FY, POMP_IDLE_FCX, POMP_IDLE_FCY, OBJ_DIR::LEFT, ENEMY_TYPE::WALK_TYPE, PLAYER_START_POS_FX + 200, PLAYER_START_POS_FX + 400));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CPomp>::Create(PLAYER_START_POS_FX + 290, PLAYER_START_POS_FY, POMP_IDLE_FCX, POMP_IDLE_FCY, OBJ_DIR::RIGHT, ENEMY_TYPE::WALK_TYPE, PLAYER_START_POS_FX + 200, PLAYER_START_POS_FX + 400));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CPomp>::Create(PLAYER_START_POS_FX + 310, PLAYER_START_POS_FY, POMP_IDLE_FCX, POMP_IDLE_FCY, OBJ_DIR::LEFT, ENEMY_TYPE::WALK_TYPE, PLAYER_START_POS_FX + 200, PLAYER_START_POS_FX + 400));


	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CGangster>::Create(500, 295, GANGSTER_IDLE_FCX, GANGSTER_IDLE_FCY, OBJ_DIR::RIGHT, ENEMY_TYPE::WALK_TYPE, 400, 800));
	
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CGrunt>::Create(280, GAS_ROOM_POS_FY, GRUNT_IDLE_FCX, GRUNT_IDLE_FCY, OBJ_DIR::RIGHT, ENEMY_TYPE::WALK_TYPE, 250, 500));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_ENEMY, CAbstractFactory<CGrunt>::Create(225, GAS_ROOM_POS_FY, GRUNT_IDLE_FCX, GRUNT_IDLE_FCY, OBJ_DIR::RIGHT, ENEMY_TYPE::WALK_TYPE, 200, 400));

	// FIRE OIL DRUM
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_OIL_DRUM, CAbstractFactory<COilDrum>::Create(245, 295, OIL_DRUM_FCX, OIL_DRUM_FCY));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_OIL_DRUM, CAbstractFactory<COilDrum>::Create(307, 295, OIL_DRUM_FCX, OIL_DRUM_FCY));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_OIL_DRUM, CAbstractFactory<COilDrum>::Create(260, 295, OIL_DRUM_FCX, OIL_DRUM_FCY));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_OIL_DRUM, CAbstractFactory<COilDrum>::Create(310, 295, OIL_DRUM_FCX, OIL_DRUM_FCY));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_OIL_DRUM, CAbstractFactory<COilDrum>::Create(315, 295, OIL_DRUM_FCX, OIL_DRUM_FCY));

	CCamera::Get_Instance()->Set_SmallerX(130.f);
	CCamera::Get_Instance()->Set_LookAt(WINCX / 2.0f + 130.f, WINCY / 2.0f);
	CCamera::Get_Instance()->Set_Camera_Target(m_pPlayer);
	CCamera::Get_Instance()->Set_Limit_X(STAGE01_WIDTH);
	CCamera::Get_Instance()->Set_Limit_Y(STAGE01_HEIGHT);



	CLineMgr::Get_Instance()->Initialize();
	CUIMgr::Get_Instance()->Initialize();
	CUIMgr::Get_Instance()->Set_Player(m_pPlayer);

	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlaySound(L"katanabgm.wav", SOUND_BGM, 1.f);

	backgroundMusic = L"katanabgm.wav";



	//CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_EFFECT, g_fVolume);

	//CSoundMgr::Get_Instance()->PlaySound(L"song_dragon.wav", SOUND_EFFECT, g_fVolume);
}

int CStage01::Update()
{
	if (CTimeRewindMgr::Get_Instance()->Get_RewindTime() == false)
	{
		CCamera::Get_Instance()->Update();
		CObjMgr::Get_Instance()->Update();
		CLineMgr::Get_Instance()->Update();
	}
	return 0;
}

void CStage01::Late_Update()
{
	if (CTimeRewindMgr::Get_Instance()->Get_RewindTime() == false)
	{
		CCamera::Get_Instance()->Late_Update();
		CObjMgr::Get_Instance()->Late_Update();
		CLineMgr::Get_Instance()->Late_Update();
		Store_Mementos();
		++m_llFrameCount;
	}
}

void CStage01::Render(HDC _hDC)
{
	if (CTimeRewindMgr::Get_Instance()->Get_RewindTime() == false)
	{
		Vec2 vLookAt = CCamera::Get_Instance()->Get_LookAt();

		HDC hMapDC = nullptr;
		if (CTimeSlowMgr::Get_Instance()->Get_Slow_Time() || CThunderBreathingMgr::Get_Instance()->Get_Player_Thunder_Breathing_Motion() != PLAYER_THUNDER_BREATHING_MOTION_END)
		{
			hMapDC = CBmpMgr::Get_Instance()->Find_Img(L"Stage01Slow");
		}
		else
		{
			hMapDC = CBmpMgr::Get_Instance()->Find_Img(L"Stage01");
		}

		


		BitBlt(_hDC, WINCX / 2.0f - vLookAt.fX, WINCY / 2.0f - vLookAt.fY, STAGE01_WIDTH, STAGE01_HEIGHT, hMapDC, 0, 0, SRCCOPY);

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
			
			CHighlightMgr::Get_Instance()->Print_Highlight(_hDC, m_Highlight_Target_fX, m_Highlight_Target_fY, 500.f, true);
		}

		// 다음에 들어가기
		if (m_pPlayer->Get_Info().fX >= 1100)
		{
			CReplayMgr::Get_Instance()->Set_Full_Frame(m_llFrameCount);
			CReplayMgr::Get_Instance()->Set_Scene_Height(STAGE01_HEIGHT);
			CReplayMgr::Get_Instance()->Set_Scene_Width(STAGE01_WIDTH);

			CSceneMgr::Get_Instance()->Change_Scene(SCENE_ID::SC_REPLAY);
		}
	}
	else
	{
		Print_Store_Mementos(_hDC);
		--m_llFrameCount;
		if (m_llFrameCount == 0)
		{
			CSceneMgr::Get_Instance()->Renew_Scene(SCENE_ID::SC_STAGE_01);
		}
	}
}


void CStage01::Release()
{
	CLineMgr::Destroy_Instance();
	CCamera::Destroy_Instance();
	CTimeSlowMgr::Destroy_Instance();
	CThunderBreathingMgr::Destroy_Instance();
	CHighlightMgr::Destroy_Instance();
	
	//CPlayerCareTaker::Destroy_Instance();
	//CCameraCareTaker::Destroy_Instance();
	//CEffectCareTaker::Destroy_Instance();
	//CEnemyCareTaker::Destroy_Instance();
	//CItemCareTaker::Destroy_Instance();
}


void CStage01::Print_Store_Mementos(HDC _hDC)
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
	HDC hMapDC = CBmpMgr::Get_Instance()->Find_Img(L"Stage01");

	BitBlt(_hDC, WINCX / 2.0f - vLookAt.fX, WINCY / 2.0f - vLookAt.fY, STAGE01_WIDTH, STAGE01_HEIGHT, hMapDC, 0, 0, SRCCOPY);

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
	
	// 총알 가져오기
	if (CBulletCareTaker::Get_Instance()->Get_Memento_Size() != 0)
	{
		CBulletMemento* pLastMemento = CBulletCareTaker::Get_Instance()->Back();
		while (pLastMemento->Get_Frame_Count() == m_llFrameCount)
		{
			pLastMemento = CBulletCareTaker::Get_Instance()->Roll_Back();
			pLastMemento->Print_Memento(_hDC);
			Safe_Delete<CBulletMemento*>(pLastMemento);

			if (CBulletCareTaker::Get_Instance()->Get_Memento_Size() != 0)
			{
				pLastMemento = CBulletCareTaker::Get_Instance()->Back();
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

void CStage01::Store_Mementos()
{
	// Player Memento 저장
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

	// 총알 저장
	list<CObj*> m_pObjBulletList = CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_BULLET);
	for (auto iter = m_pObjBulletList.begin(); iter != m_pObjBulletList.end(); ++iter)
	{
		CObj* pObj = (*iter);
		CBulletMemento* pCurrentMemento = new CBulletMemento(
			pObj->Get_Frame(),
			pObj->Get_Frame_Key(),
			pObj->Get_Render_Rect(),
			pObj->Get_Info(),
			pObj->Get_Obj_Cur_Dir(),
			m_llFrameCount
		);
		CBulletCareTaker::Get_Instance()->Add_Memento(pCurrentMemento);
	}


}


