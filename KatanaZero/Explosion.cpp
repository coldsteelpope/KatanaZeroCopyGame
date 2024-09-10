#include "pch.h"
#include "Explosion.h"
#include "BmpMgr.h"
#include "SoundMgr.h"

CExplosion::CExplosion()
{
}

CExplosion::~CExplosion()
{
	Release();
}

void CExplosion::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/explosion/EXPLOSION.bmp", L"EXPLOSION");
	m_tInfo.fCX = EXPLOSION_FCX;
	m_tInfo.fCY = EXPLOSION_FCY;
	m_tInfo.fY -= m_tInfo.fCY / 2.0f;
	
	m_pFrameKey = L"EXPLOSION";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 9;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 100;


}

int CExplosion::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}
	CObj::Update_Rect();
	CObj::Update_Render_Rect();
	return OBJ_NO_EVENT;
}

void CExplosion::Late_Update()
{
	//if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	//{
	//	m_bDead = true;
	//}
	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		m_bDead = true;
	}
	CObj::Move_Frame();
}

void CExplosion::Render(HDC _hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"EXPLOSION");

	if (m_tRenderRect.left == m_tRenderRect.right)
	{
		return;
	}
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

void CExplosion::Release()
{
	
}
