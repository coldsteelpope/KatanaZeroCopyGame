#include "pch.h"
#include "BossStage02.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "UIMgr.h"
#include "LineMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "MouseMgr.h"
#include "AbstractFactory.h"
#include "Boss2.h"
#include "TileMgr.h"
#include "CameraCareTaker.h"
#include "CameraMemento.h"
#include "PlayerCareTaker.h"
#include "Memento.h"
#include "BossCareTaker.h"
#include "BossMemento.h"
#include "BloodCareTaker.h"
#include "BloodMemento.h"
#include "ItemCareTaker.h"
#include "ItemMemento.h"
#include "TimeRewindMgr.h"
#include "SceneMgr.h"
#include "TimeSlowMgr.h"
#include "HighlightMgr.h"
#include "ThunderBreathingMgr.h"
#include "KeyMgr.h"
#include "Samurai.h"

#define BOSS_STAGE_02_WIDTH			1028
#define BOSS_STAGE_02_HEIGHT		600

#define PLAYER_START_POS_FX			300
#define PLAYER_START_POS_FY			0

#define ENEMY_START_POS_FX			700
#define ENEMY_START_POS_FY			400

CBossStage02::CBossStage02()
{
	ZeroMemory(&m_tPortalInfo, sizeof(INFO));
	ZeroMemory(&m_tPortalRect, sizeof(RECT));

	m_tPortalInfo.fX = 515;
	m_tPortalInfo.fY = 380;
	m_tPortalInfo.fCX = 60;
	m_tPortalInfo.fCY = 80;

	//CSoundMgr::Get_Instance()->StopAll();
	//CSoundMgr::Get_Instance()->PlaySound(L"")
}

CBossStage02::~CBossStage02()
{
}

void CBossStage02::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/map/BS_2.bmp", L"BS2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/map/BS_2_slow.bmp", L"BS2_Slow");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/effect/keyboard/SPACE_BAR.bmp", L"SPACE_BAR");


	// Player
	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_PLAYER, CAbstractFactory<CPlayer>::Create(PLAYER_START_POS_FX, PLAYER_START_POS_FY, PLAYER_IDLE_FCX, PLAYER_IDLE_FCY));
	m_pPlayer = CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_PLAYER).front();
	CMouseMgr::Get_Instance()->Set_Target(m_pPlayer);

	CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_BOSS, CAbstractFactory<CBoss2>::Create(ENEMY_START_POS_FX, ENEMY_START_POS_FY + 15));
	CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_BOSS).front()->Set_Target(m_pPlayer);

	CCamera::Get_Instance()->Set_LookAt(WINCX / 2.0 + 110, WINCY / 2.0f);
	CCamera::Get_Instance()->Set_Camera_Target(m_pPlayer);
	CCamera::Get_Instance()->Set_Limit_X(BOSS_STAGE_02_WIDTH);
	CCamera::Get_Instance()->Set_Limit_Y(BOSS_STAGE_02_HEIGHT);

	CUIMgr::Get_Instance()->Initialize();
	CUIMgr::Get_Instance()->Set_Player(m_pPlayer);

	CLineMgr::Get_Instance()->Initialize();
	
	CTileMgr::Get_Instance()->Set_Width(BOSS_STAGE_02_WIDTH);
	CTileMgr::Get_Instance()->Set_Height(BOSS_STAGE_02_HEIGHT);
	CTileMgr::Get_Instance()->Initialize();

	

	backgroundMusic = L"bossbgm.wav";

	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlaySound(backgroundMusic, SOUND_BGM, 1.f);


}

int CBossStage02::Update()
{
	if (CTimeRewindMgr::Get_Instance()->Get_RewindTime() == false)
	{
		CCamera::Get_Instance()->Update();
		CLineMgr::Get_Instance()->Update();
		CObjMgr::Get_Instance()->Update();
		CTileMgr::Get_Instance()->Update();

		if (m_iBossHP <= 0)
		{
			bool b1 = static_cast<CBoss2*>(CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_BOSS).front())->Get_Boss_Cur_Status() != BOSS_STATUS::BOSS_DEAD_BODY_LEFT;
			bool b2 = static_cast<CBoss2*>(CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_BOSS).front())->Get_Boss_Cur_Status() != BOSS_STATUS::BOSS_DEAD_BODY_RIGHT;
			bool b3 = static_cast<CBoss2*>(CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_BOSS).front())->Get_Boss_Cur_Status() != BOSS_STATUS::BOSS_NO_HEAD_DEAD_BODY_LEFT;
			bool b4 = static_cast<CBoss2*>(CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_BOSS).front())->Get_Boss_Cur_Status() != BOSS_STATUS::BOSS_NO_HEAD_DEAD_BODY_RIGHT;

			CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);

			if (b1 && b2 && b3 && b4)
			{
				OBJ_DIR eBossObjDir = static_cast<CBoss2*>(CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_BOSS).front())->Get_Obj_Cur_Dir();
				switch (eBossObjDir)
				{
				case OBJ_DIR::LEFT:
				{
					static_cast<CBoss2*>(CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_BOSS).front())->Set_Cur_Boss_Status(BOSS_STATUS::BOSS_LAY_DOWN_LEFT);
					break;
				}
				case OBJ_DIR::RIGHT:
				{
					static_cast<CBoss2*>(CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_BOSS).front())->Set_Cur_Boss_Status(BOSS_STATUS::BOSS_LAY_DOWN_RIGHT);
					break;
				}
				}
			}

		}
	}

	
	return 0;
}

void CBossStage02::Late_Update()
{
	if (m_pPlayer->Get_Info().fY >= 350.f)
	{
		static_cast<CBoss2*>(CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_BOSS).front())->Set_Start();
	}

	if (CTimeRewindMgr::Get_Instance()->Get_RewindTime() == false)
	{
		CCamera::Get_Instance()->Late_Update();
		CLineMgr::Get_Instance()->Late_Update();
		CObjMgr::Get_Instance()->Late_Update();
		CTileMgr::Get_Instance()->Late_Update();
		Store_Mementos();
		++m_llFrameCount;
	}

	
	int iBossHeadListSize = CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_BOSS_HEAD).size();
	if (m_bBossHeadAppear == false && iBossHeadListSize > 0)
	{

		m_bBossHeadAppear = true;
		Update_Portal_Rect();
	}

	if (m_bBossHeadAppear == true)
	{
		RECT temp;
		RECT tPlayerCollideRect = m_pPlayer->Get_Collide_Rect();
		if (IntersectRect(&temp, &tPlayerCollideRect, &(m_tPortalRect)))
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
			{
				int a = 3;
				if (m_bAppearSamurai == false)
				{
					CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_SAMURAI, CAbstractFactory<CSamurai>::Create(m_tPortalInfo.fX, m_tPortalInfo.fY));
				}

			}
		}
	}


}

void CBossStage02::Render(HDC _hDC)
{
	if (CTimeRewindMgr::Get_Instance()->Get_RewindTime() == false)
	{
		Vec2 vLookAt = CCamera::Get_Instance()->Get_LookAt();
		HDC hMapDC = CBmpMgr::Get_Instance()->Find_Img(L"BS2");
		HDC hSlowMapDC = CBmpMgr::Get_Instance()->Find_Img(L"BS2_Slow");

		if (CTimeSlowMgr::Get_Instance()->Get_Slow_Time())
		{
			BitBlt(_hDC, WINCX / 2.0f - vLookAt.fX, WINCY / 2.0f - vLookAt.fY, BOSS_STAGE_02_WIDTH, BOSS_STAGE_02_HEIGHT, hSlowMapDC, 0, 0, SRCCOPY);
		}
		else
		{
			BitBlt(_hDC, WINCX / 2.0f - vLookAt.fX, WINCY / 2.0f - vLookAt.fY, BOSS_STAGE_02_WIDTH, BOSS_STAGE_02_HEIGHT, hMapDC, 0, 0, SRCCOPY);
		}

		
		CUIMgr::Get_Instance()->Render(_hDC);
		CObjMgr::Get_Instance()->Render(_hDC);

		Vec2 colliderLeftTop = CCamera::Get_Instance()->GetRenderPos(Vec2{ (float)m_tPortalRect.left, (float)m_tPortalRect.top });
		Vec2 colliderRightBottom = CCamera::Get_Instance()->GetRenderPos(Vec2{ (float)m_tPortalRect.right, (float)m_tPortalRect.bottom });
		//::Rectangle(_hDC, colliderLeftTop.fX, colliderLeftTop.fY, colliderRightBottom.fX, colliderRightBottom.fY);

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

	}
	else
	{
		Print_Store_Mementos(_hDC);
		--m_llFrameCount;
		if (m_llFrameCount == 0)
		{
			CSceneMgr::Get_Instance()->Renew_Scene(SCENE_ID::SC_BOSS_02);
		}
	}
}

void CBossStage02::Release()
{
	CBmpMgr::Destroy_Instance();
	CLineMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
	CTileMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
	CPlayerCareTaker::Destroy_Instance();
	CItemCareTaker::Destroy_Instance();
	CBossCareTaker::Destroy_Instance();
	CEffectCareTaker::Destroy_Instance();

}

void CBossStage02::Print_Store_Mementos(HDC _hDC)
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
	HDC hMapDC = CBmpMgr::Get_Instance()->Find_Img(L"BS2");

	BitBlt(_hDC, WINCX / 2.0f - vLookAt.fX, WINCY / 2.0f - vLookAt.fY, BOSS_STAGE_02_WIDTH, BOSS_STAGE_02_HEIGHT, hMapDC, 0, 0, SRCCOPY);


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


	// Boss 가져오기
	if (CBossCareTaker::Get_Instance()->Get_Memento_Size() != 0)
	{
		CBossMemento* pLastMemento = CBossCareTaker::Get_Instance()->Back();
		while (pLastMemento->Get_Frame_Count() == m_llFrameCount)
		{
			pLastMemento = CBossCareTaker::Get_Instance()->Roll_Back();
			pLastMemento->Print_Memento(_hDC);
			Safe_Delete<CBossMemento*>(pLastMemento);
			if (CBossCareTaker::Get_Instance()->Get_Memento_Size() != 0)
			{
				pLastMemento = CBossCareTaker::Get_Instance()->Back();
			}
			else
			{
				break;
			}
		}
	}
}

void CBossStage02::Store_Mementos()
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

	// 보스 저장
	list<CObj*> m_pObjBossList = CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_BOSS);
	for (auto iter = m_pObjBossList.begin(); iter != m_pObjBossList.end(); ++iter)
	{
		CObj* pObj = (*iter);
		CBossMemento* pCurrentMemento = new CBossMemento(
			pObj->Get_Frame(),
			pObj->Get_Frame_Key(),
			pObj->Get_Render_Rect(),
			pObj->Get_Info(),
			pObj->Get_Obj_Cur_Dir(),
			m_llFrameCount
		);
		CBossCareTaker::Get_Instance()->Add_Memento(pCurrentMemento);
	}
}

void CBossStage02::Update_Portal_Rect()
{
	m_tPortalRect.left = (long)(m_tPortalInfo.fX - m_tPortalInfo.fCX / 2.0f);
	m_tPortalRect.top = (long)(m_tPortalInfo.fY - m_tPortalInfo.fCY / 2.0f);
	m_tPortalRect.right = (long)(m_tPortalInfo.fX + m_tPortalInfo.fCX / 2.0f);
	m_tPortalRect.bottom = (long)(m_tPortalInfo.fY + m_tPortalInfo.fCY / 2.0f);
}
