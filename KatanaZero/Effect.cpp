#include "pch.h"
#include "Effect.h"
#include "BmpMgr.h"

CEffect::CEffect() : m_bDone(false)
{
}

CEffect::~CEffect()
{
	Release();
}

void CEffect::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/effect/dragon/attack/PlgForAttackEffect.bmp", L"Plg");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/effect/dragon/attack/ResetForAttackEffect.bmp", L"Reset");
	if (lstrcmp(L"Effect_Dragon_Attack", m_pFrameKey) == 0)
	{
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 3;
		m_tFrame.iMotion = 0;
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.dwSpeed = 50;
	}

	m_fAngle = 0.f;
}

int CEffect::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	CObj::Update_Rect();
	CObj::Update_Render_Rect();
	return OBJ_NO_EVENT;
}

void CEffect::Late_Update()
{
	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		m_bDead = true;
	}
	
	CObj::Move_Frame();
}

void CEffect::Render(HDC _hDC)
{	
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey, m_eObjCurDir);
	CObj::Update_Render_Rect();
	
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
		RGB(254, 0, 254)
	);
}

void CEffect::Release()
{

}



// ¹é¾÷¿ë
//void CEffect::Render(HDC _hDC)
//{
//	if (m_bDead == true)
//	{
//		return;
//	}
//
//	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey, m_eObjCurDir);
//	CObj::Update_Render_Rect();
//
//	GdiTransparentBlt(
//		_hDC,
//		m_tRenderRect.left,
//		m_tRenderRect.top,
//		(int)m_tInfo.fCX,
//		(int)m_tInfo.fCY,
//		hMemDC,
//		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
//		(int)m_tInfo.fCY * m_tFrame.iMotion,
//		(int)m_tInfo.fCX,
//		(int)m_tInfo.fCY,
//		RGB(254, 0, 254)
//	);
//}