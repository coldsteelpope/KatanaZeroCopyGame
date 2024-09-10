#include "pch.h"
#include "Grunt.h"
#include "BmpMgr.h"
#include "LineMgr.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Blood.h"

CGrunt::CGrunt() : dwIdleTime(GetTickCount())
{
}

CGrunt::~CGrunt()
{
	Release();
	
}

void CGrunt::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/grunt/idle/IDLE_LEFT.bmp", L"Grunt_IDLE", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/grunt/idle/IDLE_RIGHT.bmp", L"Grunt_IDLE", OBJ_DIR::RIGHT);
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/grunt/walk/WALK_LEFT.bmp", L"Grunt_WALK", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/grunt/walk/WALK_RIGHT.bmp", L"Grunt_WALK", OBJ_DIR::RIGHT);
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/grunt/run/RUN_LEFT.bmp", L"Grunt_CHASE", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/grunt/run/RUN_RIGHT.bmp", L"Grunt_CHASE", OBJ_DIR::RIGHT);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/grunt/attack/ATTACK_LEFT.bmp", L"Grunt_ATTACK", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/grunt/attack/ATTACK_RIGHT.bmp", L"Grunt_ATTACK", OBJ_DIR::RIGHT);
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/grunt/dead/DEAD_LEFT.bmp", L"Grunt_DEAD", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/grunt/dead/DEAD_RIGHT.bmp", L"Grunt_DEAD", OBJ_DIR::RIGHT);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/effect/enemy/FOLLOW.bmp", L"ENEMY_FOLLOW_MARK");

	m_eObjPreStatus = OBJ_STATUS::OBJ_STATUS_END;
	m_eObjCurStatus = OBJ_STATUS::IDLE;
	m_fSpeed = 1.f;
	m_pFrameKey = L"Grunt_IDLE";
	m_fRayRadius = 100.f;
	m_fAttackRadius = 10.f;


	m_tFollowFrame.iFrameStart = 0;
	m_tFollowFrame.iFrameEnd = 1;
	m_tFollowFrame.iMotion = 0;
	m_tFollowFrame.dwTime = GetTickCount();
	m_tFollowFrame.dwSpeed = 200;

	m_bBlind = false;
}



int CGrunt::Update()
{
	if (OBJ_STATUS::DEAD != m_eObjCurStatus)
	{
		if (m_bDead)
		{
			return OBJ_DEAD;
		}

		m_bBlind = false;
		CGrunt::Move();
		CObj::Update_Rect();
		CGrunt::Update_Collide_Rect();
		CObj::Update_Ray_Rect();

		return OBJ_NO_EVENT;
	}

	return OBJ_NO_EVENT;
}

void CGrunt::Late_Update()
{
	switch (m_eObjCurStatus)
	{
	case OBJ_STATUS::DEAD:
	{
		Jump();

		Motion_Change();
		Manage_Status();

		
		ZeroMemory(&m_tRayRect, sizeof(RECT));
		ZeroMemory(&m_tCollideRect, sizeof(RECT));
		ZeroMemory(&m_tAttackAreaRect, sizeof(RECT));
		if (m_tFrame.iFrameStart != m_tFrame.iFrameEnd)
		{
			CObj::Move_Frame();
		}
		break;
	}
	default:
	{
		if (m_eObjCurStatus == OBJ_STATUS::CHASE)
		{
			if (m_tFollowFrame.iFrameStart != m_tFollowFrame.iFrameEnd)
			{
				CGrunt::Follow_Frame_Start();
			}
		}

		CGrunt::Jump();
		CGrunt::Motion_Change();
		CGrunt::Manage_Status();

		CObj::Update_Render_Rect();
		CObj::Update_Collide_Rect();
		CObj::Move_Frame();

		
	}
	}

	if (m_bThunderBreathingDeath)
	{
		if (m_dwThunderBreathingDeath + 1000 < GetTickCount())
		{
			this->Set_Obj_Cur_Status(OBJ_STATUS::DEAD);
			CCamera::Get_Instance()->Camera_Shaking();
			CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_BLOOD, CAbstractFactory<CBlood>::Create(m_tInfo.fX, m_tInfo.fY, ATTACK_TYPE::NORMAL_ATTACK, m_eObjCurDir));
			m_bThunderBreathingDeath = false;

			ZeroMemory(&m_tRayRect, sizeof(RECT));
			ZeroMemory(&m_tCollideRect, sizeof(RECT));
			ZeroMemory(&m_tAttackAreaRect, sizeof(RECT));
		}
	}
}

void CGrunt::Render(HDC _hDC)
{
	CObj::Update_Render_Rect();

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey, m_eObjCurDir);
	HDC hFollowDC = CBmpMgr::Get_Instance()->Find_Img(L"ENEMY_FOLLOW_MARK");

	GdiTransparentBlt(
		_hDC,
		m_tRenderRect.left,
		m_tRenderRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 0, 255)
	);

	switch (m_eObjCurStatus)
	{
	case OBJ_STATUS::CHASE:
	{
		GdiTransparentBlt(
			_hDC,
			m_tRenderRect.left,
			m_tRenderRect.top,
			(int)ENEMY_FOLLOW_FCX,
			(int)ENEMY_FOLLOW_FCY,
			hFollowDC,
			(int)ENEMY_FOLLOW_FCX * m_tFollowFrame.iFrameStart,
			(int)ENEMY_FOLLOW_FCY * m_tFollowFrame.iMotion,
			(int)ENEMY_FOLLOW_FCX,
			(int)ENEMY_FOLLOW_FCY,
			RGB(255, 0, 255)
		);
		break;
	}
	}
}

void CGrunt::Release()
{


}

void CGrunt::Jump()
{
	float fY(0.f); // 캐릭터의 bottom이 아닌 Y의 값이다. > 나중에 _fCY로 조정 필요
	bool bValidLine = CLineMgr::Get_Instance()->Collision_Line_Enemy(m_tInfo.fX, m_fSpeed, m_tInfo.fY, m_tInfo.fCY, &fY, m_eObjCurStatus);

	if (bValidLine)
	{
		m_tInfo.fY = fY - m_tInfo.fCY / 2.0f;
	}
	else
	{
		// 선이 없다면 떨어지도록 설정
	}
}

void CGrunt::Manage_Status()
{
	switch (m_eObjCurStatus)
	{
	case OBJ_STATUS::CHASE:
	{
		m_fSpeed = 3.5f;
		m_eObjCurStatus = OBJ_STATUS::CHASE;
		m_pFrameKey = L"Grunt_CHASE";
		m_tInfo.fCX = GRUNT_CHASE_FCX;
		m_tInfo.fCY = GRUNT_CHASE_FCY;

		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CObj::Update_Attack_Rect();
		break;
	}
	case OBJ_STATUS::ATTACK:
	{
		m_fSpeed = 0.f;
		if (m_tFrame.iFrameStart == 0)
		{
			m_eObjCurStatus = OBJ_STATUS::ATTACK;
			m_pFrameKey = L"Grunt_ATTACK";
			m_tInfo.fCX = GRUNT_ATTACK_FCX;
			m_tInfo.fCY = GRUNT_ATTACK_FCY;
			m_bDamageable = false;

		}
		else if (m_tFrame.iFrameStart >= 5 && m_tFrame.iFrameStart < 7)
		{
			if (m_tFrame.iFrameStart == 5)
			{
				CSoundMgr::Get_Instance()->StopSound(GRUNT_ATTACK_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"punch.wav", GRUNT_ATTACK_EFFECT, 1.f);
			}
			m_bDamageable = true;
		}
		else if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd && m_eObjCurStatus == m_eObjPreStatus)
		{
			m_eObjCurStatus = OBJ_STATUS::CHASE;
			m_pFrameKey = L"Grunt_CHASE";
			m_tInfo.fCX = GRUNT_CHASE_FCX;
			m_tInfo.fCY = GRUNT_CHASE_FCY;
			m_bDamageable = false;

		}

		CObj::Update_Rect();
		CObj::Update_Render_Rect();
		CObj::Update_Attack_Rect();

		break;
	}
	case OBJ_STATUS::DEAD:
	{
		m_eObjCurStatus = OBJ_STATUS::DEAD;
		m_pFrameKey = L"Grunt_DEAD";
		m_tInfo.fCX = GRUNT_DEAD_FCX;
		m_tInfo.fCY = GRUNT_DEAD_FCY;

		CObj::Update_Rect();
		CObj::Update_Render_Rect();


		ZeroMemory(&m_tRayRect, sizeof(RECT));
		ZeroMemory(&m_tCollideRect, sizeof(RECT));
		ZeroMemory(&m_tAttackAreaRect, sizeof(RECT));
		break;
	}
	default:
	{
		ZeroMemory(&m_tAttackAreaRect, sizeof(RECT));
		break;
	}
	}
}

void CGrunt::Move()
{
	if (ENEMY_TYPE::WALK_TYPE == m_eEnemyType)
	{
		switch (m_eObjCurStatus)
		{
		case OBJ_STATUS::IDLE:
		{
			if (m_tInfo.fX > m_fStartWalkPos && m_tInfo.fX < m_fEndWalkPos)
			{
				m_eObjCurStatus = OBJ_STATUS::WALK;
				m_pFrameKey = L"Grunt_WALK";
				m_tInfo.fCX = GRUNT_WALK_FCX;
				m_tInfo.fCY = GRUNT_WALK_FCY;
				CObj::Update_Rect();
				CObj::Update_Render_Rect();
			}
			else
			{
				if (dwIdleTime + 3000 < GetTickCount())
				{
					m_eObjCurStatus = OBJ_STATUS::TURN;
				}
			}
			break;
		}
		case OBJ_STATUS::TURN:
		{
			switch (m_eObjCurDir)
			{
			case OBJ_DIR::LEFT:
			{
				if (m_tInfo.fX == m_fEndWalkPos)
				{
					m_tInfo.fX -= m_fSpeed;
					m_eObjCurStatus = OBJ_STATUS::WALK;
					m_pFrameKey = L"Grunt_WALK";
					m_tInfo.fCX = GRUNT_WALK_FCX;
					m_tInfo.fCY = GRUNT_WALK_FCY;
					CObj::Update_Rect();
					CObj::Update_Render_Rect();
				}
				else
				{
					m_eObjCurDir = OBJ_DIR::RIGHT;
					m_tInfo.fX += m_fSpeed;
					m_eObjCurStatus = OBJ_STATUS::WALK;
					m_pFrameKey = L"Grunt_WALK";
					m_tInfo.fCX = GRUNT_WALK_FCX;
					m_tInfo.fCY = GRUNT_WALK_FCY;
					CObj::Update_Rect();
					CObj::Update_Render_Rect();
				}
				break;
			}
			case OBJ_DIR::RIGHT:
			{
				if (m_tInfo.fX == m_fStartWalkPos)
				{
					m_tInfo.fX += m_fSpeed;
					m_eObjCurStatus = OBJ_STATUS::WALK;
					m_pFrameKey = L"Grunt_WALK";
					m_tInfo.fCX = GRUNT_WALK_FCX;
					m_tInfo.fCY = GRUNT_WALK_FCY;
					CObj::Update_Rect();
					CObj::Update_Render_Rect();

				}
				else
				{
					m_eObjCurDir = OBJ_DIR::LEFT;
					m_tInfo.fX -= m_fSpeed;
					m_eObjCurStatus = OBJ_STATUS::WALK;
					m_pFrameKey = L"Grunt_WALK";
					m_tInfo.fCX = GRUNT_WALK_FCX;
					m_tInfo.fCY = GRUNT_WALK_FCY;
					CObj::Update_Rect();
					CObj::Update_Render_Rect();

				}
				break;
			}
			}
			break;
		}
		case OBJ_STATUS::WALK:
		{
			if (m_tInfo.fX > m_fStartWalkPos && m_tInfo.fX < m_fEndWalkPos)
			{
				switch (m_eObjCurDir)
				{
				case OBJ_DIR::LEFT:
				{
					m_tInfo.fX -= m_fSpeed;
					break;
				}
				case OBJ_DIR::RIGHT:
				{
					m_tInfo.fX += m_fSpeed;
					break;
				}
				}
			}
			else if (m_tInfo.fX == m_fStartWalkPos || m_tInfo.fX == m_fEndWalkPos)
			{
				m_eObjCurStatus = OBJ_STATUS::IDLE;
				m_pFrameKey = L"Grunt_IDLE";
				m_tInfo.fCX = GRUNT_IDLE_FCX;
				m_tInfo.fCY = GRUNT_IDLE_FCY;
				CObj::Update_Rect();
				CObj::Update_Render_Rect();
				dwIdleTime = GetTickCount();
			}
			break;
		}
		case OBJ_STATUS::CHASE:
		{
			float fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
			float fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;
			float fDiagonal = sqrtf((fWidth * fWidth) + (fHeight * fHeight));
			
			float normalX = fWidth / fDiagonal;
			float normalY = fHeight / fDiagonal;
			
			if (normalX > 0)
			{
				m_eObjCurDir = OBJ_DIR::RIGHT;
				m_tInfo.fX += m_fSpeed;
			}
			else if (normalX < 0)
			{
				m_eObjCurDir = OBJ_DIR::LEFT;
				m_tInfo.fX -= m_fSpeed;
			}
			break;
		}
		}
	}
	else if (ENEMY_TYPE::STAY_TYPE == m_eEnemyType)
	{
		
	}

}

void CGrunt::Motion_Change()
{
	if (m_eObjPreStatus != m_eObjCurStatus)
	{
		switch (m_eObjCurStatus)
		{
		case OBJ_STATUS::IDLE:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case OBJ_STATUS::WALK:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case OBJ_STATUS::CHASE:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case OBJ_STATUS::ATTACK:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case OBJ_STATUS::DEAD:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 15;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		}
		m_eObjPreStatus = m_eObjCurStatus;
	}
}

void CGrunt::Update_Collide_Rect()
{
	m_tCollideInfo.fX = m_tInfo.fX;
	m_tCollideInfo.fY = m_tInfo.fY;
	m_tCollideInfo.fCX = GRUNT_IDLE_FCX;
	m_tCollideInfo.fCY = GRUNT_IDLE_FCY;

	m_tCollideRect.left = (long)(m_tCollideInfo.fX - m_tCollideInfo.fCX / 2.0f);
	m_tCollideRect.top = (long)(m_tCollideInfo.fY - m_tCollideInfo.fCX / 2.0f);
	m_tCollideRect.right = (long)(m_tCollideInfo.fX + m_tCollideInfo.fCX / 2.0f);
	m_tCollideRect.bottom = (long)(m_tCollideInfo.fY + m_tCollideInfo.fCX / 2.0f);

}

void CGrunt::Follow_Frame_Start()
{

}
