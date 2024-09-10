#include "pch.h"
#include "Explosive.h"
#include "BmpMgr.h"

CExplosive::CExplosive()
{
}

CExplosive::~CExplosive()
{
	Release();
}

void CExplosive::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/item/explosive.bmp", L"EXPLOSIVE");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/effect/item/ITEM_ARROW.bmp", L"ITEM_ARROW");

	m_tInfo.fCX = EXPLOSIVE_FCX;
	m_tInfo.fCY = EXPLOSIVE_FCY;
	m_tInfo.fY -= m_tInfo.fCY / 2.0f;
	m_fSpeed = 15.0f;

	m_pFrameKey = L"EXPLOSIVE";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 0;

	m_tItemArrowFrame.iFrameStart = 0;
	m_tItemArrowFrame.iFrameEnd = 7;
	m_tItemArrowFrame.iMotion = 0;
	m_tItemArrowFrame.dwTime = GetTickCount();
	m_tItemArrowFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
}

int CExplosive::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}
	
	switch (m_eExplosiveType)
	{
	case EXPLOSIVE_TYPE::EXPLOSIVE_PICK_TYPE:
	{
		break;
	}
	case EXPLOSIVE_TYPE::EXPLOSIVE_THROW_TYPE:
	{
		m_tInfo.fX += m_fSpeed * m_vNormalVec.fX;
		m_tInfo.fY += m_fSpeed * m_vNormalVec.fY;
		break;
	}
	}

	CObj::Update_Rect();
	CObj::Update_Render_Rect();
	return OBJ_NO_EVENT;
}

void CExplosive::Late_Update()
{
	CExplosive::Move_Item_Arrow_Frame();
}

void CExplosive::Render(HDC _hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"EXPLOSIVE");
	switch (m_eExplosiveType)
	{
	case EXPLOSIVE_TYPE::EXPLOSIVE_PICK_TYPE:
	{
		HDC hArrowDC = CBmpMgr::Get_Instance()->Find_Img(L"ITEM_ARROW");

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

		GdiTransparentBlt(
			_hDC,
			m_tRenderRect.left,
			m_tRenderRect.top - m_tInfo.fCY,
			(int)ITEM_ARROW_FCX,
			(int)ITEM_ARROW_FCY,
			hArrowDC,
			(int)ITEM_ARROW_FCX * m_tItemArrowFrame.iFrameStart,
			(int)ITEM_ARROW_FCY * m_tItemArrowFrame.iMotion,
			(int)ITEM_ARROW_FCX,
			(int)ITEM_ARROW_FCY,
			RGB(255, 0, 255)
		);
		break;
	}
	case EXPLOSIVE_TYPE::EXPLOSIVE_THROW_TYPE:
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
	}
}

void CExplosive::Release()
{
	
}

void CExplosive::Move_Item_Arrow_Frame()
{
	if (m_tItemArrowFrame.dwTime + (m_tItemArrowFrame.dwSpeed) < GetTickCount())
	{
		++m_tItemArrowFrame.iFrameStart;
		if (m_tItemArrowFrame.iFrameStart > m_tItemArrowFrame.iFrameEnd)
		{
			m_tItemArrowFrame.iFrameStart = 0;
		}
		m_tItemArrowFrame.dwTime = GetTickCount();
	}
}
