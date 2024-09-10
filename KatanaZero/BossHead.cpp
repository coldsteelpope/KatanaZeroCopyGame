#include "pch.h"
#include "BossHead.h"
#include "BmpMgr.h"
#include "Camera.h"

CBossHead::CBossHead()
{
}

CBossHead::~CBossHead()
{
	Release();
}

void CBossHead::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/die/ONLY_HEAD.bmp", L"Boss_ONLY_HEAD");
	m_tInfo.fCX = 40;
	m_tInfo.fCY = 42;
	switch (m_eObjCurDir)
	{
	case OBJ_DIR::LEFT:
	{
		m_eBossHeadCurStatus = BOSS_HEAD_STATUS::BOSS_HEAD_LEFT;
		break;
	}
	case OBJ_DIR::RIGHT:
	{
		m_eBossHeadCurStatus = BOSS_HEAD_STATUS::BOSS_HEAD_RIGHT;
		break;
	}
	}

	m_fSpeed = 7.f;
}

int CBossHead::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	CObj::Update_Rect();
	CObj::Update_Render_Rect();
	CBossHead::Update_Collide_Rect_Using_Boss_Head_Info();
	
	switch (m_eObjCurDir)
	{
	case OBJ_DIR::LEFT:
	{
		m_tInfo.fX = m_tInfo.fX + m_fSpeed * std::cosf(m_fTheta);
		
		break;
	}
	case OBJ_DIR::RIGHT:
	{
		m_tInfo.fX = m_tInfo.fX - m_fSpeed * std::cosf(m_fTheta);
		break;
	}
	}

	if (m_fSpeed < 0.f)
	{
		if (m_fStopIFramtStart != m_tFrame.iFrameStart)
		{
			m_fStopIFramtStart = m_tFrame.iFrameStart;
		}
		m_tFrame.iFrameStart = m_fStopIFramtStart;
		return OBJ_NO_EVENT;
	}

	m_fSpeed -= 0.1f;
	
	
	return OBJ_NO_EVENT;
}

void CBossHead::Late_Update()
{
	CBossHead::Motion_Change();
	CBossHead::Move_Frames();
}

void CBossHead::Render(HDC _hDC)
{
	CObj::Update_Rect();
	CObj::Update_Render_Rect();
	CBossHead::Update_Collide_Rect_Using_Boss_Head_Info();

	Vec2 renderColliderLeftTop = CCamera::Get_Instance()->GetRenderPos(Vec2{ (float)m_tCollideRect.left, (float)m_tCollideRect.top });
	Vec2 renderColliderRightBottom = CCamera::Get_Instance()->GetRenderPos(Vec2{ (float)m_tCollideRect.right, (float)m_tCollideRect.bottom });

	//::Rectangle(_hDC, renderColliderLeftTop.fX, renderColliderLeftTop.fY, renderColliderRightBottom.fX, renderColliderRightBottom.fY);
	

	HDC hHeadDC = CBmpMgr::Get_Instance()->Find_Img(L"Boss_ONLY_HEAD");
	GdiTransparentBlt(
		_hDC,
		m_tRenderRect.left,
		m_tRenderRect.top,
		(int)m_tInfo.fCX / 1.75f,
		(int)m_tInfo.fCY / 1.75f,
		hHeadDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart, 
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 0, 255)
	);
}

void CBossHead::Release()
{

}

void CBossHead::Motion_Change()
{
	if (m_eBossHeadPreStatus != m_eBossHeadCurStatus)
	{
		switch (m_eBossHeadCurStatus)
		{
		case BOSS_HEAD_STATUS::BOSS_HEAD_LEFT:
		{
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		case BOSS_HEAD_STATUS::BOSS_HEAD_RIGHT:
		{
			m_tFrame.iFrameStart = 7;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
			break;
		}
		}
		m_eBossHeadPreStatus = m_eBossHeadCurStatus;
	}
}

void CBossHead::Move_Frames()
{
	switch (m_eBossHeadCurStatus)
	{
	case BOSS_HEAD_STATUS::BOSS_HEAD_LEFT:
	{
		CObj::Move_Frame();
		break;
	}
	case BOSS_HEAD_STATUS::BOSS_HEAD_RIGHT:
	{
		CObj::Move_Reverse_Frame(7);
		break;
	}
	}
}



void CBossHead::Update_Collide_Rect_Using_Boss_Head_Info()
{
	m_tCollideInfo.fX = m_tInfo.fX - 8;
	m_tCollideInfo.fY = m_tInfo.fY - 8;
	m_tCollideInfo.fCX = m_tInfo.fCX / 2.25f;
	m_tCollideInfo.fCY = m_tInfo.fCY / 2.25f;
	
	m_tCollideRect.left		= (long)(m_tCollideInfo.fX - m_tCollideInfo.fCX / 2.0f);
	m_tCollideRect.top		= (long)(m_tCollideInfo.fY - m_tCollideInfo.fCY / 2.0f);
	m_tCollideRect.right	= (long)(m_tCollideInfo.fX + m_tCollideInfo.fCX / 2.0f);
	m_tCollideRect.bottom	= (long)(m_tCollideInfo.fY + m_tCollideInfo.fCY / 2.0f);
}
