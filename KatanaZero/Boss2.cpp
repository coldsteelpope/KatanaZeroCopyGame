#include "pch.h"
#include "Boss2.h"
#include "Camera.h"
#include "BmpMgr.h"
#include "LineMgr.h"
#include "ObjMgr.h"

#include "AbstractFactory.h"
#include "Lazer.h"
#include "BossBullet.h"
#include "Gernade.h"
#include "SceneMgr.h"
#include "BossStage02.h"
#include "SoundMgr.h"

#define TOP_LEFT_ONE_FX			280
#define TOP_LEFT_TWO_FX			400
#define TOP_RIGHT_ONE_FX		750
#define TOP_RIGHT_TWO_FX		600
#define BOTTOM_LINE_FY			418

CBoss2::CBoss2()
{

}

CBoss2::~CBoss2()
{
	Release();
}

void CBoss2::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/idle/IDLE_LEFT.bmp", L"Boss_IDLE_LEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/idle/IDLE_RIGHT.bmp", L"Boss_IDLE_RIGHT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/teleport/TELEPORT.bmp", L"Boss_TELEPORT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/teleport/TELEPORT_GROUND.bmp", L"Boss_TELEPORT_GROUND");


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/sweep/SWEEP.bmp", L"Boss_SWEEP");

	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/gernade/SHOOT_GUN.bmp", L"Boss_SHOOTGUN");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/gernade/TAKE_OUT_GUN.bmp", L"Boss_TAKE_OUT_GUN");


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/machineGun/BOSS_JUMP.bmp", L"Boss_JUMP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/machineGun/BOSS_JUMP_SHADOW.bmp", L"Boss_JUMP_SHADOW");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/machineGun/BOSS_WALL_GRAB.bmp", L"Boss_WALL_GRAB");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/machineGun/BOSS_WALL_JUMP.bmp", L"Boss_WALL_JUMP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/machineGun/BOSS_OUT_PATTERN.bmp", L"Boss_OUT_PATTERN");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/gernade/BOSS_IN_PATTERN.bmp", L"Boss_IN_PATTERN");
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/recover/RECOVER_LEFT.bmp", L"Boss_RECOVER_LEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/recover/RECOVER_RIGHT.bmp", L"Boss_RECOVER_RIGHT");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/die/DIE_GROUND.bmp", L"Boss_DIE_GROUND");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/die/DEAD_BODY.bmp", L"Boss_DEAD_BODY");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/die/NO_HEAD_BODY.bmp", L"Boss_NO_HEAD_BODY");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/die/ONLY_HEAD.bmp", L"Boss_ONLY_HEAD");

	
	


	//m_eObjCurDir = OBJ_DIR::LEFT;
	//m_eBossCurStatus = BOSS_STATUS::BOSS_IDLE_LEFT;
	//m_pFrameKey = L"Boss_IDLE_LEFT";
	//m_tInfo.fCX = BOSS_IDLE_FCX;
	//m_tInfo.fCY = BOSS_IDLE_FCY;


	m_eObjCurDir = OBJ_DIR::LEFT;
	m_eBossCurStatus = BOSS_STATUS::BOSS_IDLE_LEFT;
	m_pFrameKey = L"Boss_IDLE_LEFT";
	m_tInfo.fCX = BOSS_IDLE_FCX;
	m_tInfo.fCY = BOSS_IDLE_FCY;
	m_tInfo.fX = TOP_RIGHT_ONE_FX;
	m_tInfo.fY = BOTTOM_LINE_FY;
}

int CBoss2::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}
	CObj::Update_Rect();
	CObj::Update_Render_Rect();

	switch (m_eBossCurStatus)
	{
	case BOSS_STATUS::BOSS_LAY_DOWN_LEFT:
	{
		break;
	}
	case BOSS_STATUS::BOSS_LAY_DOWN_RIGHT:
	{
		break;
	}
	case BOSS_STATUS::BOSS_NO_HEAD_DEAD_BODY_LEFT:
	{
		break;
	}
	case BOSS_STATUS::BOSS_NO_HEAD_DEAD_BODY_RIGHT:
	{
		break;
	}
	case BOSS_STATUS::BOSS_DEAD_BODY_LEFT:
	{
		break;
	}
	case BOSS_STATUS::BOSS_DEAD_BODY_RIGHT:
	{
		break;
	}
	default:
	{
		CBoss2::Update_Collide_Rect_For_Boss2();
		break;
	}
	}

	return OBJ_NO_EVENT;
}

void CBoss2::Late_Update()
{
	if (m_bDeadScene)
	{
		CBoss2::Manage_Status();
		CBoss2::Motion_Change();
		CBoss2::All_Frame_Works();
	}
	else
	{
		if (m_bStart == true)
		{
			// 아직 캐릭터가 착지했을 때
			CBoss2::Manage_Status();
			if (
				m_eBossCurStatus != BOSS_STATUS::BOSS_RECOVER_LEFT && 
				m_eBossCurStatus != BOSS_STATUS::BOSS_RECOVER_RIGHT && 
				m_eBossCurStatus != BOSS_STATUS::BOSS_LAY_DOWN_LEFT && 
				m_eBossCurStatus != BOSS_STATUS::BOSS_LAY_DOWN_RIGHT &&
				m_eBossCurStatus != BOSS_STATUS::BOSS_DEAD_BODY_LEFT &&
				m_eBossCurStatus != BOSS_STATUS::BOSS_DEAD_BODY_RIGHT
			)
			{
				CBoss2::Manage_Pattern();
			}
		}
		CBoss2::Motion_Change();
		CBoss2::All_Frame_Works();
	}
}

void CBoss2::Render(HDC _hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	//Vec2 renderCollideRectLeftTop = CCamera::Get_Instance()->GetRenderPos(Vec2{ (float)m_tCollideRect.left, (float)m_tCollideRect.top });
	//Vec2 renderCollideRectRightBottom = CCamera::Get_Instance()->GetRenderPos(Vec2{ (float)m_tCollideRect.right, (float)m_tCollideRect.bottom });
	//::Rectangle(_hDC, renderCollideRectLeftTop.fX, renderCollideRectLeftTop.fY, renderCollideRectRightBottom.fX, renderCollideRectRightBottom.fY);


	switch (m_eBossCurStatus)
	{
	default:
	{
		GdiTransparentBlt(
			_hDC,
			m_tRenderRect.left,
			m_tRenderRect.top,
			(int)m_tInfo.fCX / 1.75f,
			(int)m_tInfo.fCY / 1.75f,
			hMemDC,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * m_tFrame.iMotion,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 0, 255)
		);
		break;
	}
	}

	
}

void CBoss2::Release()
{
	
}

void CBoss2::Motion_Change()
{
	if (m_eBossPreStatus != m_eBossCurStatus)
	{
		switch (m_eBossCurStatus)
		{
		case BOSS_STATUS::BOSS_DEAD_BODY_LEFT:
		{
			m_tFrame.iFrameStart = 18;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case BOSS_STATUS::BOSS_DEAD_BODY_RIGHT:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 18;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case BOSS_STATUS::BOSS_RECOVER_LEFT:
		{
			m_tFrame.iFrameStart = 11;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case BOSS_STATUS::BOSS_RECOVER_RIGHT:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case BOSS_STATUS::BOSS_IDLE_LEFT:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case BOSS_STATUS::BOSS_IDLE_RIGHT:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case BOSS_STATUS::BOSS_TELEPORT_APPEAR_TOP_LEFT:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 75;
			break;
		}
		case BOSS_STATUS::BOSS_TELEPORT_APPEAR_TOP_RIGHT:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 75;
			break;
		}
		case BOSS_STATUS::BOSS_TELEPORT_APPEAR_GROUND_LEFT:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 75;
			break;
		}
		case BOSS_STATUS::BOSS_TELEPORT_APPEAR_GROUND_RIGHT:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 75;
			break;
		}
		case BOSS_STATUS::BOSS_TELEPORT_DISAPPEAR_TOP_LEFT:
		{
			m_tFrame.iFrameStart = 4;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 75;
			break;
		}
		case BOSS_STATUS::BOSS_TELEPORT_DISAPPEAR_TOP_RIGHT:
		{
			m_tFrame.iFrameStart = 4;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 75;
			break;
		}
		case BOSS_STATUS::BOSS_TELEPORT_DISAPPEAR_GROUND_LEFT:
		{
			m_tFrame.iFrameStart = 4;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 75;
			break;
		}
		case BOSS_STATUS::BOSS_TELEPORT_DISAPPEAR_GROUND_RIGHT:
		{
			m_tFrame.iFrameStart = 4;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 75;
			break;
		}
		case BOSS_STATUS::BOSS_SHOOT_GUN_LEFT:
		{
			m_tFrame.iFrameStart = 7;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case BOSS_STATUS::BOSS_TAKE_OUT_GUN_LEFT:
		{
			m_tFrame.iFrameStart = 6;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case BOSS_STATUS::BOSS_SHOOT_GUN_RIGHT:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 70;
			break;
		}
		case BOSS_STATUS::BOSS_TAKE_OUT_GUN_RIGHT:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case BOSS_STATUS::BOSS_JUMP_LEFT:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case BOSS_STATUS::BOSS_JUMP_RIGHT:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case BOSS_STATUS::BOSS_GRAB_LEFT:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case BOSS_STATUS::BOSS_GRAB_RIGHT:
		{
			m_tFrame.iFrameStart = 2;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case BOSS_STATUS::BOSS_WALL_JUMP_LEFT:
		{
			m_tFrame.iFrameStart = 6;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 150;
			break;
		}
		case BOSS_STATUS::BOSS_WALL_JUMP_RIGHT:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 150;
			break;
		}
		case BOSS_STATUS::BOSS_OUT_PATTERN_LEFT:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 100;
			break;
		}
		case BOSS_STATUS::BOSS_OUT_PATTERN_RIGHT:
		{
			m_tFrame.iFrameStart = 3;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 100;
			break;
		}
		case BOSS_STATUS::BOSS_IN_PATTERN_LEFT:
		{
			m_tFrame.iFrameStart = 3;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case BOSS_STATUS::BOSS_IN_PATTERN_RIGHT:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case BOSS_STATUS::BOSS_LAY_DOWN_LEFT:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 500;
			break;
		}
		case BOSS_STATUS::BOSS_LAY_DOWN_RIGHT:
		{
			m_tFrame.iFrameStart = 7;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 500;
			break;
		}
		case BOSS_STATUS::BOSS_NO_HEAD_DEAD_BODY_LEFT:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case BOSS_STATUS::BOSS_NO_HEAD_DEAD_BODY_RIGHT:
		{
			m_tFrame.iFrameStart = 5;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			
			break;
		}
		}
		m_eBossPreStatus = m_eBossCurStatus;
	}
}

void CBoss2::Manage_Status()
{
	switch (m_eBossCurStatus)
	{
	case BOSS_STATUS::BOSS_NO_HEAD_DEAD_BODY_LEFT:
	{
		m_tInfo.fCX = BOSS_DEAD_BODY_NO_HEAD_FCX;
		m_tInfo.fCY = BOSS_DEAD_BODY_NO_HEAD_FCY;
		m_pFrameKey = L"Boss_NO_HEAD_BODY";
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		ZeroMemory(&m_tCollideRect, sizeof(RECT));

		
		break;
	}
	case BOSS_STATUS::BOSS_NO_HEAD_DEAD_BODY_RIGHT:
	{
		m_tInfo.fCX = BOSS_DEAD_BODY_NO_HEAD_FCX;
		m_tInfo.fCY = BOSS_DEAD_BODY_NO_HEAD_FCY;
		m_pFrameKey = L"Boss_NO_HEAD_BODY";
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		ZeroMemory(&m_tCollideRect, sizeof(RECT));


		break;
	}
	case BOSS_STATUS::BOSS_DEAD_BODY_LEFT:
	{
		m_tInfo.fCX = BOSS_DEAD_BODY_FCX;
		m_tInfo.fCY = BOSS_DEAD_BODY_FCY;
		m_pFrameKey = L"Boss_DEAD_BODY";
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss2::Update_Collide_Rect_For_Boss2();
		m_tInfo.fX -= 1.f;
		break;
	}
	case BOSS_STATUS::BOSS_DEAD_BODY_RIGHT:
	{
		m_tInfo.fCX = BOSS_DEAD_BODY_FCX;
		m_tInfo.fCY = BOSS_DEAD_BODY_FCY;
		m_pFrameKey = L"Boss_DEAD_BODY";
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss2::Update_Collide_Rect_For_Boss2();
		m_tInfo.fX += 1.f;

		break;
	}
	case BOSS_STATUS::BOSS_LAY_DOWN_LEFT:
	{
		m_tInfo.fCX = BOSS_LAY_DOWN_FCX;
		m_tInfo.fCY = BOSS_LAY_DOWN_FCY;
		m_pFrameKey = L"Boss_DIE_GROUND";
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		ZeroMemory(&m_tCollideRect, sizeof(RECT));
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossCurStatus == m_eBossPreStatus)
		{
			float fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
			if (fWidth)
			{
				m_eObjCurDir = OBJ_DIR::RIGHT;
			}
			else
			{
				m_eObjCurDir = OBJ_DIR::LEFT;
			}
			m_eBossCurStatus = BOSS_STATUS::BOSS_DEAD_BODY_LEFT;
			m_pFrameKey = L"Boss_DEAD_BODY";
			m_tInfo.fCX = BOSS_DEAD_BODY_FCX;
			m_tInfo.fCY = BOSS_DEAD_BODY_FCY;
			CObj::Update_Rect();
			CObj::Update_Render_Rect();
			CBoss2::Update_Collide_Rect_For_Boss2();
			m_bDeadScene = true;
		}
		break;
	}
	case BOSS_STATUS::BOSS_LAY_DOWN_RIGHT:
	{
		m_tInfo.fCX = BOSS_LAY_DOWN_FCX;
		m_tInfo.fCY = BOSS_LAY_DOWN_FCY;
		m_pFrameKey = L"Boss_DIE_GROUND";
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		ZeroMemory(&m_tCollideRect, sizeof(RECT));
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossCurStatus == m_eBossPreStatus)
		{
			float fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
			if (fWidth)
			{
				m_eObjCurDir = OBJ_DIR::RIGHT;
			}
			else
			{
				m_eObjCurDir = OBJ_DIR::LEFT;
			}

			m_eBossCurStatus = BOSS_STATUS::BOSS_DEAD_BODY_RIGHT;
			m_pFrameKey = L"Boss_DEAD_BODY";
			m_tInfo.fCX = BOSS_DEAD_BODY_FCX;
			m_tInfo.fCY = BOSS_DEAD_BODY_FCY;
			CObj::Update_Rect();
			CObj::Update_Render_Rect();
			CBoss2::Update_Collide_Rect_For_Boss2();
			m_bDeadScene = true;
		}
		break;
	}
	case BOSS_STATUS::BOSS_RECOVER_LEFT:
	{
		m_tInfo.fY = BOTTOM_LINE_FY;
		m_tInfo.fCX = BOSS_RECOVER_FCX;
		m_tInfo.fCY = BOSS_RECOVER_FCY;
		m_pFrameKey = L"Boss_RECOVER_LEFT";
		CObj::Update_Rect();
		CObj::Update_Render_Rect();

		ZeroMemory(&m_tCollideRect, sizeof(RECT));

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossCurStatus == m_eBossPreStatus)
		{
			m_eObjCurDir = OBJ_DIR::LEFT;
			m_eCurrentPattern = BOSS_2_STAGE_PATTERN::BOSS_IDLE_PATTERN;
			m_eBossPatternOneDetail = BOSS_PATTERN_1_END;
			m_eBossPatternTwoDetail = BOSS_PATTERN_2_END;
			m_eBossPatternThreeDetail = BOSS_PATTERN_3_DETAIL_END;

			CObj* pPlayer = m_pTarget;
			if (pPlayer->Get_Info().fX >= 530.f)
			{
				m_eObjCurDir = OBJ_DIR::RIGHT;
				m_eBossCurStatus = BOSS_STATUS::BOSS_IN_PATTERN_RIGHT;
			}
			else if (pPlayer->Get_Info().fX < 530.f)
			{
				m_eObjCurDir = OBJ_DIR::LEFT;
				m_eBossCurStatus = BOSS_STATUS::BOSS_IN_PATTERN_LEFT;
			}
			CBoss2::Motion_Change();

			//int iPatternRandom = (int)(rand() % 3);
			int iPatternRandom = 2;

			switch (iPatternRandom)
			{
			case 0:
			{
				m_eCurrentPattern = BOSS_PATTERN_1;
				break;
			}
			case 1:
			{
				m_eCurrentPattern = BOSS_PATTERN_2;
				break;
			}
			case 2:
			{
				m_eCurrentPattern = BOSS_PATTERN_3;
				break;
			}
			}

		}

		break;
	}
	case BOSS_STATUS::BOSS_RECOVER_RIGHT:
	{
		m_tInfo.fY = BOTTOM_LINE_FY;
		m_tInfo.fCX = BOSS_RECOVER_FCX;
		m_tInfo.fCY = BOSS_RECOVER_FCY;
		m_pFrameKey = L"Boss_RECOVER_RIGHT";
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		ZeroMemory(&m_tCollideRect, sizeof(RECT));

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossCurStatus == m_eBossPreStatus)
		{
			m_eObjCurDir = OBJ_DIR::RIGHT;
			m_eCurrentPattern = BOSS_2_STAGE_PATTERN::BOSS_IDLE_PATTERN;
			m_eBossPatternOneDetail = BOSS_PATTERN_1_END;
			m_eBossPatternTwoDetail = BOSS_PATTERN_2_END;
			m_eBossPatternThreeDetail = BOSS_PATTERN_3_DETAIL_END;

			CObj* pPlayer = m_pTarget;
			if (pPlayer->Get_Info().fX >= 530.f)
			{
				m_eObjCurDir = OBJ_DIR::RIGHT;
				m_eBossCurStatus = BOSS_STATUS::BOSS_IN_PATTERN_RIGHT;

			}
			else if (pPlayer->Get_Info().fX < 530.f)
			{
				m_eObjCurDir = OBJ_DIR::LEFT;
				m_eBossCurStatus = BOSS_STATUS::BOSS_IN_PATTERN_LEFT;
			}
			CBoss2::Motion_Change();

			int iPatternRandom = (int)(rand() % 3);

			switch (iPatternRandom)
			{
			case 0:
			{	
				m_eCurrentPattern = BOSS_PATTERN_1;
				break;
			}
			case 1:
			{
				m_eCurrentPattern = BOSS_PATTERN_2;
				break;
			}
			case 2:
			{
				m_eCurrentPattern = BOSS_PATTERN_3;
				break;
			}
			}
		}
		break;
	}
	}
}

void CBoss2::Update_Collide_Rect_For_Boss2()
{
	// collideInfo 기반으로 선타기를 진행하자
	m_tCollideInfo.fX = m_tInfo.fX - 10;
	m_tCollideInfo.fY = m_tInfo.fY - 10;
	
	m_tCollideInfo.fCX = BOSS_IDLE_FCX * 0.75;
	m_tCollideInfo.fCY = BOSS_IDLE_FCY * 0.75;

	m_tCollideRect.left = (long)(m_tCollideInfo.fX - m_tCollideInfo.fCX / 2.0f);
	m_tCollideRect.top = (long)(m_tCollideInfo.fY - m_tCollideInfo.fCY / 2.0f);
	m_tCollideRect.right = (long)(m_tCollideInfo.fX + m_tCollideInfo.fCX / 2.0f);
	m_tCollideRect.bottom = (long)(m_tCollideInfo.fY + m_tCollideInfo.fCX / 2.0f);
}



void CBoss2::Manage_Pattern()
{
	switch (m_eCurrentPattern)
	{
	case BOSS_2_STAGE_PATTERN::BOSS_IDLE_PATTERN:
	{
		CObj* pPlayer = m_pTarget;
		if (pPlayer->Get_Info().fX >= 530.f)
		{
			m_eObjCurDir = OBJ_DIR::RIGHT;
			m_eBossCurStatus = BOSS_STATUS::BOSS_IN_PATTERN_RIGHT;
		}
		else if (pPlayer->Get_Info().fX < 530.f)
		{
			m_eObjCurDir = OBJ_DIR::LEFT;
			m_eBossCurStatus = BOSS_STATUS::BOSS_IN_PATTERN_LEFT;
		}

		int iPatternRandom = (int)(rand() % 3);

		switch (iPatternRandom)
		{
		case 0:
		{
			m_eCurrentPattern = BOSS_PATTERN_1;
			break;
		}
		case 1:
		{
			m_eCurrentPattern = BOSS_PATTERN_2;
			break;
		}
		case 2:
		{
			m_eCurrentPattern = BOSS_PATTERN_3;
			break;
		}
		}
		break;
	}
	case BOSS_2_STAGE_PATTERN::BOSS_PATTERN_1:
	{
		Pattern_One();
		break;
	}
	case BOSS_2_STAGE_PATTERN::BOSS_PATTERN_2:
	{
		Pattern_Two();
		break;
	}
	case BOSS_2_STAGE_PATTERN::BOSS_PATTERN_3:
	{
		Pattern_Three();
		break;
	}
	}

}



void CBoss2::Jump()
{
	
	float fY(0.f); // not foot just y 좌표

}

void CBoss2::Pattern_One()
{
	switch (m_eBossPatternOneDetail)
	{
	case BOSS_PATTERN_1_END:
	{
		m_eBossPatternOneDetail = BOSS_PATTERN_1_DETAIL::TOP_LEFT_1_START;
		break;
	}
	case TOP_LEFT_1_START:
	{
		m_tInfo.fX = TOP_LEFT_ONE_FX;
		m_tInfo.fY = 100;
		m_eBossCurStatus = BOSS_STATUS::BOSS_TELEPORT_APPEAR_TOP_LEFT;
		m_pFrameKey = L"Boss_TELEPORT";
		m_tInfo.fCX = BOSS_TELEPORT_FCX;
		m_tInfo.fCY = BOSS_TELEPORT_FCY;


		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss2::Update_Collide_Rect_For_Boss2();
		
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossPreStatus == m_eBossCurStatus)
		{
			CSoundMgr::Get_Instance()->StopSound(BOSS_ATTACK_SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"LazerTop.wav", BOSS_ATTACK_SOUND_EFFECT, 1.f);


			// 레이저 생성하기
			CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_LAZER, CAbstractFactory<CLazer>::Create(m_tInfo.fX - 15, m_tInfo.fY + LAZER_WIDTH / 2, LAZER_TYPE::VERTICAL));

			m_eBossPatternOneDetail = BOSS_PATTERN_1_DETAIL::TOP_LEFT_1_END;
		}
		break;
	}
	case TOP_LEFT_1_END:
	{
		m_tInfo.fX = TOP_LEFT_ONE_FX;
		m_tInfo.fY = 100;
		m_eBossCurStatus = BOSS_STATUS::BOSS_TELEPORT_DISAPPEAR_TOP_LEFT;
		m_pFrameKey = L"Boss_TELEPORT";
		m_tInfo.fCX = BOSS_TELEPORT_FCX;
		m_tInfo.fCY = BOSS_TELEPORT_FCY;
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss2::Update_Collide_Rect_For_Boss2();
		
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossPreStatus == m_eBossCurStatus)
		{
			m_eBossPatternOneDetail = BOSS_PATTERN_1_DETAIL::TOP_RIGHT_1_START;
		}
		break;
	}
	case TOP_RIGHT_1_START:
	{
		m_tInfo.fX = TOP_RIGHT_ONE_FX;
		m_tInfo.fY = 100;

		m_eBossCurStatus = BOSS_STATUS::BOSS_TELEPORT_APPEAR_TOP_RIGHT;
		m_pFrameKey = L"Boss_TELEPORT";
		m_tInfo.fCX = BOSS_TELEPORT_FCX;
		m_tInfo.fCY = BOSS_TELEPORT_FCY;
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss2::Update_Collide_Rect_For_Boss2();

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossPreStatus == m_eBossCurStatus)
		{
			CSoundMgr::Get_Instance()->StopSound(BOSS_ATTACK_SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"LazerTop.wav", BOSS_ATTACK_SOUND_EFFECT, 1.f);

			CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_LAZER, CAbstractFactory<CLazer>::Create(m_tInfo.fX - 7, m_tInfo.fY + LAZER_WIDTH / 2, LAZER_TYPE::VERTICAL));
			m_eBossPatternOneDetail = BOSS_PATTERN_1_DETAIL::TOP_RIGHT_1_END;
		}
		break;
	}
	case TOP_RIGHT_1_END:
	{
		m_tInfo.fX = TOP_RIGHT_ONE_FX;
		m_tInfo.fY = 100;
	
		m_eBossCurStatus = BOSS_STATUS::BOSS_TELEPORT_DISAPPEAR_TOP_RIGHT;
		m_pFrameKey = L"Boss_TELEPORT";
		m_tInfo.fCX = BOSS_TELEPORT_FCX;
		m_tInfo.fCY = BOSS_TELEPORT_FCY;
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss2::Update_Collide_Rect_For_Boss2();

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossPreStatus == m_eBossCurStatus)
		{
			m_eBossPatternOneDetail = BOSS_PATTERN_1_DETAIL::TOP_LEFT_2_START;
		}
		break;
	}
	case TOP_LEFT_2_START:
	{
		m_tInfo.fX = TOP_LEFT_TWO_FX; 
		m_tInfo.fY = 100;

		m_eBossCurStatus = BOSS_STATUS::BOSS_TELEPORT_APPEAR_TOP_LEFT;
		m_pFrameKey = L"Boss_TELEPORT";
		m_tInfo.fCX = BOSS_TELEPORT_FCX;
		m_tInfo.fCY = BOSS_TELEPORT_FCY;
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss2::Update_Collide_Rect_For_Boss2();

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossPreStatus == m_eBossCurStatus)
		{
			CSoundMgr::Get_Instance()->StopSound(BOSS_ATTACK_SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"LazerTop..wav", BOSS_ATTACK_SOUND_EFFECT, 1.f);

			CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_LAZER, CAbstractFactory<CLazer>::Create(m_tInfo.fX - 15, m_tInfo.fY + LAZER_WIDTH / 2, LAZER_TYPE::VERTICAL));
			m_eBossPatternOneDetail = BOSS_PATTERN_1_DETAIL::TOP_LEFT_2_END;
		}
		break;
	}
	case TOP_LEFT_2_END:
	{
		m_tInfo.fX = TOP_LEFT_TWO_FX;
		m_tInfo.fY = 100;

		m_eBossCurStatus = BOSS_STATUS::BOSS_TELEPORT_DISAPPEAR_TOP_LEFT;
		m_pFrameKey = L"Boss_TELEPORT";
		m_tInfo.fCX = BOSS_TELEPORT_FCX;
		m_tInfo.fCY = BOSS_TELEPORT_FCY;
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss2::Update_Collide_Rect_For_Boss2();

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossPreStatus == m_eBossCurStatus)
		{
			m_eBossPatternOneDetail = BOSS_PATTERN_1_DETAIL::TOP_RIGHT_2_START;
		}
		break;
	}
	case TOP_RIGHT_2_START:
	{
		m_tInfo.fX = TOP_RIGHT_TWO_FX;
		m_tInfo.fY = 100;

		m_eBossCurStatus = BOSS_STATUS::BOSS_TELEPORT_APPEAR_TOP_RIGHT;
		m_pFrameKey = L"Boss_TELEPORT";
		m_tInfo.fCX = BOSS_TELEPORT_FCX;
		m_tInfo.fCY = BOSS_TELEPORT_FCY;
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss2::Update_Collide_Rect_For_Boss2();

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossPreStatus == m_eBossCurStatus)
		{
			CSoundMgr::Get_Instance()->StopSound(BOSS_ATTACK_SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"LazerTop.wav", BOSS_ATTACK_SOUND_EFFECT, 1.f);

			CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_LAZER, CAbstractFactory<CLazer>::Create(m_tInfo.fX - 7, m_tInfo.fY + LAZER_WIDTH / 2, LAZER_TYPE::VERTICAL));
			m_eBossPatternOneDetail = BOSS_PATTERN_1_DETAIL::TOP_RIGHT_2_END;
		}
		break;
	}
	case TOP_RIGHT_2_END:
	{
		m_tInfo.fX = TOP_RIGHT_TWO_FX;
		m_tInfo.fY = 100;

		m_eBossCurStatus = BOSS_STATUS::BOSS_TELEPORT_DISAPPEAR_TOP_RIGHT;
		m_pFrameKey = L"Boss_TELEPORT";
		m_tInfo.fCX = BOSS_TELEPORT_FCX;
		m_tInfo.fCY = BOSS_TELEPORT_FCY;
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss2::Update_Collide_Rect_For_Boss2();

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossPreStatus == m_eBossCurStatus)
		{
			// 여기서 스윕을 할건지 그라운드에서 쏠건지 결정
			int iPattern = rand() % 2;
			switch (iPattern)
			{
			case 0:
			{
				m_eBossPatternOneDetail = BOSS_PATTERN_1_DETAIL::GROUND_RIGHT_SHOT_START;
				break;
			}
			case 1:
			{
				m_eBossPatternOneDetail = BOSS_PATTERN_1_DETAIL::GROUND_LEFT_SHOT_START;
				break;
			}
			}
		}
		break;
	}
	// 그라운드 left, right
	case GROUND_LEFT_SHOT_START:
	{
		m_eObjCurDir = OBJ_DIR::LEFT;
		m_tInfo.fX = TOP_LEFT_ONE_FX;
		m_tInfo.fY = 410;

		m_eBossCurStatus = BOSS_STATUS::BOSS_TELEPORT_APPEAR_GROUND_LEFT;
		m_pFrameKey = L"Boss_TELEPORT_GROUND";
		m_tInfo.fCX = BOSS_TELEPORT_GROUND_FCX;
		m_tInfo.fCY = BOSS_TELEPORT_GROUND_FCY;
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss2::Update_Collide_Rect_For_Boss2();

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossPreStatus == m_eBossCurStatus)
		{
			CSoundMgr::Get_Instance()->StopSound(BOSS_ATTACK_SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"LazerTop.wav", BOSS_ATTACK_SOUND_EFFECT, 1.f);


			CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_LAZER, CAbstractFactory<CLazer>::Create(m_tCollideInfo.fX + m_tCollideInfo.fCX / 2.0f + LAZER_WIDTH / 2.0f, m_tInfo.fY - m_tCollideInfo.fCY / 2.0f + 10, LAZER_TYPE::HORIZONTAL));
			m_eBossPatternOneDetail = BOSS_PATTERN_1_DETAIL::GROUND_LEFT_SHOT_END;

		}

		break;
	}
	case GROUND_LEFT_SHOT_END:
	{
		m_tInfo.fX = TOP_LEFT_ONE_FX;
		m_tInfo.fY = 410;

		m_eBossCurStatus = BOSS_STATUS::BOSS_TELEPORT_DISAPPEAR_GROUND_LEFT;
		m_pFrameKey = L"Boss_TELEPORT_GROUND";
		m_tInfo.fCX = BOSS_TELEPORT_GROUND_FCX;
		m_tInfo.fCY = BOSS_TELEPORT_GROUND_FCY;
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss2::Update_Collide_Rect_For_Boss2();

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossPreStatus == m_eBossCurStatus)
		{
			m_eBossPatternOneDetail = BOSS_PATTERN_1_DETAIL::BOSS_PATTERN_1_END;
			m_eCurrentPattern = BOSS_2_STAGE_PATTERN::BOSS_IDLE_PATTERN;
		}
		break;
	}
	case GROUND_RIGHT_SHOT_START:
	{
		m_eObjCurDir = OBJ_DIR::RIGHT;
		m_tInfo.fX = TOP_RIGHT_ONE_FX;
		m_tInfo.fY = 410;

		m_eBossCurStatus = BOSS_STATUS::BOSS_TELEPORT_APPEAR_GROUND_RIGHT;
		m_pFrameKey = L"Boss_TELEPORT_GROUND";
		m_tInfo.fCX = BOSS_TELEPORT_GROUND_FCX;
		m_tInfo.fCY = BOSS_TELEPORT_GROUND_FCY;
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss2::Update_Collide_Rect_For_Boss2();

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossPreStatus == m_eBossCurStatus)
		{
			CSoundMgr::Get_Instance()->StopSound(BOSS_ATTACK_SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"LazerTop.wav", BOSS_ATTACK_SOUND_EFFECT, 1.f);

			CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_LAZER, CAbstractFactory<CLazer>::Create(m_tCollideInfo.fX - m_tCollideInfo.fCX / 2.0f - LAZER_WIDTH / 2.0f, m_tInfo.fY - m_tCollideInfo.fCY / 2.0f + 10, LAZER_TYPE::HORIZONTAL));
			m_eBossPatternOneDetail = BOSS_PATTERN_1_DETAIL::GROUND_RIGHT_SHOT_END;
		}
		break;
	}
	case GROUND_RIGHT_SHOT_END:
	{
		m_tInfo.fX = TOP_RIGHT_ONE_FX;
		m_tInfo.fY = 410;

		m_eBossCurStatus = BOSS_STATUS::BOSS_TELEPORT_DISAPPEAR_GROUND_RIGHT;
		m_pFrameKey = L"Boss_TELEPORT_GROUND";
		m_tInfo.fCX = BOSS_TELEPORT_GROUND_FCX;
		m_tInfo.fCY = BOSS_TELEPORT_GROUND_FCY;
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss2::Update_Collide_Rect_For_Boss2();

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossPreStatus == m_eBossCurStatus)
		{
			m_eBossPatternOneDetail = BOSS_PATTERN_1_DETAIL::BOSS_PATTERN_1_END;
			m_eCurrentPattern = BOSS_2_STAGE_PATTERN::BOSS_IDLE_PATTERN;
		}
		break;
	}
	// sweep left, right
	}
}



void CBoss2::Pattern_Two()
{
	switch (m_eBossPatternTwoDetail)
	{
	case BOSS_PATTERN_2_DETAIL::BOSS_PATTERN_2_IN:
	{
		switch (m_eObjCurDir)
		{
		case OBJ_DIR::LEFT:
		{
			m_eObjCurDir = OBJ_DIR::LEFT;
			m_tInfo.fX = TOP_RIGHT_ONE_FX;
			m_tInfo.fY = 410;
			m_eBossCurStatus = BOSS_STATUS::BOSS_IN_PATTERN_LEFT;
			m_pFrameKey = L"Boss_IN_PATTERN";
			m_tInfo.fCX = BOSS_IN_PATTERN_FCX;
			m_tInfo.fCY = BOSS_IN_PATTERN_FCY;

			if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossCurStatus == m_eBossPreStatus)
			{
				CSoundMgr::Get_Instance()->StopSound(BOSS_ATTACK_SOUND_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"boss_gun.wav", BOSS_ATTACK_SOUND_EFFECT, 1.f);

				m_eBossPatternTwoDetail = BOSS_PATTERN_2_DETAIL::TAKE_OUT_GUN_LEFT;
			}
			break;
		}
		case OBJ_DIR::RIGHT:
		{
			m_eObjCurDir = OBJ_DIR::RIGHT;

			m_tInfo.fX = TOP_LEFT_ONE_FX;
			m_tInfo.fY = 410;
			m_eBossCurStatus = BOSS_STATUS::BOSS_IN_PATTERN_RIGHT;
			m_pFrameKey = L"Boss_IN_PATTERN";
			m_tInfo.fCX = BOSS_IN_PATTERN_FCX;
			m_tInfo.fCY = BOSS_IN_PATTERN_FCY;

			if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossCurStatus == m_eBossPreStatus)
			{
				CSoundMgr::Get_Instance()->StopSound(BOSS_ATTACK_SOUND_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"boss_gun.wav", BOSS_ATTACK_SOUND_EFFECT, 1.f);


				m_eBossPatternTwoDetail = BOSS_PATTERN_2_DETAIL::TAKE_OUT_GUN_RIGHT;
				
			}
			break;
		}
		}
		break;
	}
	case BOSS_PATTERN_2_DETAIL::TAKE_OUT_GUN_LEFT:
	{
		m_tInfo.fX = TOP_RIGHT_ONE_FX;
		m_tInfo.fY = 410;
		m_eBossCurStatus = BOSS_STATUS::BOSS_TAKE_OUT_GUN_LEFT;
		m_pFrameKey = L"Boss_TAKE_OUT_GUN";
		m_tInfo.fCX = TAKE_OUT_GUN_FCX;
		m_tInfo.fCY = TAKE_OUT_GUN_FCY;

		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss2::Update_Collide_Rect_For_Boss2();

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossPreStatus == m_eBossCurStatus)
		{

			m_eBossPatternTwoDetail = BOSS_PATTERN_2_DETAIL::SHOOT_GUN_LEFT;

		}
		break;
	}
	case BOSS_PATTERN_2_DETAIL::SHOOT_GUN_LEFT:
	{
		m_tInfo.fX = TOP_RIGHT_ONE_FX;
		m_tInfo.fY = 410;
		m_eBossCurStatus = BOSS_STATUS::BOSS_SHOOT_GUN_LEFT;
		m_pFrameKey = L"Boss_SHOOTGUN";
		m_tInfo.fCX = SHOOT_GUN_FCX;
		m_tInfo.fCY = SHOOT_GUN_FCY;
		
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss2::Update_Collide_Rect_For_Boss2();


		if (m_tFrame.iFrameStart == 5 && m_iBeforeFrame != m_tFrame.iFrameStart)
		{

			CObjMgr::Get_Instance()->Add_Object(OBJ_ID_GERNADE, CAbstractFactory<CGernade>::Create(m_tCollideInfo.fX, m_tCollideInfo.fY, OBJ_DIR::LEFT));
			CSoundMgr::Get_Instance()->StopSound(BOSS_ATTACK_SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"boss_gun_shot.wav", BOSS_ATTACK_SOUND_EFFECT, 1.f);

			++m_iFireNumber;
		}

		if (m_iFireNumber > 2)
		{

			m_eBossPatternTwoDetail = BOSS_PATTERN_2_DETAIL::BOSS_PATTERN_2_OUT_OF_PATTERN;
			m_iFireNumber = 0;
			return;
		}
		m_iBeforeFrame = m_tFrame.iFrameStart;
		
		break;
	}
	case BOSS_PATTERN_2_DETAIL::TAKE_OUT_GUN_RIGHT:
	{
		m_tInfo.fX = TOP_LEFT_ONE_FX;
		m_tInfo.fY = 410;
		m_eBossCurStatus = BOSS_STATUS::BOSS_TAKE_OUT_GUN_RIGHT;
		m_pFrameKey = L"Boss_TAKE_OUT_GUN";
		m_tInfo.fCX = TAKE_OUT_GUN_FCX;
		m_tInfo.fCY = TAKE_OUT_GUN_FCY;

		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss2::Update_Collide_Rect_For_Boss2();
		
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossPreStatus == m_eBossCurStatus)
		{

			m_eBossPatternTwoDetail = BOSS_PATTERN_2_DETAIL::SHOOT_GUN_RIGHT;
		}
		break;
	}
	case BOSS_PATTERN_2_DETAIL::SHOOT_GUN_RIGHT:
	{
		m_tInfo.fX = TOP_LEFT_ONE_FX + 30;
		m_tInfo.fY = 410;
		m_eBossCurStatus = BOSS_STATUS::BOSS_SHOOT_GUN_RIGHT;
		m_pFrameKey = L"Boss_SHOOTGUN";
		m_tInfo.fCX = SHOOT_GUN_FCX;
		m_tInfo.fCY = SHOOT_GUN_FCY;

		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss2::Update_Collide_Rect_For_Boss2();

		if (m_tFrame.iFrameStart == 5 && m_iBeforeFrame != m_tFrame.iFrameStart)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_ID_GERNADE, CAbstractFactory<CGernade>::Create(m_tCollideInfo.fX, m_tCollideInfo.fY, OBJ_DIR::RIGHT));
			++m_iFireNumber;

			CSoundMgr::Get_Instance()->StopSound(BOSS_ATTACK_SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"boss_gun_shot.wav", BOSS_ATTACK_SOUND_EFFECT, 1.f);

		}

		if (m_iFireNumber > 2)
		{

			m_eBossPatternTwoDetail = BOSS_PATTERN_2_DETAIL::BOSS_PATTERN_2_OUT_OF_PATTERN;
			m_iFireNumber = 0;
			return;
		}
		m_iBeforeFrame = m_tFrame.iFrameStart;
		break;
	}

	case BOSS_PATTERN_2_DETAIL::BOSS_PATTERN_2_OUT_OF_PATTERN:
	{
		switch (m_eObjCurDir)
		{
		case OBJ_DIR::LEFT:
		{
			m_eBossCurStatus = BOSS_STATUS::BOSS_OUT_PATTERN_RIGHT;
			break;
		}
		case OBJ_DIR::RIGHT:
		{
			m_tInfo.fX = TOP_LEFT_ONE_FX;
			m_eBossCurStatus = BOSS_STATUS::BOSS_OUT_PATTERN_LEFT;
			break;
		}
		}
		m_tInfo.fCX = BOSS_OUT_PATTERN_FCX;
		m_tInfo.fCY = BOSS_OUT_PATTERN_FCY;
		m_pFrameKey = L"Boss_OUT_PATTERN";
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss2::Update_Collide_Rect_For_Boss2();

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossCurStatus == m_eBossPreStatus)
		{
			m_eBossPatternTwoDetail = BOSS_PATTERN_2_DETAIL::BOSS_PATTERN_2_END;
		}
		break;
	}
	case BOSS_PATTERN_2_DETAIL::BOSS_PATTERN_2_END:
	{
		m_eBossPatternTwoDetail = BOSS_PATTERN_2_DETAIL::BOSS_PATTERN_2_IN;
		m_eCurrentPattern = BOSS_2_STAGE_PATTERN::BOSS_IDLE_PATTERN;
		break;
	}
	}
}

void CBoss2::Pattern_Three()
{
	switch (m_eBossPatternThreeDetail)
	{
	case BOSS_PATTERN_3_DETAIL::BOSS_PATTERN_3_IN:
	{
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss2::Update_Render_Rect();	
		switch (m_eObjCurDir)
		{
		case OBJ_DIR::LEFT:
		{
			m_tInfo.fX = 700;
			m_tInfo.fY = 400;
			m_eBossPatternThreeDetail = BOSS_PATTERN_3_DETAIL::BOSS_JUMP_LEFT;

			CSoundMgr::Get_Instance()->StopSound(BOSS_ATTACK_SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"boss_jump.wav", BOSS_ATTACK_SOUND_EFFECT, 1.f);
			break;
		}
		case OBJ_DIR::RIGHT:
		{
			m_tInfo.fX = 320;
			m_tInfo.fY = 400;
			m_eBossPatternThreeDetail = BOSS_PATTERN_3_DETAIL::BOSS_JUMP_RIGHT;

			CSoundMgr::Get_Instance()->StopSound(BOSS_ATTACK_SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"boss_jump.wav", BOSS_ATTACK_SOUND_EFFECT, 1.f);
			break;
		}
		}
		break;
	}
	case BOSS_PATTERN_3_DETAIL::BOSS_JUMP_LEFT:
	{
		m_tInfo.fX = m_tInfo.fX + 4.5 * std::cosf(-45 * (PI / 180.0f));
		m_tInfo.fY = m_tInfo.fY + 6.5 * std::sinf(-45 * (PI / 180.0f)) + (0.5 * 9.8 * m_fJumpTime * m_fJumpTime);

		m_fJumpTime += 0.02f;
		m_eBossCurStatus = BOSS_STATUS::BOSS_JUMP_LEFT;
		m_pFrameKey = L"Boss_JUMP";
		m_tInfo.fCX = BOSS_JUMP_FCX;
		m_tInfo.fCY = BOSS_JUMP_FCY;

		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss2::Update_Collide_Rect_For_Boss2();

		
		break;
	}
	case BOSS_PATTERN_3_DETAIL::BOSS_JUMP_WALL_GRAB_LEFT:
	{
		m_eBossCurStatus = BOSS_STATUS::BOSS_GRAB_LEFT;
		m_tInfo.fCX = BOSS_WALL_GRAB_FCX;
		m_tInfo.fCY = BOSS_WALL_GRAB_FCY;
		m_pFrameKey = L"Boss_WALL_GRAB";
		
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss2::Update_Collide_Rect_For_Boss2();

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossCurStatus == m_eBossPreStatus)
		{
			CSoundMgr::Get_Instance()->StopSound(BOSS_ATTACK_SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"boss_wall_jump.wav", BOSS_ATTACK_SOUND_EFFECT, 1.f);

			m_eBossPatternThreeDetail = BOSS_PATTERN_3_DETAIL::BOSS_WALL_JUMP_LEFT;
			m_fJumpTime = 0.f;
		}

		break;
	}
	case BOSS_PATTERN_3_DETAIL::BOSS_WALL_JUMP_LEFT:
	{
		m_eBossCurStatus = BOSS_STATUS::BOSS_WALL_JUMP_LEFT;
		m_tInfo.fX = m_tInfo.fX - 10 * std::cosf(25 * (PI / 180.f));
		m_tInfo.fY = m_tInfo.fY - 10 * std::sinf(25 * (PI / 180.f)) + (0.5 * 9.8 * m_fJumpTime * m_fJumpTime);
		m_fJumpTime += 0.0325f;
		m_pFrameKey = L"Boss_WALL_JUMP";
		m_tInfo.fCX = BOSS_WALL_JUMP_FCX;
		m_tInfo.fCY = BOSS_WALL_JUMP_FCY;
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss2::Update_Collide_Rect_For_Boss2();

		if (m_bShootGatling == false)
		{
			CSoundMgr::Get_Instance()->StopSound(BOSS_ATTACK_SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"boss_gatling.wav", BOSS_ATTACK_SOUND_EFFECT, 1.f);
			m_bShootGatling = true;

		}


		if (m_tFrame.iFrameStart >= 3 && m_tFrame.iFrameStart <= 4 && m_eBossCurStatus == m_eBossPreStatus)
		{
			

			CObjMgr::Get_Instance()->Add_Object(
				OBJ_ID::OBJ_ID_BOSS_BULLET,
				CAbstractFactory<CBossBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fBossBulletAngle)
			);
			m_fBossBulletAngle += 0.3f;
		}

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossCurStatus == m_eBossPreStatus)
		{
			m_eBossPatternThreeDetail = BOSS_PATTERN_3_DETAIL::BOSS_WALL_FALL_LEFT;
			m_fBossBulletAngle = -PI / 2.0f;
			m_bShootGatling = false;
		}
		break;
	}
	case BOSS_PATTERN_3_DETAIL::BOSS_WALL_FALL_LEFT:
	{
		m_eObjCurDir = OBJ_DIR::RIGHT;

		m_eBossCurStatus = BOSS_STATUS::BOSS_JUMP_RIGHT;
		m_tInfo.fCX = BOSS_JUMP_FCX;
		m_tInfo.fCY = BOSS_JUMP_FCY;
		m_pFrameKey = L"Boss_JUMP";
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss2::Update_Collide_Rect_For_Boss2();
		m_tInfo.fX = m_tInfo.fX - 10 * std::cosf(25 * (PI / 180.0f));
		m_tInfo.fY = m_tInfo.fY - 10 * std::sinf(25 * (PI / 180.0f)) + (0.5 * 9.8 * m_fJumpTime * m_fJumpTime);
		m_fJumpTime += 0.0325f;
		
		if (m_tCollideInfo.fY > BOTTOM_LINE_FY)
		{
			m_eBossPatternThreeDetail = BOSS_PATTERN_3_DETAIL::BOSS_WALL_LANDING_LEFT;
			
			m_tInfo.fY -= m_tInfo.fCY / 2.0f;
			m_tCollideInfo.fY -= m_tCollideInfo.fCY / 2.0f;
			m_tInfo.fX + 15;
			m_tCollideInfo.fX + 15;
			
			CObj::Update_Rect();
			CObj::Update_Render_Rect();
			CBoss2::Update_Collide_Rect_For_Boss2();
			m_fJumpTime = 0.f;
			return;
		}
		break;
	}
	case BOSS_PATTERN_3_DETAIL::BOSS_WALL_LANDING_LEFT:
	{
		m_eBossCurStatus = BOSS_STATUS::BOSS_OUT_PATTERN_LEFT;
		m_tInfo.fCX = BOSS_OUT_PATTERN_FCX;
		m_tInfo.fCY = BOSS_OUT_PATTERN_FCY;
		m_pFrameKey = L"Boss_OUT_PATTERN";
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss2::Update_Collide_Rect_For_Boss2();
		
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossCurStatus == m_eBossPreStatus)
		{
			m_eBossPatternThreeDetail = BOSS_PATTERN_3_DETAIL::BOSS_PATTERN_3_DETAIL_END;
			m_eCurrentPattern = BOSS_2_STAGE_PATTERN::BOSS_IDLE_PATTERN;
		}
		break;
	}

	// right
	case BOSS_PATTERN_3_DETAIL::BOSS_JUMP_RIGHT:
	{
		m_tInfo.fX = m_tInfo.fX - 10 * std::cosf(-60 * (PI / 180.0f));
		m_tInfo.fY = m_tInfo.fY + 10 * std::sinf(-60 * (PI / 180.0f)) + (0.5 * 9.8 * m_fJumpTime * m_fJumpTime);

		m_fJumpTime += 0.02f;
		m_eBossCurStatus = BOSS_STATUS::BOSS_JUMP_RIGHT;
		m_pFrameKey = L"Boss_JUMP";
		m_tInfo.fCX = BOSS_JUMP_FCX;
		m_tInfo.fCY = BOSS_JUMP_FCY;
		
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss2::Update_Collide_Rect_For_Boss2();

		break;
	}
	case BOSS_PATTERN_3_DETAIL::BOSS_JUMP_WALL_GRAB_RIGHT:
	{
		m_eBossCurStatus = BOSS_STATUS::BOSS_GRAB_RIGHT;
		m_tInfo.fCX = BOSS_WALL_GRAB_FCX;
		m_tInfo.fCY = BOSS_WALL_GRAB_FCY;
		m_pFrameKey = L"Boss_WALL_GRAB";

		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss2::Update_Collide_Rect_For_Boss2();

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossCurStatus == m_eBossPreStatus)
		{
			CSoundMgr::Get_Instance()->StopSound(BOSS_ATTACK_SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"boss_wall_jump.wav", BOSS_ATTACK_SOUND_EFFECT, 1.f);

			m_eBossPatternThreeDetail = BOSS_PATTERN_3_DETAIL::BOSS_WALL_JUMP_RIGHT;
			m_fJumpTime = 0.f;
		}
		break;
	}
	case BOSS_PATTERN_3_DETAIL::BOSS_WALL_JUMP_RIGHT:
	{
		m_eBossCurStatus = BOSS_STATUS::BOSS_WALL_JUMP_RIGHT;
		m_tInfo.fX = m_tInfo.fX + 10 * std::cosf(25 * (PI / 180.f));
		m_tInfo.fY = m_tInfo.fY - 10 * std::sinf(25 * (PI / 180.f)) + (0.5 * 9.8 * m_fJumpTime * m_fJumpTime);

		m_fJumpTime += 0.0325f;
		m_pFrameKey = L"Boss_WALL_JUMP";
		m_tInfo.fCX = BOSS_WALL_JUMP_FCX;
		m_tInfo.fCY = BOSS_WALL_JUMP_FCY;

		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss2::Update_Collide_Rect_For_Boss2();
		
		if (m_bShootGatling == false)
		{
			CSoundMgr::Get_Instance()->StopSound(BOSS_ATTACK_SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"boss_gatling.wav", BOSS_ATTACK_SOUND_EFFECT, 1.f);
			m_bShootGatling = true;

		}

		if (m_tFrame.iFrameStart >= 3 && m_tFrame.iFrameStart <= 4 && m_eBossCurStatus == m_eBossPreStatus)
		{

			CObjMgr::Get_Instance()->Add_Object(
				OBJ_ID::OBJ_ID_BOSS_BULLET,
				CAbstractFactory<CBossBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fBossBulletAngle)
			);
			m_fBossBulletAngle += 0.3f;
		}

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossCurStatus == m_eBossPreStatus)
		{
			m_eBossPatternThreeDetail = BOSS_PATTERN_3_DETAIL::BOSS_WALL_FALL_RIGHT;
			m_fBossBulletAngle = -PI / 2.0f;
			m_bShootGatling = false;
		}
		break;
	}
	case BOSS_PATTERN_3_DETAIL::BOSS_WALL_FALL_RIGHT:
	{
		m_eObjCurDir = OBJ_DIR::LEFT;
		m_eBossCurStatus = BOSS_STATUS::BOSS_JUMP_LEFT;
		m_tInfo.fCX = BOSS_JUMP_FCX;
		m_tInfo.fCY = BOSS_JUMP_FCY;
		m_pFrameKey = L"Boss_JUMP";
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss2::Update_Collide_Rect_For_Boss2();
		m_tInfo.fX = m_tInfo.fX + 10 * std::cosf(45 * (PI / 180.0f));
		m_tInfo.fY = m_tInfo.fY - 10 * std::sinf(45 * (PI / 180.0f)) + (0.5 * 9.8 * m_fJumpTime * m_fJumpTime);
		m_fJumpTime += 0.0325f;

		if (m_tCollideInfo.fY > BOTTOM_LINE_FY)
		{
			m_eBossPatternThreeDetail = BOSS_PATTERN_3_DETAIL::BOSS_WALL_LANDING_LEFT;
			m_tInfo.fY -= m_tInfo.fCY / 2.0f;
			m_tInfo.fY += 5.0f;

			m_tCollideInfo.fY -= m_tCollideInfo.fCY / 2.0f;
			m_tCollideInfo.fY += 5.0f;

			CObj::Update_Rect();
			CObj::Update_Render_Rect();
			CBoss2::Update_Collide_Rect_For_Boss2();
			m_fJumpTime = 0.f;
			return;
		}
		break;
	}
	case BOSS_PATTERN_3_DETAIL::BOSS_WALL_LANDING_RIGHT:
	{
		m_eBossCurStatus = BOSS_STATUS::BOSS_OUT_PATTERN_LEFT;
		m_tInfo.fCX = BOSS_OUT_PATTERN_FCX;
		m_tInfo.fCY = BOSS_OUT_PATTERN_FCY;
		m_pFrameKey = L"Boss_OUT_PATTERN";
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss2::Update_Collide_Rect_For_Boss2();

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossCurStatus == m_eBossPreStatus)
		{
			m_eBossPatternThreeDetail = BOSS_PATTERN_3_DETAIL::BOSS_PATTERN_3_DETAIL_END;
			m_eCurrentPattern = BOSS_2_STAGE_PATTERN::BOSS_IDLE_PATTERN;
		}
		break;
	}
	case BOSS_PATTERN_3_DETAIL::BOSS_PATTERN_3_DETAIL_END:
	{
		m_eBossPatternThreeDetail = BOSS_PATTERN_3_DETAIL::BOSS_PATTERN_3_IN;
		m_eCurrentPattern = BOSS_2_STAGE_PATTERN::BOSS_IDLE_PATTERN;
		break;
	}
	default:
	{
		m_eCurrentPattern = BOSS_2_STAGE_PATTERN::BOSS_IDLE_PATTERN;
		m_eBossPatternThreeDetail = BOSS_PATTERN_3_DETAIL::BOSS_PATTERN_3_IN;
		break;
	}
	}
}

void CBoss2::All_Frame_Works()
{
	switch (m_eBossCurStatus)
	{
	case BOSS_STATUS::BOSS_LAY_DOWN_RIGHT:
	{
		CObj::Move_Reverse_Frame(7);
		break;
	}
	case BOSS_STATUS::BOSS_RECOVER_LEFT:
	{
		CObj::Move_Reverse_Frame(11);
		break;
	}
	case BOSS_STATUS::BOSS_WALL_JUMP_LEFT:
	{
		CObj::Move_Reverse_Frame(7);
		break;
	}
	case BOSS_STATUS::BOSS_SHOOT_GUN_LEFT:
	{
		CObj::Move_Reverse_Frame(7);
		break;
	}
	case BOSS_STATUS::BOSS_SHOOT_GUN_RIGHT:
	{
		CObj::Move_Frame();
		break;
	}
	case BOSS_STATUS::BOSS_TAKE_OUT_GUN_RIGHT:
	{
		CObj::Move_Frame();
		break;
	}
	case BOSS_STATUS::BOSS_TAKE_OUT_GUN_LEFT:
	{
		CObj::Move_Reverse_Frame(6);
		break;
	}
	case BOSS_STATUS::BOSS_OUT_PATTERN_LEFT:
	{
		CObj::Move_Frame();
	}
	case BOSS_STATUS::BOSS_OUT_PATTERN_RIGHT:
	{
		CObj::Move_Reverse_Frame(4);
	}
	case BOSS_STATUS::BOSS_IN_PATTERN_LEFT:
	{
		CObj::Move_Reverse_Frame(3);
		break;
	}
	case BOSS_STATUS::BOSS_IN_PATTERN_RIGHT:
	{
		CObj::Move_Frame();
		break;
	}
	case BOSS_STATUS::BOSS_DEAD_BODY_LEFT:
	{
		CObj::Move_Reverse_Frame(18);
		break;
	}
	case BOSS_STATUS::BOSS_NO_HEAD_DEAD_BODY_LEFT:
	{
		if (m_tFrame.iFrameStart != m_tFrame.iFrameEnd)
		{
			CObj::Move_Frame();
		}
		break;
	}
	case BOSS_STATUS::BOSS_NO_HEAD_DEAD_BODY_RIGHT:
	{
		if (m_tFrame.iFrameStart != m_tFrame.iFrameEnd)
		{
			CObj::Move_Reverse_Frame(5);
		}
		break;
	}

	default:
	{
		CObj::Move_Frame();
		break;
	}
	}
}

void CBoss2::Manage_Dead_Status()
{
	switch (m_eBossCurStatus)
	{
	case BOSS_STATUS::BOSS_DEAD_SCENE:
	{
		
		break;
	}
	case BOSS_STATUS::BOSS_DEAD_CRAWL_LEFT:
	{
		break;
	}
	case BOSS_STATUS::BOSS_DEAD_CRAWL_RIGHT:
	{
		break;
	}
	}
}

void CBoss2::All_Dead_Frame_Works()
{
	switch (m_eBossCurStatus)
	{
	case BOSS_STATUS::BOSS_DEAD_SCENE:
	{

		break;
	}
	case BOSS_STATUS::BOSS_DEAD_CRAWL_LEFT:
	{

		break;
	}
	case BOSS_STATUS::BOSS_DEAD_CRAWL_RIGHT:
	{
		break;
	}
	}
}

