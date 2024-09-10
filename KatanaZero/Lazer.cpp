#include "pch.h"
#include "Lazer.h"
#include "BmpMgr.h"
#include "Camera.h"

CLazer::CLazer()
{
}

CLazer::~CLazer()
{
	Release();
}

void CLazer::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/attackEffect/lazer.bmp", L"LAZER");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/attackEffect/lazer_vertical.bmp", L"LAZER_VERTICAL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/attackEffect/Plg.bmp", L"LAZER_PLG");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/attackEffect/Reset.bmp", L"LAZER_RESET");


	switch (m_eLazerType)
	{
	case LAZER_TYPE::HORIZONTAL:
	{
		m_tInfo.fCX = LAZER_WIDTH;
		m_tInfo.fCY = LAZER_HEIGHT;
		m_pFrameKey = L"LAZER";

		break;
	}
	case LAZER_TYPE::VERTICAL:
	{
		m_tInfo.fCX = LAZER_HEIGHT;
		m_tInfo.fCY = LAZER_WIDTH;
		m_pFrameKey = L"LAZER_VERTICAL";
		break;
	}
	}

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
	m_tFrame.dwTime = GetTickCount();
	m_fAngle = 0.f;
	
}

int CLazer::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}


	CObj::Update_Rect();
	CObj::Update_Render_Rect();
	CLazer::Update_Collide_Rect_For_Lazer();
	return OBJ_NO_EVENT;
}

void CLazer::Late_Update()
{
	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		m_bDead = true;
	}

	CObj::Move_Frame();
	++m_iCount;
}

void CLazer::Render(HDC _hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);
	CObj::Update_Rect();
	CObj::Update_Render_Rect();
	CLazer::Update_Collide_Rect_For_Lazer();


	switch (m_eLazerType)
	{
	case LAZER_TYPE::VERTICAL:
	{
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
		break;
	}
	case LAZER_TYPE::HORIZONTAL:
	{
		GdiTransparentBlt(
			_hDC,
			m_tRenderRect.left,
			m_tRenderRect.top,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hMemDC,
			(int)m_tInfo.fCX * m_tFrame.iMotion,
			(int)m_tInfo.fCY * m_tFrame.iFrameStart,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			RGB(255, 0, 255)
		);
		break;
	}
	}



	// COllide Rect -> 이걸로 충돌 처리할것
	//Vec2 vRenderCollideRectLeftTop = CCamera::Get_Instance()->GetRenderPos(Vec2{ (float)m_tCollideRect.left, (float)m_tCollideRect.top });
	//Vec2 vRenderCollideRectRightBottom = CCamera::Get_Instance()->GetRenderPos(Vec2{ (float)m_tCollideRect.right, (float)m_tCollideRect.bottom });
	//::Rectangle(_hDC, vRenderCollideRectLeftTop.fX, vRenderCollideRectLeftTop.fY, vRenderCollideRectRightBottom.fX, vRenderCollideRectRightBottom.fY);

}

void CLazer::Release()
{

}

void CLazer::Set_Points()
{
	float	fDiagonal = sqrt((m_tInfo.fCX / 2.f) * (m_tInfo.fCX / 2.f) + (m_tInfo.fCY / 2.f) * (m_tInfo.fCY / 2.f));
	// 좌상단
	m_tPoints[0].x = long((m_tInfo.fCX / 2.f) + cos((m_fAngle + 135.f) * PI / 180.f) * fDiagonal);
	m_tPoints[0].y = long((m_tInfo.fCY / 2.f) - sin((m_fAngle + 135.f) * PI / 180.f) * fDiagonal);

	// 우상단
	m_tPoints[1].x = long((m_tInfo.fCX / 2.f) + cos((m_fAngle + 45.f) * PI / 180.f) * fDiagonal);
	m_tPoints[1].y = long((m_tInfo.fCY / 2.f) - sin((m_fAngle + 45.f) * PI / 180.f) * fDiagonal);

	// 좌하단
	m_tPoints[2].x = long((m_tInfo.fCX / 2.f) + cos((m_fAngle + 225.f) * PI / 180.f) * fDiagonal);
	m_tPoints[2].y = long((m_tInfo.fCY / 2.f) - sin((m_fAngle + 225.f) * PI / 180.f) * fDiagonal);
}

void CLazer::Update_Collide_Rect_For_Lazer()
{
	m_tCollideInfo.fX = m_tInfo.fX;
	m_tCollideInfo.fY = m_tInfo.fY;
	m_tCollideInfo.fCX = m_tInfo.fCX;
	m_tCollideInfo.fCY = m_tInfo.fCY;

	switch (m_eLazerType)
	{
	case LAZER_TYPE::HORIZONTAL:
	{
		m_tCollideRect.left = (long)(m_tCollideInfo.fX - m_tCollideInfo.fCX / 2.0f);
		m_tCollideRect.top = (long)(m_tCollideInfo.fY - m_tCollideInfo.fCY / 2.0f) + (4 * m_iCount);
		m_tCollideRect.right = (long)(m_tCollideInfo.fX + m_tCollideInfo.fCX / 2.0f);
		m_tCollideRect.bottom = (long)(m_tCollideInfo.fY + m_tCollideInfo.fCY / 2.0f) - (4 * m_iCount);

		if (m_tCollideRect.top >= m_tCollideRect.bottom)
		{
			m_tCollideRect.top = m_tCollideRect.bottom;
		}
		break;
	}
	case LAZER_TYPE::VERTICAL:
	{
		m_tCollideRect.left = (long)(m_tCollideInfo.fX - m_tCollideInfo.fCX / 2.0f) + (4 * m_iCount);
		m_tCollideRect.top = (long)(m_tCollideInfo.fY - m_tCollideInfo.fCY / 2.0f);
		m_tCollideRect.right = (long)(m_tCollideInfo.fX + m_tCollideInfo.fCX / 2.0f) - (4 * m_iCount);
		m_tCollideRect.bottom = (long)(m_tCollideInfo.fY + m_tCollideInfo.fCY / 2.0f);

		if (m_tCollideRect.left >= m_tCollideRect.right)
		{
			m_tCollideRect.right = m_tCollideRect.left;
		}
		break;
	}

	}

}
