#include "pch.h"
#include "Samurai.h"
#include "BmpMgr.h"

CSamurai::CSamurai()
{
}

CSamurai::~CSamurai()
{
	Release();
}

void CSamurai::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/effect/SAMURAI_DANCE.bmp", L"SAMURAI_DANCE");

	m_tInfo.fCX = 34;
	m_tInfo.fCY = 43;
	
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 11;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
}

int CSamurai::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	CObj::Update_Rect();
	CObj::Update_Render_Rect();
	
	return OBJ_NO_EVENT;
}

void CSamurai::Late_Update()
{
	CObj::Move_Frame();
}

void CSamurai::Render(HDC _hDC)
{
	HDC samuraiDC = CBmpMgr::Get_Instance()->Find_Img(L"SAMURAI_DANCE");
	
	GdiTransparentBlt(
		_hDC,
		m_tRenderRect.left,
		m_tRenderRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		samuraiDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 0, 255)
	);
}

void CSamurai::Release()
{
}
