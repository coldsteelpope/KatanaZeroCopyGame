#include "pch.h"
#include "Boss.h"
#include "SceneMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "BossStage01.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "BossStage01.h"
#include "SoundMgr.h"

#define FIRST_GATE_FX   132
#define FIRST_GATE_FY   380
#define FOURTH_GATE_FX  660
#define FOURTH_GATE_FY  380



CBoss::CBoss()
{
}

CBoss::~CBoss()
{
}

void CBoss::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/idle/IDLE_LEFT.bmp", L"Boss_IDLE_LEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/idle/IDLE_RIGHT.bmp", L"Boss_IDLE_RIGHT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/drawgun/DRAW_GUN_LEFT.bmp", L"Boss_DRAW_GUN_LEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/drawgun/DRAW_GUN_RIGHT.bmp", L"Boss_DRAW_GUN_RIGHT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/aim/AIM_LEFT.bmp", L"Boss_AIM_LEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/aim/AIM_RIGHT.bmp", L"Boss_AIM_RIGHT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/recover/RECOVER_LEFT.bmp", L"Boss_RECOVER_LEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/recover/RECOVER_RIGHT.bmp", L"Boss_RECOVER_RIGHT");
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/gernade/BOSS_IN_PATTERN.bmp", L"Boss_IN_PATTERN");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/machineGun/BOSS_OUT_PATTERN.bmp", L"Boss_OUT_PATTERN");


	m_eObjCurDir = OBJ_DIR::LEFT;
	m_eBossCurStatus = BOSS_STATUS::BOSS_IDLE_LEFT;
	m_pFrameKey = L"Boss_IDLE_LEFT";
	m_tInfo.fCX = BOSS_IDLE_FCX;
	m_tInfo.fCY = BOSS_IDLE_FCY;
	
}

int CBoss::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}
	CObj::Update_Rect();
	CObj::Update_Render_Rect();
	CBoss::Update_Collide_Rect_For_Boss();


	return OBJ_NO_EVENT;
}

void CBoss::Late_Update()
{
	Motion_Change();
	Manage_Status();

	switch (m_eBossCurStatus)
	{
	case BOSS_STATUS::BOSS_RECOVER_LEFT:
	{
		CObj::Move_Reverse_Frame(11);
		break;
	}
	case BOSS_STATUS::BOSS_DRAW_GUN_LEFT:
	{
		CObj::Move_Reverse_Frame(7);
		break;
	}
	case BOSS_STATUS::BOSS_AIM_LEFT:
	{
		// 움직일 필요가 없음
		break;
	}
	case BOSS_STATUS::BOSS_AIM_RIGHT:
	{
		// 움직일 필요가 없음
		break;
	}
	case BOSS_STATUS::BOSS_SHOOT_GUN_LEFT:
	{
		// 움직일 필요가 없음
		break;
	}
	case BOSS_STATUS::BOSS_SHOOT_GUN_RIGHT:
	{
		// 움직일 필요가 없음
		break;
	}
	case BOSS_STATUS::BOSS_OUT_PATTERN_RIGHT:
	{
		CObj::Move_Reverse_Frame(3);
		break;
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
	default:
	{
		CObj::Move_Frame();
		break;
	}
	}
}

void CBoss::Render(HDC _hDC)
{
	BOSS_STAGE_ONE_TYPE stageType = static_cast<CBossStage01*>(CSceneMgr::Get_Instance()->Get_Active_Scene())->Get_Boss_Stage_One_Type();

	if (stageType == BOSS_STAGE_ONE_TYPE::BOSS_STAGE_ONE_NORMAL)
	{
		HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

		// Collide Rect
		//Vec2 renderCollideRectTopLeft = CCamera::Get_Instance()->GetRenderPos(Vec2{ (float)m_tCollideRect.left, (float)m_tCollideRect.top });
		//Vec2 renderCollideRectRightBottom = CCamera::Get_Instance()->GetRenderPos(Vec2{ (float)m_tCollideRect.right, (float)m_tCollideRect.bottom });
		//::Rectangle(_hDC, renderCollideRectTopLeft.fX, renderCollideRectTopLeft.fY, renderCollideRectRightBottom.fX, renderCollideRectRightBottom.fY);

		Vec2 renderPos = CCamera::Get_Instance()->GetRenderPos(Vec2{ m_tInfo.fX, m_tInfo.fY });

		switch (m_eBossCurStatus)
		{
		case BOSS_AIM_LEFT:
		{

			HPEN lazerPen = (HPEN)::CreatePen(PS_SOLID, m_iAimLineWidth, RGB(255, 255, 0));
			HPEN oldPen = (HPEN)::SelectObject(_hDC, lazerPen);

			::MoveToEx(_hDC, renderPos.fX - 10, renderPos.fY - 25, nullptr);
			::LineTo(_hDC, 0, renderPos.fY - 25);

			::SelectObject(_hDC, oldPen);
			::DeleteObject(lazerPen);

			break;
		}
		case BOSS_AIM_RIGHT:
		{
			HPEN lazerPen = (HPEN)::CreatePen(PS_SOLID, m_iAimLineWidth, RGB(255, 255, 0));
			HPEN oldPen = (HPEN)::SelectObject(_hDC, lazerPen);

			::MoveToEx(_hDC, renderPos.fX + 8, renderPos.fY - 25, nullptr);
			::LineTo(_hDC, 800, renderPos.fY - 25);

			::SelectObject(_hDC, oldPen);
			::DeleteObject(lazerPen);
			break;
		}
		}

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
				m_tInfo.fCX * m_tFrame.iFrameStart,
				m_tInfo.fCY * m_tFrame.iMotion,
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY,
				RGB(255, 0, 255)
			);
			break;
		}
		}
	}
}

void CBoss::Release()
{

}

void CBoss::Motion_Change()
{
	if (m_eBossPreStatus != m_eBossCurStatus)
	{
		switch (m_eBossCurStatus)
		{
		
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
		case BOSS_STATUS::BOSS_DRAW_GUN_LEFT:
		{
			m_tFrame.iFrameStart = 7;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case BOSS_STATUS::BOSS_DRAW_GUN_RIGHT:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
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
		case BOSS_STATUS::BOSS_AIM_LEFT:
		{
			m_tFrame.iFrameStart = 9;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case BOSS_STATUS::BOSS_AIM_RIGHT:
		{
			m_tFrame.iFrameStart = 9;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case BOSS_STATUS::BOSS_SHOOT_GUN_LEFT:
		{
			m_tFrame.iFrameStart = 9;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case BOSS_STATUS::BOSS_SHOOT_GUN_RIGHT:
		{
			m_tFrame.iFrameStart = 9;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
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
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case BOSS_STATUS::BOSS_IN_PATTERN_RIGHT:
		{
			m_tFrame.iFrameStart = 3;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		}
		m_eBossPreStatus = m_eBossCurStatus;
	}
}

void CBoss::Manage_Status()
{
	switch (m_eBossCurStatus)
	{
	case BOSS_STATUS::BOSS_RECOVER_LEFT:
	{
		m_tInfo.fCX = BOSS_RECOVER_FCX;
		m_tInfo.fCY = BOSS_RECOVER_FCY;
		m_pFrameKey = L"Boss_RECOVER_LEFT";
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		m_iAimLineWidth = 5;

		//CBoss::Update_Collide_Rect_For_Boss();
		ZeroMemory(&m_tCollideRect, sizeof(RECT));
		
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossCurStatus == m_eBossPreStatus)
		{
			int iRandom = rand() % 2;
			switch (iRandom)
			{
			case 0:
			{
				m_eBossCurStatus = BOSS_STATUS::BOSS_IN_PATTERN_LEFT;
				break;
			}
			case 1:
			{
				m_eBossCurStatus = BOSS_STATUS::BOSS_IN_PATTERN_RIGHT;
				break;
			}
			}
			break;
		}
		break;
	}
	case BOSS_STATUS::BOSS_RECOVER_RIGHT:
	{
		m_tInfo.fCX = BOSS_RECOVER_FCX;
		m_tInfo.fCY = BOSS_RECOVER_FCY;
		m_pFrameKey = L"Boss_RECOVER_RIGHT";
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss::Update_Collide_Rect_For_Boss();
		ZeroMemory(&m_tCollideRect, sizeof(RECT));
		m_iAimLineWidth = 5;

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossCurStatus == m_eBossPreStatus)
		{
			int iRandom = rand() % 2;
			switch (iRandom)
			{
			case 0:
			{
				m_eBossCurStatus = BOSS_STATUS::BOSS_IN_PATTERN_LEFT;
				break;
			}
			case 1:
			{
				m_eBossCurStatus = BOSS_STATUS::BOSS_IN_PATTERN_RIGHT;
				break;
			}
			}
			break;
		}
		break;
	}
	case BOSS_STATUS::BOSS_IN_PATTERN_LEFT:
	{
		m_tInfo.fX = FOURTH_GATE_FX;
		m_tInfo.fY = FOURTH_GATE_FY;
		m_eObjCurDir = OBJ_DIR::LEFT;
		m_tInfo.fCX = BOSS_IN_PATTERN_FCX;
		m_tInfo.fCY = BOSS_IN_PATTERN_FCY;
		m_pFrameKey = L"Boss_IN_PATTERN";
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss::Update_Collide_Rect_For_Boss();

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossCurStatus == m_eBossPreStatus)
		{
			m_eBossCurStatus = BOSS_STATUS::BOSS_IDLE_LEFT;
			break;
		}
		break;
	}
	case BOSS_STATUS::BOSS_IN_PATTERN_RIGHT:
	{
		m_tInfo.fX = FIRST_GATE_FX;
		m_tInfo.fY = FIRST_GATE_FY;
		m_eObjCurDir = OBJ_DIR::RIGHT;
		m_tInfo.fCX = BOSS_IN_PATTERN_FCX;
		m_tInfo.fCY = BOSS_IN_PATTERN_FCY;
		m_pFrameKey = L"Boss_IN_PATTERN";
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss::Update_Collide_Rect_For_Boss();

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossCurStatus == m_eBossPreStatus)
		{
			m_eBossCurStatus = BOSS_STATUS::BOSS_IDLE_RIGHT;
			break;
		}
		break;
	}
	case BOSS_STATUS::BOSS_IDLE_LEFT:
	{
		m_eObjCurDir = OBJ_DIR::LEFT;
		m_eBossCurStatus = BOSS_STATUS::BOSS_IDLE_LEFT;
		m_tInfo.fCX = BOSS_IDLE_FCX;
		m_tInfo.fCY = BOSS_IDLE_FCY;
		m_pFrameKey = L"Boss_IDLE_LEFT";
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss::Update_Collide_Rect_For_Boss();
		
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossCurStatus == m_eBossPreStatus)
		{

			m_eBossCurStatus = BOSS_STATUS::BOSS_DRAW_GUN_LEFT;
			break;
		}
		break;
	}
	case BOSS_STATUS::BOSS_IDLE_RIGHT:
	{
		m_eObjCurDir = OBJ_DIR::RIGHT;
		m_eBossCurStatus = BOSS_STATUS::BOSS_IDLE_RIGHT;
		m_tInfo.fCX = BOSS_IDLE_FCX;
		m_tInfo.fCY = BOSS_IDLE_FCY;
		m_pFrameKey = L"Boss_IDLE_RIGHT";
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss::Update_Collide_Rect_For_Boss();

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossCurStatus == m_eBossPreStatus)
		{

			m_eBossCurStatus = BOSS_STATUS::BOSS_DRAW_GUN_RIGHT;
			break;
		}
		break;
	}
	case BOSS_STATUS::BOSS_DRAW_GUN_LEFT:
	{
		m_eObjCurDir = OBJ_DIR::LEFT;
		m_eBossCurStatus = BOSS_STATUS::BOSS_DRAW_GUN_LEFT;
		m_tInfo.fCX = BOSS_DRAW_GUN_FCX;
		m_tInfo.fCY = BOSS_DRAW_GUN_FCY;
		m_pFrameKey = L"Boss_DRAW_GUN_LEFT";

		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss::Update_Collide_Rect_For_Boss();

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossCurStatus == m_eBossPreStatus)
		{
			CSoundMgr::Get_Instance()->StopSound(BOSS_ATTACK_SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"aimground.wav", BOSS_ATTACK_SOUND_EFFECT, 1.f);
			m_eBossCurStatus = BOSS_STATUS::BOSS_AIM_LEFT;
			m_dwAimTime = GetTickCount();
			m_dwAimLineTime = GetTickCount();
			m_iAimLineWidth = 5;

			break;
		}
		break;
	}
	case BOSS_STATUS::BOSS_DRAW_GUN_RIGHT:
	{
		m_eObjCurDir = OBJ_DIR::RIGHT;
		m_eBossCurStatus = BOSS_STATUS::BOSS_DRAW_GUN_RIGHT;
		m_tInfo.fCX = BOSS_DRAW_GUN_FCX;
		m_tInfo.fCY = BOSS_DRAW_GUN_FCY;
		m_pFrameKey = L"Boss_DRAW_GUN_RIGHT";

		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss::Update_Collide_Rect_For_Boss();

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossCurStatus == m_eBossPreStatus)
		{
			CSoundMgr::Get_Instance()->StopSound(BOSS_ATTACK_SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"aimground.wav", BOSS_ATTACK_SOUND_EFFECT, 1.f);
			m_eBossCurStatus = BOSS_STATUS::BOSS_AIM_RIGHT;
			m_dwAimTime = GetTickCount();
			m_dwAimLineTime = GetTickCount();
			m_iAimLineWidth = 5;

			break;
		}
		break;
	}
	case BOSS_STATUS::BOSS_AIM_LEFT:
	{
		m_eObjCurDir = OBJ_DIR::LEFT;
		m_eBossCurStatus = BOSS_STATUS::BOSS_AIM_LEFT;
		m_tInfo.fCX = BOSS_AIM_FCX;
		m_tInfo.fCY = BOSS_AIM_FCY;
		m_pFrameKey = L"Boss_AIM_LEFT";

		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss::Update_Collide_Rect_For_Boss();

		if (m_dwAimLineTime + 300 < GetTickCount())
		{
			m_iAimLineWidth -= 1;
			m_dwAimLineTime = GetTickCount();
		}

		if (m_dwAimTime + 1500 < GetTickCount())
		{
			CSoundMgr::Get_Instance()->StopSound(BOSS_ATTACK_SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"lazer.wav", BOSS_ATTACK_SOUND_EFFECT, 1.f);

			CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_LAZER, CAbstractFactory<CLazer>::Create(m_tCollideInfo.fX - 525, m_tInfo.fY - 25, LAZER_TYPE::HORIZONTAL));
			m_eBossCurStatus = BOSS_STATUS::BOSS_SHOOT_GUN_LEFT;
			m_dwShootTime = GetTickCount();
		}
		
		break;
	}
	case BOSS_STATUS::BOSS_AIM_RIGHT:
	{
		m_eObjCurDir = OBJ_DIR::RIGHT;
		m_eBossCurStatus = BOSS_STATUS::BOSS_AIM_RIGHT;
		m_tInfo.fCX = BOSS_AIM_FCX;
		m_tInfo.fCY = BOSS_AIM_FCY;
		m_pFrameKey = L"Boss_AIM_RIGHT";
		
		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss::Update_Collide_Rect_For_Boss();

		if (m_dwAimLineTime + 300 < GetTickCount())
		{
			m_iAimLineWidth -= 1;
			m_dwAimLineTime = GetTickCount();
		}

		if (m_dwAimTime + 1500 < GetTickCount())
		{
			CSoundMgr::Get_Instance()->StopSound(BOSS_ATTACK_SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"lazer.wav", BOSS_ATTACK_SOUND_EFFECT, 1.f);

			CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_LAZER, CAbstractFactory<CLazer>::Create(m_tCollideInfo.fX + 525, m_tInfo.fY - 25, LAZER_TYPE::HORIZONTAL));
			m_eBossCurStatus = BOSS_STATUS::BOSS_SHOOT_GUN_RIGHT;
			m_dwShootTime = GetTickCount();
		}

		break;
	}
	case BOSS_STATUS::BOSS_SHOOT_GUN_LEFT:
	{
		if (m_dwShootTime + 1000 < GetTickCount())
		{
			CSoundMgr::Get_Instance()->StopSound(BOSS_ATTACK_SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"huntress_vanish.wav", BOSS_ATTACK_SOUND_EFFECT, 1.f);

			m_eBossCurStatus = BOSS_STATUS::BOSS_OUT_PATTERN_RIGHT;
		}
		break;
	}
	case BOSS_STATUS::BOSS_SHOOT_GUN_RIGHT:
	{
		if (m_dwShootTime + 1000 < GetTickCount())
		{
			CSoundMgr::Get_Instance()->StopSound(BOSS_ATTACK_SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"huntress_vanish.wav", BOSS_ATTACK_SOUND_EFFECT, 1.f);

			m_eBossCurStatus = BOSS_STATUS::BOSS_OUT_PATTERN_LEFT;
		}
		break;
	}
	case BOSS_STATUS::BOSS_OUT_PATTERN_LEFT:
	{
		m_eObjCurDir = OBJ_DIR::LEFT;
		m_eBossCurStatus = BOSS_STATUS::BOSS_OUT_PATTERN_LEFT;
		m_tInfo.fCX = BOSS_OUT_PATTERN_FCX;
		m_tInfo.fCY = BOSS_OUT_PATTERN_FCY;
		m_pFrameKey = L"Boss_OUT_PATTERN";

		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss::Update_Collide_Rect_For_Boss();

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossCurStatus == m_eBossPreStatus)
		{
			CSoundMgr::Get_Instance()->StopSound(BOSS_ATTACK_SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"huntress_vanish.wav", BOSS_ATTACK_SOUND_EFFECT, 1.f);


			int iRandom = rand() % 2;
			switch (iRandom)
			{
			case 0:
			{
				m_eBossCurStatus = BOSS_STATUS::BOSS_IN_PATTERN_LEFT;
				break;
			}
			case 1:
			{
				m_eBossCurStatus = BOSS_STATUS::BOSS_IN_PATTERN_RIGHT;
				break;
			}
			}
		}

		break;
	}
	case BOSS_STATUS::BOSS_OUT_PATTERN_RIGHT:
	{
		m_eObjCurDir = OBJ_DIR::RIGHT;
		m_eBossCurStatus = BOSS_STATUS::BOSS_OUT_PATTERN_RIGHT;
		m_tInfo.fCX = BOSS_OUT_PATTERN_FCX;
		m_tInfo.fCY = BOSS_OUT_PATTERN_FCY;
		m_pFrameKey = L"Boss_OUT_PATTERN";

		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CBoss::Update_Collide_Rect_For_Boss();

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eBossCurStatus == m_eBossPreStatus)
		{

			int iRandom = rand() % 2;
			switch (iRandom)
			{
			case 0:
			{
				m_eBossCurStatus = BOSS_STATUS::BOSS_IN_PATTERN_LEFT;
				break;
			}
			case 1:
			{
				m_eBossCurStatus = BOSS_STATUS::BOSS_IN_PATTERN_RIGHT;
				break;
			}
			}
		}
		break;
	}
	}
}

void CBoss::Set_Target(CObj* _pTarget)
{
	m_pTarget = _pTarget;
}

void CBoss::Update_Collide_Rect_For_Boss()
{
	m_tCollideInfo.fX = m_tInfo.fX - 10;
	m_tCollideInfo.fY = m_tInfo.fY - 10;
	m_tCollideInfo.fCX = BOSS_IDLE_FCX * 0.75;
	m_tCollideInfo.fCY = BOSS_IDLE_FCY * 0.75;
	
	m_tCollideRect.left = (long)(m_tCollideInfo.fX - m_tCollideInfo.fCX / 2.f);
	m_tCollideRect.top = (long)(m_tCollideInfo.fY - m_tCollideInfo.fCY / 2.f) ;
	m_tCollideRect.right = (long)(m_tCollideInfo.fX + m_tCollideInfo.fCX / 2.f);
	m_tCollideRect.bottom = (long)(m_tCollideInfo.fY + m_tCollideInfo.fCY / 2.f);
}

