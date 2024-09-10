#include "pch.h"
#include "OilDrum.h"
#include "BmpMgr.h"

COilDrum::COilDrum()
{
}

COilDrum::~COilDrum()
{
}

void COilDrum::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/item/oil_drum.bmp", L"OIL_DRUM");

	m_tInfo.fCX = OIL_DRUM_FCX;
	m_tInfo.fCY = OIL_DRUM_FCY;
	m_tInfo.fY = m_tInfo.fY - m_tInfo.fCY / 2.0f;
	m_fSpeed = 0.f;

	m_pFrameKey = L"OIL_DRUM";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 0;
}

int COilDrum::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	CObj::Update_Rect();
	CObj::Update_Render_Rect();
	return OBJ_NO_EVENT;
}

void COilDrum::Late_Update()
{
	
}

void COilDrum::Render(HDC _hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"OIL_DRUM");
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
		RGB(254, 6, 254)
	);
}

void COilDrum::Release()
{
}
