#include "pch.h"
#include "Obj.h"
#include "ObjMgr.h"
#include "Effect.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "Mouse.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "LineMgr.h"
#include "TimeSlowMgr.h"
#include "TimeRewindMgr.h"
#include "Line.h"
#include "MouseMgr.h"
#include "Blood.h"
#include "ThunderBreathingMgr.h"
#include "SoundMgr.h"
#include "HighlightMgr.h"

#define SKILL_EFFECT_FCX 800
#define SKILL_EFFECT_FCY 176


CPlayer::CPlayer()
{
	ZeroMemory(&m_bInventory, sizeof(bool) * ITEM_TYPE::ITEM_TYPE_END);
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	// Left Right 
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/idle/IDLE_RIGHT.bmp", L"Player_IDLE", OBJ_DIR::RIGHT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/idle/IDLE_LEFT.bmp", L"Player_IDLE", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/idle_to_run/IDLE_TO_RUN_RIGHT.bmp", L"Player_IDLE_TO_RUN", OBJ_DIR::RIGHT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/idle_to_run/IDLE_TO_RUN_LEFT.bmp", L"Player_IDLE_TO_RUN", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/run/RUN_RIGHT.bmp", L"Player_RUN", OBJ_DIR::RIGHT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/run/RUN_LEFT.bmp", L"Player_RUN", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/run_to_idle/RUN_TO_IDLE_LEFT.bmp", L"Player_RUN_TO_IDLE", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/run_to_idle/RUN_TO_IDLE_RIGHT.bmp", L"Player_RUN_TO_IDLE", OBJ_DIR::RIGHT);
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/idle_to_sneak/IDLE_TO_SNEAK_LEFT.bmp", L"Player_IDLE_TO_SNEAK", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/idle_to_sneak/IDLE_TO_SNEAK_RIGHT.bmp", L"Player_IDLE_TO_SNEAK", OBJ_DIR::RIGHT);
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/crouch/CROUCH_LEFT.bmp", L"Player_CROUCH", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/crouch/CROUCH_RIGHT.bmp", L"Player_CROUCH", OBJ_DIR::RIGHT);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/roll/ROLL_LEFT.bmp", L"Player_ROLL", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/roll/ROLL_RIGHT.bmp", L"Player_ROLL", OBJ_DIR::RIGHT);
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/jump/JUMP_LEFT.bmp", L"Player_JUMP", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/jump/JUMP_RIGHT.bmp", L"Player_JUMP", OBJ_DIR::RIGHT);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/fall/FALL_LEFT.bmp", L"Player_FALL", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/fall/FALL_RIGHT.bmp", L"Player_FALL", OBJ_DIR::RIGHT);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/attack/ATTACK_LEFT.bmp", L"Player_Attack", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/attack/ATTACK_RIGHT.bmp", L"Player_Attack", OBJ_DIR::RIGHT);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/effect/dragon/attack/ATTACK_EFFECT_LEFT.bmp", L"Effect_Dragon_Attack", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/effect/dragon/attack/ATTACK_EFFECT_RIGHT.bmp", L"Effect_Dragon_Attack", OBJ_DIR::RIGHT);

	// 잔상
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/emerald/run/RUN_LEFT.bmp", L"Player_RUN_E", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/emerald/run/RUN_RIGHT.bmp", L"Player_RUN_E", OBJ_DIR::RIGHT);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/emerald/roll/ROLL_LEFT.bmp", L"Player_ROLL_E", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/emerald/roll/ROLL_RIGHT.bmp", L"Player_ROLL_E", OBJ_DIR::RIGHT);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/emerald/idle_to_run/IDLE_TO_RUN_LEFT.bmp", L"Player_IDLE_TO_RUN_E", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/emerald/idle_to_run/IDLE_TO_RUN_RIGHT.bmp", L"Player_IDLE_TO_RUN_E", OBJ_DIR::RIGHT);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/emerald/run_to_idle/RUN_TO_IDLE_LEFT.bmp", L"Player_RUN_TO_IDLE_E", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/emerald/run_to_idle/RUN_TO_IDLE_RIGHT.bmp", L"Player_RUN_TO_IDLE_E", OBJ_DIR::LEFT);
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/emerald/attack/ATTACK_LEFT.bmp", L"Player_ATTACK_E", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/emerald/attack/ATTACK_RIGHT.bmp", L"Player_ATTACK_E", OBJ_DIR::RIGHT);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/emerald/jump/JUMP_LEFT.bmp", L"Player_JUMP_E", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/emerald/jump/JUMP_RIGHT.bmp", L"Player_JUMP_E", OBJ_DIR::RIGHT);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/emerald/fall/FALL_LEFT.bmp", L"Player_FALL_E", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/emerald/fall/FALL_RIGHT.bmp", L"Player_FALL_E", OBJ_DIR::RIGHT);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/emerald/flip/FLIP_LEFT.bmp", L"Player_FLIP_E", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/emerald/flip/FLIP_RIGHT.bmp", L"Player_FLIP_E", OBJ_DIR::RIGHT);
	// 잔상

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/wall_grab_right/WALL_GRAB_RIGHT.bmp", L"Player_WALL_GRAB", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/wall_grab_left/WALL_GRAB_LEFT.bmp", L"Player_WALL_GRAB", OBJ_DIR::RIGHT);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/flip/FLIP_LEFT.bmp", L"Player_FLIP", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/flip/FLIP_RIGHT.bmp", L"Player_FLIP", OBJ_DIR::RIGHT);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/rush/RUSH_LEFT.bmp", L"Player_RUSH", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/rush/RUSH_RIGHT.bmp", L"Player_RUSH", OBJ_DIR::RIGHT);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/door_kick/DOOR_KICK_RIGHT.bmp", L"Player_DOOR_KICK", OBJ_DIR::RIGHT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/door_kick/DOOR_KICK_LEFT.bmp", L"Player_DOOR_KICK", OBJ_DIR::LEFT);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/laydown/DRAGON_LAY_DOWN_LEFT.bmp", L"Player_LAY_DOWN", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/laydown/DRAGON_LAY_DOWN_RIGHT.bmp", L"Player_LAY_DOWN", OBJ_DIR::RIGHT);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/laydown/LAY_DOWN_START_LEFT.bmp", L"Player_LAY_DOWN_START", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/laydown/LAY_DOWN_START_RIGHT.bmp", L"Player_LAY_DOWN_START", OBJ_DIR::RIGHT);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/laydown/LAY_DOWN_MIDDLE_LEFT.bmp", L"Player_LAY_DOWN_MIDDLE", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/dragon/normal/laydown/LAY_DOWN_MIDDLE_RIGHT.bmp", L"Player_LAY_DOWN_MIDDLE", OBJ_DIR::RIGHT);


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/effect/dragon/PLAYER_RUN_EFFECT_LEFT.bmp", L"PLAYER_RUN_EFFECT", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/effect/dragon/PLAYER_RUN_EFFECT_RIGHT.bmp", L"PLAYER_RUN_EFFECT", OBJ_DIR::RIGHT);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/effect/dragon/FullMoon.bmp", L"PLAYER_FULL_MOON");
	


	m_tRunEffectFrame.iFrameStart = 0;
	m_tRunEffectFrame.iFrameEnd = 9;
	m_tRunEffectFrame.dwTime = GetTickCount();
	m_tRunEffectFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;

	m_eObjCurDir = OBJ_DIR::RIGHT;
	m_eObjPreDir = OBJ_DIR::OBJ_DIR_END;
	m_eObjCurStatus = OBJ_STATUS::IDLE;
	m_eObjPreStatus = OBJ_STATUS::OBJ_STATUS_END;

	m_pFrameKey = L"Player_IDLE";
	m_fSpeed = 5;
	m_fPower = 10.0f; // 10.0f이 좋음
	m_fDegree = 90;
	m_fJumpTime = 0.f;
	m_fJumpLeftRightSpeed = 2.0f;
	m_fFlipSpeed = 10.0f;

	m_tCollideInfo.fX = m_tInfo.fX;
	m_tCollideInfo.fY = m_tInfo.fY;
	m_tCollideInfo.fCX = PLAYER_IDLE_FCX;
	m_tCollideInfo.fCY = PLAYER_IDLE_FCY;
	
	// Attack Radius
	m_fAttackRadius = 16.0f;
	m_fAttackAreaHeight = PLAYER_ATTACK_FCY;

	m_bInventory[ITEM_TYPE::ITEM_EXPLOSIVE] = true;
}

int CPlayer::Update()
{
	if (CThunderBreathingMgr::Get_Instance()->Get_ThunderBreathing_Mode() == true)
	{
		// 벽력 일섬 모드일 때

		switch (CThunderBreathingMgr::Get_Instance()->Get_Player_Thunder_Breathing_Motion())
		{
		case PLAYER_THUNDER_BREATHING_MOTION::PLAYER_IDLE_TO_CROUCH:
		{
			m_eObjCurStatus = OBJ_STATUS::IDLE_TO_SNEAK;
			m_tInfo.fCX = PLAYER_IDLE_TO_SNEAK_FCX;
			m_tInfo.fCY = PLAYER_IDLE_TO_SNEAK_FCY;
			m_pFrameKey = L"Player_IDLE_TO_SNEAK";
			CObj::Update_Rect();
			CObj::Update_Render_Rect();
			CPlayer::Update_Collide_Rect();
			
			if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eObjCurStatus == m_eObjPreStatus)
			{
				CThunderBreathingMgr::Get_Instance()->Set_Player_Thunder_Breathing_Motion(PLAYER_THUNDER_BREATHING_MOTION::PLAYER_CROUCH);
			}
			
			break;
		}
		case PLAYER_THUNDER_BREATHING_MOTION::PLAYER_CROUCH:
		{
			m_eObjCurStatus = OBJ_STATUS::CROUCH;
			m_tInfo.fCX = PLAYER_CROUCH_FCX;
			m_tInfo.fCY = PLAYER_CROUCH_FCY;
			m_pFrameKey = L"Player_CROUCH";
			CObj::Update_Rect();
			CObj::Update_Render_Rect();
			CPlayer::Update_Collide_Rect();
			
			if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eObjCurStatus == m_eObjPreStatus)
			{
				CThunderBreathingMgr::Get_Instance()->Set_Player_Thunder_Breathing_Motion(PLAYER_THUNDER_BREATHING_MOTION::PLAYER_SCRIPT);
			}

			break;
		}
		case PLAYER_THUNDER_BREATHING_MOTION::PLAYER_SCRIPT:
		{
			// 여기에 대사 추가하기

			CThunderBreathingMgr::Get_Instance()->Set_Say_Script();

			m_eObjCurStatus = OBJ_STATUS::CROUCH;
			m_tInfo.fCX = PLAYER_CROUCH_FCX;
			m_tInfo.fCY = PLAYER_CROUCH_FCY;
			m_pFrameKey = L"Player_CROUCH";
			CObj::Update_Rect();
			CObj::Update_Render_Rect();
			CPlayer::Update_Collide_Rect();

			if (CThunderBreathingMgr::Get_Instance()->Get_ScriptTime() + 8000 < GetTickCount())
			{
				if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eObjCurStatus == m_eObjPreStatus)
				{
					float fSmoothX = CHighlightMgr::Get_Instance()->Get_SmoothX();
					if (fSmoothX <= 0.4f)
					{
						CThunderBreathingMgr::Get_Instance()->Set_Player_Thunder_Breathing_Motion(PLAYER_THUNDER_BREATHING_MOTION::PLAYER_ATTACK_BEFORE);
					}
				}
			}

		}
		case PLAYER_THUNDER_BREATHING_MOTION::PLAYER_ATTACK_BEFORE:
		{
			float fSmoothX = CHighlightMgr::Get_Instance()->Get_SmoothX();
			if (fSmoothX >= 2.0f)
			{
				CThunderBreathingMgr::Get_Instance()->Set_Player_Thunder_Breathing_Motion(PLAYER_THUNDER_BREATHING_MOTION::PLAYER_ATTACK);
				
			}
			break;
			
		}
		
		case PLAYER_THUNDER_BREATHING_MOTION::PLAYER_ATTACK:
		{
			m_eObjCurStatus = OBJ_STATUS::THUNDER_BREATHING_PROCESS;
			m_tInfo.fCX = PLAYER_ATTACK_FCX;
			m_tInfo.fCY = PLAYER_ATTACK_FCY;
			m_pFrameKey = L"Player_Attack";
			CObj::Update_Rect();
			CObj::Update_Render_Rect();
			CPlayer::Update_Collide_Rect();

			CThunderBreathingMgr::Get_Instance()->Set_Thunder_Breathing_Mode_Off_Temp();

			break;
		}
		}

		return OBJ_NO_EVENT;
	}
	else
	{
		N_Key_Input();
		switch (m_eObjCurStatus)
		{

		case OBJ_STATUS::LAY_DOWN:
		{
			R_Key_Button_Key_Input();

			CObj::Update_Rect();
			CObj::Update_Render_Rect();
			ZeroMemory(&m_tCollideRect, sizeof(RECT));
			break;
		}
		case OBJ_STATUS::LAY_DOWN_MIDDLE:
		{
			R_Key_Button_Key_Input();

			CObj::Update_Rect();
			CObj::Update_Render_Rect();
			ZeroMemory(&m_tCollideRect, sizeof(RECT));
			break;
		}
		case OBJ_STATUS::LAY_DOWN_START:
		{
			R_Key_Button_Key_Input();

			CObj::Update_Rect();
			CObj::Update_Render_Rect();
			ZeroMemory(&m_tCollideRect, sizeof(RECT));
			break;
		}
		default:
		{
			Key_Input();
			if (R_Key_Button_Key_Input())
			{
				return OBJ_EVENT_REWIND;
			}

			CObj::Update_Rect();
			CObj::Update_Render_Rect();
			CObj::Update_Collide_Rect();

			CPlayer::Update_Player_Collide();
			return OBJ_NO_EVENT;
		}
		}
	}
}

void CPlayer::Late_Update()
{
	if (CThunderBreathingMgr::Get_Instance()->Get_Player_Thunder_Breathing_Motion() != PLAYER_THUNDER_BREATHING_MOTION::PLAYER_THUNDER_BREATHING_MOTION_END)
	{
		Motion_Change();
		Thunder_Breathing_Manage_Status();
		__super::Move_Frame();

		CObj::Check_Delete_After_Image();
		CPlayer::Move_Run_Effect_Frame();
	}
	else
	{
		switch (m_eObjCurStatus)
		{
		case OBJ_STATUS::WALL_GRAB:
		{
			break;
		}
		case OBJ_STATUS::THUNDER_BREATHING:
		{
			break;
		}
		case OBJ_STATUS::SLASH:
		{

			break;
		}
		default:
		{
			Jump();
			break;
		}
		}

		Motion_Change();
		Manage_Status();

		switch (m_eObjCurStatus)
		{
		case OBJ_STATUS::LAY_DOWN:
		{
			if (m_tFrame.iFrameStart != m_tFrame.iFrameEnd)
			{
				__super::Move_Frame();
				CObj::Check_Delete_After_Image();
				CPlayer::Move_Run_Effect_Frame();
			}
			break;
		}
		default:
		{
			__super::Move_Frame();
			CObj::Check_Delete_After_Image();
			break;
		}
		}
	}
}

void CPlayer::Render(HDC _hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey, m_eObjCurDir);
	// Print Attack Area
	//::Rectangle(_hDC, m_tAttackAreaRenderRect.left, m_tAttackAreaRenderRect.top, m_tAttackAreaRenderRect.right, m_tAttackAreaRenderRect.bottom);
	
	// Print Collide Area
	//Vec2 renderCollideRectLeftTop = CCamera::Get_Instance()->GetRenderPos(Vec2{ (float)m_tPlayerCollideRect.left, (float)m_tPlayerCollideRect.top });
	//Vec2 renderCollideRectBottomRight = CCamera::Get_Instance()->GetRenderPos(Vec2{ (float)m_tPlayerCollideRect.right, (float)m_tPlayerCollideRect.bottom });
	//::Rectangle(_hDC, renderCollideRectLeftTop.fX, renderCollideRectLeftTop.fY, renderCollideRectBottomRight.fX, renderCollideRectBottomRight.fY);




	// 잔상 출력하기
	for (auto& iter = m_pAfterImageList.begin(); iter != m_pAfterImageList.end(); ++iter)
	{
		AFTER_IMAGE_INFO tAfterImageInfo = (*iter);
		LONG tAfterImageInfoLeft = tAfterImageInfo.fX - (tAfterImageInfo.fCX / 2.0f);
		LONG tAfterImageInfoTop = tAfterImageInfo.fY - (tAfterImageInfo.fCY / 2.0f);

		HDC hAfterImageDC = nullptr;

		if (lstrcmp(L"Player_RUN", tAfterImageInfo.m_pFrameKey) == 0)
		{
			hAfterImageDC = CBmpMgr::Get_Instance()->Find_Img(L"Player_RUN_E", tAfterImageInfo.m_eObjDir);
		}
		else if (lstrcmp(L"Player_ROLL", tAfterImageInfo.m_pFrameKey) == 0)
		{
			hAfterImageDC = CBmpMgr::Get_Instance()->Find_Img(L"Player_ROLL_E", tAfterImageInfo.m_eObjDir);
		}
		else if (lstrcmp(L"Player_IDLE_TO_RUN", tAfterImageInfo.m_pFrameKey) == 0)
		{
			hAfterImageDC = CBmpMgr::Get_Instance()->Find_Img(L"Player_IDLE_TO_RUN_E", tAfterImageInfo.m_eObjDir);
		}
		else if (lstrcmp(L"Player_RUN_TO_IDLE", tAfterImageInfo.m_pFrameKey) == 0)
		{
			hAfterImageDC = CBmpMgr::Get_Instance()->Find_Img(L"Player_RUN_TO_IDLE_E", tAfterImageInfo.m_eObjDir);
		}
		else if (lstrcmp(L"Player_Attack", tAfterImageInfo.m_pFrameKey) == 0)
		{
			hAfterImageDC = CBmpMgr::Get_Instance()->Find_Img(L"Player_ATTACK_E", tAfterImageInfo.m_eObjDir);
		}
		else if (lstrcmp(L"Player_JUMP", tAfterImageInfo.m_pFrameKey) == 0)
		{
			hAfterImageDC = CBmpMgr::Get_Instance()->Find_Img(L"Player_JUMP_E", tAfterImageInfo.m_eObjDir);
		}
		else if (lstrcmp(L"Player_FALL", tAfterImageInfo.m_pFrameKey) == 0)
		{
			hAfterImageDC = CBmpMgr::Get_Instance()->Find_Img(L"Player_FALL_E", tAfterImageInfo.m_eObjDir);
		}
		else if (lstrcmp(L"Player_FLIP", tAfterImageInfo.m_pFrameKey) == 0)
		{
			hAfterImageDC = CBmpMgr::Get_Instance()->Find_Img(L"Player_FLIP_E", tAfterImageInfo.m_eObjDir);
		}


		if (lstrcmp(L"Player_FLIP", tAfterImageInfo.m_pFrameKey) == 0)
		{
			GdiTransparentBlt(
				_hDC,
				tAfterImageInfoLeft,
				tAfterImageInfoTop,
				(int)tAfterImageInfo.fCX,
				(int)tAfterImageInfo.fCY,
				hAfterImageDC,
				tAfterImageInfo.fCX * tAfterImageInfo.iFrameStart,
				tAfterImageInfo.fCY * tAfterImageInfo.iMotion,
				tAfterImageInfo.fCX,
				tAfterImageInfo.fCY,
				RGB(254, 6, 254)
			);
		}
		else
		{
			GdiTransparentBlt(
				_hDC,
				tAfterImageInfoLeft,
				tAfterImageInfoTop,
				(int)tAfterImageInfo.fCX,
				(int)tAfterImageInfo.fCY,
				hAfterImageDC,
				tAfterImageInfo.fCX * tAfterImageInfo.iFrameStart,
				tAfterImageInfo.fCY * tAfterImageInfo.iMotion,
				tAfterImageInfo.fCX,
				tAfterImageInfo.fCY,
				RGB(254, 0, 254)
			);
		}
	}

	
	if (CThunderBreathingMgr::Get_Instance()->Get_Player_Thunder_Breathing_Motion() == PLAYER_THUNDER_BREATHING_MOTION::PLAYER_ATTACK)
	{
		THUNDER_BREATHING_INFO tThunderBreathingInfo = CThunderBreathingMgr::Get_Instance()->Get_Thunder_Breathing_Info();

		HPEN pen = (HPEN)::CreatePen(PS_DASH, 3, RGB(0, 210, 228));
		HPEN oldPen = (HPEN)::SelectObject(_hDC, pen);

		Vec2 renderPos0 = CCamera::Get_Instance()->GetRenderPos(Vec2{ (float)tThunderBreathingInfo.m_fThunderBreathingX0 , (float)tThunderBreathingInfo.m_fThunderBreathingY0 });
		Vec2 renderPos1 = CCamera::Get_Instance()->GetRenderPos(Vec2{ (float)tThunderBreathingInfo.m_fThunderBreathingX1 , (float)tThunderBreathingInfo.m_fThunderBreathingY1 });


		::MoveToEx(_hDC, renderPos0.fX, renderPos0.fY, nullptr);
		::LineTo(_hDC, renderPos1.fX, renderPos1.fY);
		::SelectObject(_hDC, oldPen);
		::DeleteObject(pen);
	}
	


	// 잔상 출력하기
	switch (m_eObjCurStatus)
	{
	default:
	{
		GdiTransparentBlt(
			_hDC,
			m_tRenderRect.left,
			m_tRenderRect.top,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hMemDC,
			(int)m_tInfo.fCX* m_tFrame.iFrameStart,
			(int)m_tInfo.fCY* m_tFrame.iMotion,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 0, 255)
		);
		break;
	}
	}



}

void CPlayer::Release()
{
}

void CPlayer::Jump()
{
	if (m_eObjCurStatus == OBJ_STATUS::FLIP)
	{
		int a = 3;
	}

	if (m_eObjCurStatus == OBJ_STATUS::JUMP)
	{
		return;
	}
	
	float fY(0.f); // not foot


	if (m_eObjCurStatus == OBJ_STATUS::FALL)
	{
		int a = 3;
	}

	bool bValidY = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_fSpeed, m_tInfo.fY, m_tInfo.fCY, &fY, m_eObjCurStatus);

	switch (m_eObjCurStatus)
	{
	case OBJ_STATUS::ATTACK:
	{
		m_tInfo.fY = m_tInfo.fY + (0.5f * 9.8f * m_fJumpTime * m_fJumpTime);
		m_fJumpTime += 0.1f;

		if (m_tInfo.fY + (m_tInfo.fCY / 2.0f) > fY)
		{
			m_tInfo.fY = m_tInfo.fY - (m_tInfo.fY - fY);
			m_tInfo.fY = m_tInfo.fY - (m_tInfo.fCY / 2.0f);
			m_fJumpTime = 0.f;
			
			CObj::Update_Rect();
			CObj::Update_Attack_Rect();
		}
		break;
	}
	case OBJ_STATUS::FLIP:
	{
		if (m_tInfo.fY + (m_tInfo.fCY / 2.0f) > fY)
		{
			m_tInfo.fY = m_tInfo.fY - (m_tInfo.fY - fY);
			m_tInfo.fY = m_tInfo.fY - (m_tInfo.fCY / 2.0f);
			m_fJumpTime = 0.f;
			m_eObjPreStatus = m_eObjCurStatus;
			m_eObjCurStatus = OBJ_STATUS::IDLE;
			m_pFrameKey = L"Player_IDLE";
			m_tInfo.fCX = PLAYER_IDLE_FCX;
			m_tInfo.fCY = PLAYER_IDLE_FCY;
			CObj::Update_Rect();
		}
		break;
	}

	case OBJ_STATUS::FALL:
	{
		m_tInfo.fY = m_tInfo.fY + (0.5f * 9.8f * m_fJumpTime * m_fJumpTime);
		m_fJumpTime += 0.15f;
		
		if (m_tInfo.fY + (m_tInfo.fCY / 2.0f) > fY)
		{
			m_tInfo.fY = m_tInfo.fY - (m_tInfo.fY - fY);
			m_tInfo.fY = m_tInfo.fY - (m_tInfo.fCY / 2.0f);
			m_fJumpTime = 0.f;
			m_eObjPreStatus = m_eObjCurStatus;
			m_eObjCurStatus = OBJ_STATUS::IDLE;
			m_pFrameKey = L"Player_IDLE";
			m_tInfo.fCX = PLAYER_IDLE_FCX;
			m_tInfo.fCY = PLAYER_IDLE_FCY;
			CObj::Update_Rect();
			CObj::Update_Player_Attack_Rect();

		}
		break;
	}
	default:
	{
		
		if (fY - m_tInfo.fY > 100.f)
		{
			m_eObjPreStatus = m_eObjCurStatus;
			m_eObjCurStatus = OBJ_STATUS::FALL;
			m_pFrameKey = L"Player_FALL";
			m_tInfo.fCX = PLAYER_FALL_FCX;
			m_tInfo.fCY = PLAYER_FALL_FCY;
			
		}
		else
		{
			m_tInfo.fY = fY - m_tInfo.fCY / 2.0f;
		}
		
		break;
	}
	}

}

void CPlayer::Motion_Change()
{
	if (m_eObjPreStatus != m_eObjCurStatus)
	{
		switch (m_eObjCurStatus)
		{
		case OBJ_STATUS::SLASH:
		{
			m_tFrame.iFrameStart = 6;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case OBJ_STATUS::IDLE:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case OBJ_STATUS::IDLE_TO_RUN:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case OBJ_STATUS::RUN:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case OBJ_STATUS::RUN_TO_IDLE:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case OBJ_STATUS::IDLE_TO_SNEAK:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case OBJ_STATUS::CROUCH:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case OBJ_STATUS::ROLL:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case OBJ_STATUS::JUMP:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case OBJ_STATUS::FALL:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case OBJ_STATUS::ATTACK:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case OBJ_STATUS::WALL_GRAB:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case OBJ_STATUS::FLIP:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED * 2;
			break;
		}
		case OBJ_STATUS::THUNDER_BREATHING:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case OBJ_STATUS::DOOR_KICK:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case OBJ_STATUS::THUNDER_BREATHING_PROCESS:
		{
			m_tFrame.iFrameStart = 1;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
		}

		case OBJ_STATUS::LAY_DOWN:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case OBJ_STATUS::LAY_DOWN_START:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case OBJ_STATUS::LAY_DOWN_MIDDLE:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		}
		m_eObjPreStatus = m_eObjCurStatus;
	}

}

void CPlayer::Key_Input()
{
	Left_Key_Input();
	Up_Key_Input();
	Right_Key_Input();
	Down_Key_Input();
	Item_Key_Input();
	Q_Key_Input();
	LButton_Key_Input();
	RButton_Key_Input();
	LShift_Key_Input();

	if (CKeyMgr::Get_Instance()->Key_Down('N'))
	{
		m_bNodeath = true;
	}
}

void CPlayer::Left_Key_Input()
{
	switch (m_eObjCurStatus)
	{
	case OBJ_STATUS::WALL_GRAB:
	{
		
		break;
	}
	default:
	{
		if (CKeyMgr::Get_Instance()->Key_Press('A'))
		{
			m_eObjPreDir = m_eObjCurDir;
			m_eObjCurDir = OBJ_DIR::LEFT;

			switch (m_eObjCurStatus)
			{
			case OBJ_STATUS::IDLE:
			{
				m_tInfo.fX -= m_fSpeed * 0.5f;
				m_eObjPreStatus = m_eObjCurStatus;
				m_eObjCurStatus = OBJ_STATUS::IDLE_TO_RUN;
				m_pFrameKey = L"Player_IDLE_TO_RUN";

				m_tInfo.fCX = PLAYER_IDLE_TO_RUN_FCX;
				m_tInfo.fCY = PLAYER_IDLE_TO_RUN_FCY;
				CObj::Update_Rect();
				break;
			}
			case OBJ_STATUS::RUN:
			{
				m_tInfo.fX -= m_fSpeed;
				break;
			}
			case OBJ_STATUS::ATTACK:
			{
				m_tInfo.fX -= m_fPlayerAttackSpeed;
				break;
			}
			case OBJ_STATUS::JUMP:
			{
				m_tInfo.fX -= m_fJumpLeftRightSpeed;
				break;
			}
			case OBJ_STATUS::FALL:
			{
				m_tInfo.fX -= m_fJumpLeftRightSpeed;
				break;
			}
			}
		}

		if (CKeyMgr::Get_Instance()->Key_Down('A'))
		{

			switch (m_eObjCurStatus)
			{
			case OBJ_STATUS::CROUCH:
			{
				CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"player_roll.wav", PLAYER_EFFECT, 1.f);

				m_eObjPreStatus = m_eObjCurStatus;
				m_eObjCurStatus = OBJ_STATUS::ROLL;
				m_pFrameKey = L"Player_ROLL";

				m_tInfo.fCX = PLAYER_ROLL_FCX;
				m_tInfo.fCY = PLAYER_ROLL_FCY;
				CObj::Update_Rect();
				break;
			}
			}
		}

		if (CKeyMgr::Get_Instance()->Key_Up('A'))
		{
			switch (m_eObjCurStatus)
			{
			case OBJ_STATUS::IDLE_TO_RUN:
			{
				m_eObjPreStatus = m_eObjCurStatus;
				m_eObjCurStatus = OBJ_STATUS::IDLE;
				m_pFrameKey = L"Player_IDLE";

				m_tInfo.fCX = PLAYER_IDLE_FCX;
				m_tInfo.fCY = PLAYER_IDLE_FCY;
				CObj::Update_Rect();
				break;
			}
			case OBJ_STATUS::RUN:
			{
				m_eObjPreStatus = m_eObjCurStatus;
				m_eObjCurStatus = OBJ_STATUS::RUN_TO_IDLE;
				m_pFrameKey = L"Player_RUN_TO_IDLE";

				m_tInfo.fCX = PLAYER_RUN_TO_IDLE_FCX;
				m_tInfo.fCY = PLAYER_RUN_TO_IDLE_FCY;
				CObj::Update_Rect();
				break;
			}

			}
		}
		break;
	}
	}
}

void CPlayer::Right_Key_Input()
{
	switch (m_eObjCurStatus)
	{
	case OBJ_STATUS::WALL_GRAB:
	{

		break;
	}
	default:
	{
		if (CKeyMgr::Get_Instance()->Key_Press('D'))
		{
			
			m_eObjPreDir = m_eObjCurDir;
			m_eObjCurDir = OBJ_DIR::RIGHT;

			switch (m_eObjCurStatus)
			{
			case OBJ_STATUS::IDLE:
			{
				m_tInfo.fX += m_fSpeed * 0.5f;
				m_eObjPreStatus = m_eObjCurStatus;
				m_eObjCurStatus = OBJ_STATUS::IDLE_TO_RUN;
				m_pFrameKey = L"Player_IDLE_TO_RUN";

				m_tInfo.fCX = PLAYER_IDLE_TO_RUN_FCX;
				m_tInfo.fCY = PLAYER_IDLE_TO_RUN_FCY;
				CObj::Update_Rect();
				break;
			}
			case OBJ_STATUS::RUN:
			{
				m_tInfo.fX += m_fSpeed;
				break;
			}
			case OBJ_STATUS::JUMP:
			{
				m_tInfo.fX += m_fJumpLeftRightSpeed;
				break;
			}
			case OBJ_STATUS::FALL:
			{
				m_tInfo.fX += m_fJumpLeftRightSpeed;
				break;
			}
			case OBJ_STATUS::ATTACK:
			{
				m_tInfo.fX += m_fPlayerAttackSpeed;
				break;
			}
			}
		}

		if (CKeyMgr::Get_Instance()->Key_Down('D'))
		{
			switch (m_eObjCurStatus)
			{
			case OBJ_STATUS::CROUCH:
			{
				CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"player_roll.wav", PLAYER_EFFECT, 1.f);

				m_eObjPreStatus = m_eObjCurStatus;
				m_eObjCurStatus = OBJ_STATUS::ROLL;
				m_pFrameKey = L"Player_ROLL";

				m_tInfo.fCX = PLAYER_ROLL_FCX;
				m_tInfo.fCY = PLAYER_ROLL_FCY;
				CObj::Update_Rect();
				break;
			}
			}
		}

		if (CKeyMgr::Get_Instance()->Key_Up('D'))
		{
			switch (m_eObjCurStatus)
			{
			case OBJ_STATUS::IDLE_TO_RUN:
			{
				m_eObjPreStatus = m_eObjCurStatus;
				m_eObjCurStatus = OBJ_STATUS::IDLE;
				m_pFrameKey = L"Player_IDLE";

				m_tInfo.fCX = PLAYER_IDLE_FCX;
				m_tInfo.fCY = PLAYER_IDLE_FCY;
				CObj::Update_Rect();
				break;
			}
			case OBJ_STATUS::RUN:
			{
				m_eObjPreStatus = m_eObjCurStatus;
				m_eObjCurStatus = OBJ_STATUS::RUN_TO_IDLE;
				m_pFrameKey = L"Player_RUN_TO_IDLE";

				m_tInfo.fCX = PLAYER_RUN_TO_IDLE_FCX;
				m_tInfo.fCY = PLAYER_RUN_TO_IDLE_FCY;
				CObj::Update_Rect();
				break;
			}
			case OBJ_STATUS::JUMP:
			{
				break;
			}
			}
		}
	}
	}
}

void CPlayer::Down_Key_Input()
{
	switch (m_eObjCurStatus)
	{
	case OBJ_STATUS::WALL_GRAB:
	{
		
		break;
	}
	default:
	{
		CLine* pCurrentLine = CLineMgr::Get_Instance()->Get_Current_Line();
		if (pCurrentLine == nullptr)
		{
			return;
		}
		if (CKeyMgr::Get_Instance()->Key_Press('S'))
		{
			if (pCurrentLine->Get_Line_Type() == LINE_TYPE::SOLID)
			{
				switch (m_eObjCurStatus)
				{
				case OBJ_STATUS::IDLE:
				{
					m_eObjPreStatus = m_eObjCurStatus;
					m_eObjCurStatus = OBJ_STATUS::IDLE_TO_SNEAK;
					m_pFrameKey = L"Player_IDLE_TO_SNEAK";

					m_tInfo.fCX = PLAYER_IDLE_TO_SNEAK_FCX;
					m_tInfo.fCY = PLAYER_IDLE_TO_SNEAK_FCY;
					CObj::Update_Rect();
					break;
				}
				}
			}
			else if (pCurrentLine->Get_Line_Type() == LINE_TYPE::NORMAL)
			{
				switch (m_eObjCurStatus)
				{
				case OBJ_STATUS::IDLE:
				{
					m_eObjPreStatus = m_eObjCurStatus;
					m_eObjCurStatus = OBJ_STATUS::FALL;
					m_pFrameKey = L"Player_FALL";
					m_tInfo.fY = m_tInfo.fY + m_tInfo.fCY + 3.f; // 여기서 5.f는 하드코딩...
					m_tInfo.fCX = PLAYER_FALL_FCX;
					m_tInfo.fCY = PLAYER_FALL_FCY;
					CObj::Update_Rect();
					break;
				}
				}
			}

		}

		if (CKeyMgr::Get_Instance()->Key_Up('S'))
		{
			switch (m_eObjCurStatus)
			{
			case OBJ_STATUS::IDLE_TO_SNEAK:
			{
				m_eObjPreStatus = m_eObjCurStatus;
				m_eObjCurStatus = OBJ_STATUS::IDLE;
				m_pFrameKey = L"Player_IDLE";
				m_tInfo.fCX = PLAYER_IDLE_FCX;
				m_tInfo.fCY = PLAYER_IDLE_FCY;
				CObj::Update_Rect();
				break;
			}
			case OBJ_STATUS::CROUCH:
			{
				m_eObjPreStatus = m_eObjCurStatus;
				m_eObjCurStatus = OBJ_STATUS::IDLE;
				m_pFrameKey = L"Player_IDLE";
				m_tInfo.fCX = PLAYER_IDLE_FCX;
				m_tInfo.fCY = PLAYER_IDLE_FCY;
				CObj::Update_Rect();
				break;
			}
			}
		}
		break;
	}
	}


}

void CPlayer::Up_Key_Input()
{
	switch (m_eObjCurStatus)
	{
	case OBJ_STATUS::WALL_GRAB:
	{
		if (CKeyMgr::Get_Instance()->Key_Down('W'))
		{
			CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"sound_player_landwire.wav", PLAYER_EFFECT, 1.f);

			m_eObjPreStatus = m_eObjCurStatus;
			m_eObjCurStatus = OBJ_STATUS::FLIP;
			m_pFrameKey = L"Player_FLIP";
			m_tInfo.fCX = PLAYER_FLIP_FCX;
			m_tInfo.fCY = PLAYER_FLIP_FCY;
			m_fJumpTime = 0.f;
			CObj::Update_Rect();
			break;
		}
		break;
	}
	default:
	{
		if (CKeyMgr::Get_Instance()->Key_Down('W'))
		{
			CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"player_jump.wav", PLAYER_EFFECT, 1.f);

			switch (m_eObjCurStatus)
			{
			case OBJ_STATUS::ATTACK:
			{
				break;
			}
			case OBJ_STATUS::THUNDER_BREATHING:
			{
				break;
			}
			case OBJ_STATUS::JUMP:
			{
				break;
			}
			case OBJ_STATUS::FALL:
			{
				break;
			}
			default:
			{
				m_eObjPreStatus = m_eObjCurStatus;

				m_eObjCurStatus = OBJ_STATUS::JUMP;
				m_pFrameKey = L"Player_JUMP";
				m_tInfo.fCX = PLAYER_JUMP_FCX;
				m_tInfo.fCY = PLAYER_JUMP_FCY;
				m_fBeforeY = m_tInfo.fY + (m_tInfo.fCY / 2.0f);
				CObj::Update_Rect();

				break;
			}
			}

		}

		if (CKeyMgr::Get_Instance()->Key_Up('W'))
		{

		}
		break;
	}
	}
}

void CPlayer::Manage_Status()
{
	switch (m_eObjCurStatus)
	{
	case OBJ_STATUS::SLASH:
	{
		m_pFrameKey = L"Player_Attack";
		m_tInfo.fCX = PLAYER_ATTACK_FCX;
		m_tInfo.fCY = PLAYER_ATTACK_FCY;
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		Motion_Change();
		
		float x0 = m_fMyInitPosX;
		float x1 = m_fSlashTargetX;
		float y0 = m_fMyInitPosY;
		float y1 = m_fSlashTargetY;
		float fScope = (y1 - y0) / (x1 - x0);

		switch (m_eSlashDir)
		{
		case LEFT:
		{
			m_tInfo.fX -= 10;
			m_tInfo.fY = (fScope) * (m_tInfo.fX - x0) + y0;
			
			bool bValidX = m_tInfo.fX <= m_fSlashTargetX;
			bool bValidY = false;
			switch (m_eSlashTopDown)
			{
			case TOP:
			{
				bValidY = m_tInfo.fY <= m_fSlashTargetY;
				break;
			}
			case DOWN:
			{
				bValidY = m_tInfo.fY >= m_fSlashTargetY;
				break;
			}
			}

			if (bValidX)
			{
				m_tInfo.fX = m_fSlashTargetX;
			}

			if (bValidY)
			{
				m_tInfo.fY = m_fSlashTargetY;
			}

			if (m_tInfo.fX == m_fSlashTargetX && m_tInfo.fY == m_fSlashTargetY)
			{
				m_eObjCurStatus = OBJ_STATUS::THUNDER_BREATHING;
				m_pFrameKey = L"Player_RUSH";
				m_tInfo.fCX = RANGE_RUSH_FCX;
				m_tInfo.fCY = RANGE_RUSH_FCY;
				CObj::Update_Rect();
				CObj::Update_Render_Rect();
				CObj::Update_Collide_Rect();
				m_fSlashTime = 0.f;

			}
			break;
		}
		case RIGHT:
		{
			m_tInfo.fX += 10;
			m_tInfo.fY = (fScope) * (m_tInfo.fX - x0) + y0;

			bool bValidX = m_fSlashTargetX <= m_tInfo.fX;
			bool bValidY = false;

			switch (m_eSlashTopDown)
			{
			case OBJ_TOP_DOWN_STATUS::TOP:
			{
				bValidY = m_tInfo.fY <= m_fSlashTargetY;
				break;
			}
			case OBJ_TOP_DOWN_STATUS::DOWN:
			{
				bValidY = m_tInfo.fY >= m_fSlashTargetY;
				break;
			}
			}

			if (bValidX)
			{
				m_tInfo.fX = m_fSlashTargetX;
			}

			if (bValidY)
			{
				m_tInfo.fY = m_fSlashTargetY;
			}

			if (m_tInfo.fY == m_fSlashTargetY && m_tInfo.fX == m_fSlashTargetX)
			{
				m_eObjCurStatus = OBJ_STATUS::THUNDER_BREATHING;
				m_pFrameKey = L"Player_RUSH";
				m_tInfo.fCX = RANGE_RUSH_FCX;
				m_tInfo.fCY = RANGE_RUSH_FCY;
				CObj::Update_Rect();
				CObj::Update_Render_Rect();
				CObj::Update_Collide_Rect();
				m_fSlashTime = 0.f;

			}
			break;
		}
		}
		break;
	}

	case OBJ_STATUS::LAY_DOWN_START:
	{
		m_pFrameKey = L"Player_LAY_DOWN_START";
		m_tInfo.fCX = PLAYER_LAY_DOWN_START_FCX;
		m_tInfo.fCY = PLAYER_LAY_DOWN_START_FCY;
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		ZeroMemory(&m_tCollideRect, sizeof(RECT));
		
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eObjCurStatus == m_eObjPreStatus)
		{
			m_eObjCurStatus = OBJ_STATUS::LAY_DOWN_MIDDLE;
		}
		break;
	}
	case OBJ_STATUS::LAY_DOWN_MIDDLE:
	{
		m_pFrameKey = L"Player_LAY_DOWN_MIDDLE";
		m_tInfo.fCX = PLAYER_LAY_DOWN_MIDDLE_FCX;
		m_tInfo.fCY = PLAYER_LAY_DOWN_MIDDLE_FCY;
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		ZeroMemory(&m_tCollideRect, sizeof(RECT));
		
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eObjCurStatus == m_eObjPreStatus)
		{
			m_eObjCurStatus = OBJ_STATUS::LAY_DOWN;
		}
		break;
	}
	case OBJ_STATUS::LAY_DOWN:
	{
		m_pFrameKey = L"Player_LAY_DOWN";
		m_tInfo.fCX = PLAYER_LAY_DOWN_FCX;
		m_tInfo.fCY = PLAYER_LAY_DOWN_FCY;
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		ZeroMemory(&m_tCollideRect, sizeof(RECT));
		m_bPlayerLayDown = true;
		break;
	}
	case OBJ_STATUS::DOOR_KICK:
	{
		m_pFrameKey = L"Player_DOOR_KICK";
		m_tInfo.fCX = PLAYER_DOOR_KICK_FCX;
		m_tInfo.fCY = PLAYER_DOOR_KICK_FCY;
		CObj::Update_Rect();
		CObj::Update_Render_Rect();

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			m_eObjPreStatus = m_eObjCurStatus;
			m_eObjCurStatus = OBJ_STATUS::IDLE;
			m_pFrameKey = L"Player_IDLE";
			m_tInfo.fCX = PLAYER_IDLE_FCX;
			m_tInfo.fCY = PLAYER_IDLE_FCY;
			CObj::Update_Rect();
			CObj::Update_Render_Rect();
		}
		break;
	}
	case OBJ_STATUS::CROUCH:
	{
		if (CKeyMgr::Get_Instance()->m_bKeyStates['S'] == false)
		{
			m_eObjPreStatus = m_eObjCurStatus;
			m_eObjCurStatus = OBJ_STATUS::IDLE;
			m_pFrameKey = L"Player_IDLE";
			m_tInfo.fCX = PLAYER_IDLE_FCX;
			m_tInfo.fCY = PLAYER_IDLE_FCY;
			CObj::Update_Rect();
		}
		break;
	}
	case OBJ_STATUS::FLIP:
	{
		// 다 끝나지 않았을 때
		if ((m_tFrame.iFrameStart != m_tFrame.iFrameEnd))
		{
			float fFlipTheta = (70.0f * PI) / (180.0f);
			switch (m_eObjCurDir)
			{
			case OBJ_DIR::LEFT:
			{
				m_tInfo.fX -= (m_fFlipSpeed * std::cosf(fFlipTheta) * m_fJumpTime);
				m_tInfo.fY = m_tInfo.fY - (m_fFlipSpeed * std::sinf(fFlipTheta) * m_fJumpTime) + (0.5 * 9.8f * m_fJumpTime * m_fJumpTime);

				break;
			}
			case OBJ_DIR::RIGHT:
			{
				m_tInfo.fX += (m_fFlipSpeed * std::cosf(fFlipTheta) * m_fJumpTime);
				m_tInfo.fY = m_tInfo.fY - (m_fFlipSpeed * std::sinf(fFlipTheta) * m_fJumpTime) + (0.5 * 9.8f * m_fJumpTime * m_fJumpTime);

				break;
			}
			}
			m_fJumpTime += 0.1f;
		}
		else
		{
			m_eObjPreStatus = m_eObjCurStatus;
			m_eObjCurStatus = OBJ_STATUS::FALL;
			m_pFrameKey = L"Player_FALL";
			m_tInfo.fCX = PLAYER_FALL_FCX;
			m_tInfo.fCY = PLAYER_FALL_FCY;
			m_fJumpTime = 0.f;
		}
		break;
	}
	case OBJ_STATUS::THUNDER_BREATHING:
	{
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			m_eObjPreStatus = m_eObjCurStatus;
			m_eObjCurStatus = OBJ_STATUS::FALL;
			m_tInfo.fCX = PLAYER_FALL_FCX;
			m_tInfo.fCY = PLAYER_FALL_FCY;
			m_pFrameKey = L"Player_FALL";
			CObj::Update_Rect();
			CObj::Update_Render_Rect();
			CObj::Update_Collide_Rect();
		}
		break;
	}
	case OBJ_STATUS::WALL_GRAB:
	{
		m_pFrameKey = L"Player_WALL_GRAB";
		m_tInfo.fCX = PLAYER_WALL_GRAB_FCX;
		m_tInfo.fCY = PLAYER_WALL_GRAB_FCY;
		CObj::Update_Rect();
		break;
	}
	case OBJ_STATUS::JUMP:
	{
		m_tInfo.fY = m_tInfo.fY - (m_fPower * sin(m_fDegree * (PI / 180.0f)) * m_fJumpTime) + (0.5f * 9.8f * m_fJumpTime * m_fJumpTime);
		m_fJumpTime += 0.15f;

		if (m_fBeforeY < m_tInfo.fY)
		{
			m_eObjPreStatus = m_eObjCurStatus;
			m_eObjCurStatus = OBJ_STATUS::FALL;
			m_pFrameKey = L"Player_FALL";
			m_tInfo.fCX = PLAYER_FALL_FCX;
			m_tInfo.fCY = PLAYER_FALL_FCY;
			m_fJumpTime = 0.f;
			CObj::Update_Rect();
		}
		else
		{
			m_fBeforeY = m_tInfo.fY;
		}
		break;
	}
	case OBJ_STATUS::IDLE_TO_RUN:
	{
		if (m_tFrame.iFrameEnd == m_tFrame.iFrameStart)
		{
			m_eObjPreStatus = m_eObjCurStatus;
			m_eObjCurStatus = OBJ_STATUS::RUN;
			m_pFrameKey = L"Player_RUN";

			m_tInfo.fCX = PLAYER_RUN_FCX;
			m_tInfo.fCY = PLAYER_RUN_FCY;
			CObj::Update_Rect();
		}
		break;
	}
	case OBJ_STATUS::RUN_TO_IDLE:
	{
		if (m_tFrame.iFrameEnd == m_tFrame.iFrameStart)
		{
			m_eObjPreStatus = m_eObjCurStatus;
			m_eObjCurStatus = OBJ_STATUS::IDLE;
			m_pFrameKey = L"Player_IDLE";
			m_tInfo.fCX = PLAYER_IDLE_FCX;
			m_tInfo.fCY = PLAYER_IDLE_FCY;
			CObj::Update_Rect();
		}
		break;
	}
	case OBJ_STATUS::IDLE_TO_SNEAK:
	{
		if (m_tFrame.iFrameEnd == m_tFrame.iFrameStart)
		{
			m_eObjPreStatus = m_eObjCurStatus;
			m_eObjCurStatus = OBJ_STATUS::CROUCH;
			m_pFrameKey = L"Player_CROUCH";
			m_tInfo.fCX = PLAYER_CROUCH_FCX;
			m_tInfo.fCY = PLAYER_CROUCH_FCY;
			CObj::Update_Rect();
		}
		break;
	}
	case OBJ_STATUS::ROLL:
	{
		switch (m_eObjCurDir)
		{
		case OBJ_DIR::LEFT:
		{
			m_tInfo.fX -= m_fSpeed * 1.25f;
			break;
		}
		case OBJ_DIR::RIGHT:
		{
			m_tInfo.fX += m_fSpeed * 1.25f;
			break;
		}
		}
		

		if (m_tFrame.iFrameEnd == m_tFrame.iFrameStart)
		{
			m_eObjPreStatus = m_eObjCurStatus;
			m_eObjCurStatus = OBJ_STATUS::CROUCH;
			m_pFrameKey = L"Player_CROUCH";
			m_tInfo.fCX = PLAYER_CROUCH_FCX;
			m_tInfo.fCY = PLAYER_CROUCH_FCY;
			CObj::Update_Rect();
		}
		break;
	}
	case OBJ_STATUS::ATTACK:
	{
		if (m_tFrame.iFrameEnd == m_tFrame.iFrameStart)
		{
			m_eObjPreStatus = m_eObjCurStatus;
			// check the line and 
			m_eObjCurStatus = OBJ_STATUS::IDLE;
			m_pFrameKey = L"Player_IDLE";
			m_tInfo.fCX = PLAYER_IDLE_FCX;
			m_tInfo.fCY = PLAYER_IDLE_FCY;

			ZeroMemory(&m_tAttackAreaRect, sizeof(RECT));
			ZeroMemory(&m_tAttackAreaRenderRect, sizeof(RECT));

			CObj::Update_Rect();
			//CObj::Update_Attack_Rect();
			CObj::Update_Player_Attack_Rect();
		}
		break;
	}
	case OBJ_STATUS::RUN:
	{
		switch (m_eObjCurDir)
		{
		case OBJ_DIR::LEFT:
		{
			// 키를 누르지도 않았는데 RUN을 하는 경우 처리 (하드 코딩)
			if (CKeyMgr::Get_Instance()->m_bKeyStates['A'] == false)
			{
				m_eObjPreStatus = m_eObjCurStatus;
				m_eObjCurStatus = OBJ_STATUS::IDLE;
				m_pFrameKey = L"Player_IDLE";
				m_tInfo.fCX = PLAYER_IDLE_FCX;
				m_tInfo.fCY = PLAYER_IDLE_FCY;
			}
			break;
		}
		case OBJ_DIR::RIGHT:
		{
			// 키를 누르지도 않았는데 RUN을 하는 경우 처리 (하드 코딩)
			if (CKeyMgr::Get_Instance()->m_bKeyStates['D'] == false)
			{
				m_eObjPreStatus = m_eObjCurStatus;
				m_eObjCurStatus = OBJ_STATUS::IDLE;
				m_pFrameKey = L"Player_IDLE";
				m_tInfo.fCX = PLAYER_IDLE_FCX;
				m_tInfo.fCY = PLAYER_IDLE_FCY;
			}
			break;
		}
		}
	}
	}
}

void CPlayer::LButton_Key_Input()
{
	

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		POINT renderMousePos = CMouseMgr::Get_Instance()->Get_Mouse_Pos();
		//POINT renderMousePos = m_pPlayerMouse->Get_Mouse_Pos();
		Vec2 vCurrentMousePos = CCamera::Get_Instance()->GetRealPos(Vec2{ (float)renderMousePos.x, (float)renderMousePos.y });
		POINT tCurrentMousePos = { (LONG)vCurrentMousePos.fX, (LONG)vCurrentMousePos.fY };

		m_eObjPreStatus = m_eObjCurStatus;
		m_eObjCurStatus = OBJ_STATUS::ATTACK;
		m_pFrameKey = L"Player_Attack";
		
		// Mouse Click Direction Check
		float fWidth	= tCurrentMousePos.x - m_tInfo.fX;
		float fHeight	= tCurrentMousePos.y - m_tInfo.fY;
		float fDiagonal = sqrtf((fWidth * fWidth) + (fHeight * fHeight));
		
		float fNormalX = fWidth / fDiagonal;
		float fNormalY = fHeight / fDiagonal;

		

		if (fNormalX < 0)
		{
			m_eObjCurDir = OBJ_DIR::LEFT;
		}
		else
		{
			m_eObjCurDir = OBJ_DIR::RIGHT;
		}

		float fTheta = acosf(fNormalX / fDiagonal);
		if (fNormalY < 0)
		{
			fTheta = (2 * PI) - fTheta;
		}

		CObjMgr::Get_Instance()->Add_Object(
			OBJ_ID::OBJ_ID_EFFECT,
			CAbstractFactory<CEffect>::Create(
				m_tInfo.fX,
				m_tInfo.fY,
				PLAYER_NORMAL_ATTACK_EFFECT_FCX,
				PLAYER_NORMAL_ATTACK_EFFECT_FCY,
				fTheta,
				m_eObjCurDir,
				L"Effect_Dragon_Attack"
			)
		);


		CSoundMgr::Get_Instance()->StopSound(SWORD_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"sound_player_slash_3.wav", SWORD_EFFECT, 1.f);

		m_tInfo.fCX = PLAYER_ATTACK_FCX;
		m_tInfo.fCY = PLAYER_ATTACK_FCY;


		// Create Attack Area
		CObj::Update_Attack_Rect();
		CObj::Update_Rect();
	}
}

void CPlayer::LShift_Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LSHIFT))
	{
		CSoundMgr::Get_Instance()->StopSound(SLOW_MOTION_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"Slowmo_Enter.wav", SLOW_MOTION_EFFECT, 1.f);
	}
	if (CKeyMgr::Get_Instance()->Key_Up(VK_LSHIFT))
	{
		CSoundMgr::Get_Instance()->StopSound(SLOW_MOTION_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"Slowmo_Exit.wav", SLOW_MOTION_EFFECT, 1.f);
		CTimeSlowMgr::Get_Instance()->Normal_Time();
	}

	if (CKeyMgr::Get_Instance()->Key_Press(VK_LSHIFT))
	{
		CTimeSlowMgr::Get_Instance()->Slow_Time();
	}


}

void CPlayer::Q_Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Down('Q'))
	{
		ITEM_TYPE selectedItem = ITEM_TYPE::ITEM_TYPE_END;
		for (int i = 0; i < ITEM_TYPE::ITEM_TYPE_END; ++i)
		{
			if (m_bInventory[i])
			{
				selectedItem = (ITEM_TYPE)(i);
			}
		}

		switch (selectedItem)
		{
		case ITEM_TYPE::ITEM_EXPLOSIVE:
		{
			POINT mousePos = CMouseMgr::Get_Instance()->Get_Mouse_Pos();
			Vec2 realPos = CCamera::Get_Instance()->GetRealPos(Vec2{ (float)mousePos.x, (float)mousePos.y });
			
			float fWidth = realPos.fX - this->Get_Info().fX;
			float fHeight = realPos.fY - this->Get_Info().fY;
			float fDiagonal = sqrtf((fWidth * fWidth) + (fHeight * fHeight));

			Vec2 vNormalVec = { fWidth / fDiagonal, fHeight / fDiagonal };

			CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_EXPLOSIVE_THROW,
				CAbstractFactory<CExplosive>::Create(m_tInfo.fX, m_tInfo.fY, EXPLOSIVE_TYPE::EXPLOSIVE_THROW_TYPE, vNormalVec)
			);
			break;
		}
		default:
		{
			break;
		}
		}
		
	}
}

bool CPlayer::R_Key_Button_Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Down('R'))
	{
		CTimeRewindMgr::Get_Instance()->Set_RewindTime(true);
		CSoundMgr::Get_Instance()->StopSound(REWIND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"Rewind.wav", REWIND_EFFECT, 1.f);

	}
	return CTimeRewindMgr::Get_Instance()->Get_RewindTime();
}

void CPlayer::RButton_Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
	{
		CSoundMgr::Get_Instance()->StopSound(SLOW_MOTION_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"Slowmo_Enter.wav", SLOW_MOTION_EFFECT, 1.f);
	}

	if (CKeyMgr::Get_Instance()->Key_Press(VK_RBUTTON))
	{

		CTimeSlowMgr::Get_Instance()->Slow_Time();
		CMouseMgr::Get_Instance()->Set_Thunder_Breathing_Mode(true);
		CMouseMgr::Get_Instance()->Set_Target(this);
	}

	if (CKeyMgr::Get_Instance()->Key_Up(VK_RBUTTON))
	{
		CSoundMgr::Get_Instance()->StopSound(SLOW_MOTION_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"Slowmo_Exit.wav", SLOW_MOTION_EFFECT, 1.f);
		// 마우스 정보 가지고 오기
		POINT tTargetPos = CMouseMgr::Get_Instance()->Get_Mouse_Pos();
		Vec2 tTargetRealPos = CCamera::Get_Instance()->GetRealPos(Vec2{ (float)tTargetPos.x, (float)tTargetPos.y });
		Vec2 tPlayerRealPos = CCamera::Get_Instance()->GetRealPos(Vec2{ (float)m_tInfo.fX, (float)m_tInfo.fY });

		int x0 = m_tInfo.fX;
		int x1 = (int)tTargetRealPos.fX;
		int y0 = m_tInfo.fY;
		int y1 = (int)tTargetRealPos.fY;

		// radius가 500이하면 그냥 slash
		// radius가 500초과면 벽력일섬
		float fWidth = x1 - x0;
		float fHeight = y1 - y0;
		float fDiagonal = sqrtf((fWidth * fWidth) + (fHeight * fHeight));

		if (fWidth > 0)
		{
			m_eObjPreDir = m_eObjCurDir;
			m_eObjCurDir = OBJ_DIR::RIGHT;
			m_eSlashDir = OBJ_DIR::RIGHT;
		}
		else
		{
			m_eObjPreDir = m_eObjCurDir;
			m_eObjCurDir = OBJ_DIR::LEFT;
			m_eSlashDir = OBJ_DIR::LEFT;
		}

		if (fHeight > 0)
		{
			m_eSlashTopDown = OBJ_TOP_DOWN_STATUS::DOWN;
		}
		else
		{
			m_eSlashTopDown = OBJ_TOP_DOWN_STATUS::TOP;
		}

		if (fDiagonal > 450)
		{
			// 벽력일섬
			CThunderBreathingMgr::Get_Instance()->Set_Thunder_Breathing_Info(
				tTargetRealPos.fX,
				m_tInfo.fX,
				tTargetRealPos.fY,
				m_tInfo.fY,
				m_eObjCurDir,
				m_eSlashTopDown
			);

			CThunderBreathingMgr::Get_Instance()->Set_ThunderBreathing_Mode();

			CObj::Update_Rect();
			// (Manage_status 함수에서) 벽력 일섬이 모두 끝나면, Fall 상태로 바꾸기 <완료>
			CMouseMgr::Get_Instance()->Set_Thunder_Breathing_Mode(false);
			//CMouseMgr::Get_Instance()->Set_Target(nullptr);
			CTimeSlowMgr::Get_Instance()->Normal_Time();
		}
		else
		{
			m_eObjCurStatus = OBJ_STATUS::SLASH;
			m_fMyInitPosX = x0;
			m_fMyInitPosY = y0;
			m_fSlashTargetX = x1;
			m_fSlashTargetY = y1;

			// 그냥 Slash 기능 구현하기
			CObj::Update_Rect();
			CMouseMgr::Get_Instance()->Set_Thunder_Breathing_Mode(false);
			CTimeSlowMgr::Get_Instance()->Normal_Time();
		}
	}
}

void CPlayer::Item_Key_Input()
{
	if (m_bPlayerItemMode)
	{
		list<CObj*> pExplosiveList = CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_EXPLOSIVE);
		list<CObj*> pSmokeList = CObjMgr::Get_Instance()->Get_Object_List(OBJ_ID::OBJ_ID_SMOKE);
		// 화염병 줍기
		for (auto& explosive : pExplosiveList)
		{
			RECT explosiveRenderRect = explosive->Get_Render_Rect();
			POINT tMousePos = CMouseMgr::Get_Instance()->Get_Mouse_Pos();

			if (PtInRect(&explosiveRenderRect, tMousePos))
			{
				if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
				{
					ZeroMemory(&m_bInventory, sizeof(bool) * ITEM_TYPE::ITEM_TYPE_END);
					m_bInventory[ITEM_TYPE::ITEM_EXPLOSIVE] = true;
					explosive->Set_Dead(true);
					return;
				}
			}
		}
	}

}

void CPlayer::N_Key_Input()
{
	
}

void CPlayer::Thunder_Breathing_Manage_Status()
{
	switch (m_eObjCurStatus)
	{
	case OBJ_STATUS::THUNDER_BREATHING_PROCESS:
	{
		Vec2 renderPos = CCamera::Get_Instance()->GetRenderPos(Vec2{ m_tInfo.fX, m_tInfo.fY });

		switch (CThunderBreathingMgr::Get_Instance()->Get_Thunder_Breathing_Info().m_eThunderBreathingDir)
		{
		case OBJ_DIR::LEFT:
		{
			float fTargetX = CThunderBreathingMgr::Get_Instance()->Get_Thunder_Breathing_Info().m_fThunderBreathingX0;
			float fTargetY = CThunderBreathingMgr::Get_Instance()->Get_Thunder_Breathing_Info().m_fThunderBreathingY0;


			m_tInfo.fX -= 10.f;
			m_tInfo.fY = CThunderBreathingMgr::Get_Instance()->Get_Thunder_Breathing_Info().Get_Next_Y(m_tInfo.fX);

			bool bValidX = fTargetX >= m_tInfo.fX;
			bool bValidY = false;
			switch (CThunderBreathingMgr::Get_Instance()->Get_Thunder_Breathing_Info().m_eThunderBreathingTopDown)
			{
			case OBJ_TOP_DOWN_STATUS::TOP:
			{
				bValidY = m_tInfo.fY <= fTargetY;
				break;
			}
			case OBJ_TOP_DOWN_STATUS::DOWN:
			{
				bValidY = m_tInfo.fY >= fTargetY;
				break;
			}
			}

			if (bValidX)
			{
				m_tInfo.fX = fTargetX;
			}

			if (bValidY)
			{
				m_tInfo.fY = fTargetY;
			}

			if (m_tInfo.fX == fTargetX && m_tInfo.fY == fTargetY)
			{
				m_eObjCurStatus = OBJ_STATUS::THUNDER_BREATHING;
				m_pFrameKey = L"Player_RUSH";
				m_tInfo.fCX = RANGE_RUSH_FCX;
				m_tInfo.fCY = RANGE_RUSH_FCY;
				CObj::Update_Rect();
				CObj::Update_Render_Rect();
				CObj::Update_Collide_Rect();
				CThunderBreathingMgr::Get_Instance()->Set_ThunderBreathing_Mode_Off();

			}

			break;
		}
		case OBJ_DIR::RIGHT:
		{
			float fTargetX = CThunderBreathingMgr::Get_Instance()->Get_Thunder_Breathing_Info().m_fThunderBreathingX0;
			float fTargetY = CThunderBreathingMgr::Get_Instance()->Get_Thunder_Breathing_Info().m_fThunderBreathingY0;

			m_tInfo.fX += 10.f;
			m_tInfo.fY = CThunderBreathingMgr::Get_Instance()->Get_Thunder_Breathing_Info().Get_Next_Y(m_tInfo.fX);

			bool bValidX = fTargetX <= m_tInfo.fX;
			bool bValidY = false;
			switch (CThunderBreathingMgr::Get_Instance()->Get_Thunder_Breathing_Info().m_eThunderBreathingTopDown)
			{
			case OBJ_TOP_DOWN_STATUS::TOP:
			{
				bValidY = m_tInfo.fY <= fTargetY;
				break;
			}
			case OBJ_TOP_DOWN_STATUS::DOWN:
			{
				bValidY = m_tInfo.fY >= fTargetY;
				break;
			}
			}

			if (bValidX)
			{
				m_tInfo.fX = fTargetX;
			}

			if (bValidY)
			{
				m_tInfo.fY = fTargetY;
			}


			if (m_tInfo.fY >= fTargetY && m_tInfo.fX >= fTargetX)
			{
				m_eObjCurStatus = OBJ_STATUS::THUNDER_BREATHING;
				m_pFrameKey = L"Player_RUSH";
				m_tInfo.fCX = RANGE_RUSH_FCX;
				m_tInfo.fCY = RANGE_RUSH_FCY;
				CObj::Update_Rect();
				CObj::Update_Render_Rect();
				CObj::Update_Collide_Rect();
				CThunderBreathingMgr::Get_Instance()->Set_ThunderBreathing_Mode_Off();

			}
			break;
		}
		}

		break;
	}
	}
}

void CPlayer::Move_Run_Effect_Frame()
{
	if (m_eObjCurStatus == OBJ_STATUS::IDLE_TO_RUN)
	{
		m_tRunEffectFrame.iFrameStart = 0;
		m_bRunEffectActive = true;
	}

	if (m_bRunEffectActive)
	{
		if (m_tRunEffectFrame.dwTime + (m_tRunEffectFrame.dwSpeed * CTimeSlowMgr::Get_Instance()->Get_Ratio()) < GetTickCount())
		{
			++m_tRunEffectFrame.iFrameStart;
			m_tRunEffectFrame.dwTime = GetTickCount();
		}

		if (m_tRunEffectFrame.iFrameStart == m_tRunEffectFrame.iFrameEnd)
		{
			m_bRunEffectActive = false;
		}
	}

}




