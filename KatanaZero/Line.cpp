#include "pch.h"
#include "Line.h"
#include "ScrollMgr.h"
#include "Camera.h"

CLine::CLine()
{
}

CLine::CLine(LINEPOINT& tLeft, LINEPOINT& tRight, LINE_TYPE _eLineType)
	: m_tInfo(tLeft, tRight)
{
	m_eType = _eLineType;
}

CLine::~CLine()
{

}

void CLine::Render(HDC _hDC)
{
	switch (m_eType)
	{
	case LINE_TYPE::NORMAL:
	{
		Vec2 vLeftPos = CCamera::Get_Instance()->GetRenderPos(Vec2{ m_tInfo.tLeft.fX, m_tInfo.tLeft.fY });
		Vec2 vRightPos = CCamera::Get_Instance()->GetRenderPos(Vec2{ m_tInfo.tRight.fX, m_tInfo.tRight.fY });

		HPEN bluePen = (HPEN)::CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		HPEN oldPen = (HPEN)::SelectObject(_hDC, bluePen);

		::MoveToEx(_hDC, (int)vLeftPos.fX, (int)vLeftPos.fY, nullptr);
		::LineTo(_hDC, (int)vRightPos.fX, (int)vRightPos.fY);


		::SelectObject(_hDC, oldPen);
		::DeleteObject(bluePen);

		break;
	}
	case LINE_TYPE::SOLID:
	{
		Vec2 vLeftPos = CCamera::Get_Instance()->GetRenderPos(Vec2{ m_tInfo.tLeft.fX, m_tInfo.tLeft.fY });
		Vec2 vRightPos = CCamera::Get_Instance()->GetRenderPos(Vec2{ m_tInfo.tRight.fX, m_tInfo.tRight.fY });

		HPEN redPen = (HPEN)::CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN oldPen = (HPEN)::SelectObject(_hDC, redPen);

		//int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
		::MoveToEx(_hDC, (int)vLeftPos.fX, (int)vLeftPos.fY, nullptr);
		::LineTo(_hDC, (int)vRightPos.fX, (int)vRightPos.fY);


		::SelectObject(_hDC, oldPen);
		::DeleteObject(redPen);

		break;
	}
	default:
	{
		Vec2 vLeftPos = CCamera::Get_Instance()->GetRenderPos(Vec2{ m_tInfo.tLeft.fX, m_tInfo.tLeft.fY });
		Vec2 vRightPos = CCamera::Get_Instance()->GetRenderPos(Vec2{ m_tInfo.tRight.fX, m_tInfo.tRight.fY });

		HPEN bluePen = (HPEN)::CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		HPEN oldPen = (HPEN)::SelectObject(_hDC, bluePen);

		::MoveToEx(_hDC, (int)vLeftPos.fX, (int)vLeftPos.fY, nullptr);
		::LineTo(_hDC, (int)vRightPos.fX, (int)vRightPos.fY);


		::SelectObject(_hDC, oldPen);
		::DeleteObject(bluePen);

	}
	}
}

float CLine::Get_Scope()
{
	float fWidth = m_tInfo.tRight.fX - m_tInfo.tLeft.fX;
	float fHeight = m_tInfo.tRight.fY - m_tInfo.tLeft.fY;
	return fHeight / fWidth;
}

float CLine::Get_Y(float _fX)
{
	float x0 = m_tInfo.tLeft.fX;
	float y0 = m_tInfo.tLeft.fY;
	
	float fY = (Get_Scope()) * (_fX - x0) + y0;

	return fY;
}
