#include "pch.h"
#include "Bullet.h"
#include "BmpMgr.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/bullet/bullet.bmp", L"BULLET");
	
	m_tInfo.fCX = 34.f;
	m_tInfo.fCY = 2.f;

	
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
	m_tFrame.iMotion = 0;
	m_pFrameKey = L"BULLET";
	
	CObj::Update_Rect();
	CObj::Update_Render_Rect();
	CBullet::Update_Collide_Rect_For_Bullet();
}

int CBullet::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}
	
	m_tInfo.fX += m_vNormalVec.fX * m_fSpeed;
	m_tInfo.fY += m_vNormalVec.fY * m_fSpeed;
	

	CObj::Update_Rect();
	CObj::Update_Render_Rect();
	CBullet::Update_Collide_Rect_For_Bullet();
	
	return OBJ_NO_EVENT;
}

void CBullet::Late_Update()
{

	
}

void CBullet::Render(HDC _hDC)
{
	CObj::Update_Rect();
	CObj::Update_Render_Rect();
	CBullet::Update_Collide_Rect_For_Bullet();

	HDC bulletDC = CBmpMgr::Get_Instance()->Find_Img(L"BULLET");
	GdiTransparentBlt(
		_hDC,
		m_tRenderRect.left,
		m_tRenderRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		bulletDC,
		0,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 0, 255)
	);
}

void CBullet::Release()
{
	
}

void CBullet::Update_Collide_Rect_For_Bullet()
{
	m_tCollideInfo.fX = m_tInfo.fX;
	m_tCollideInfo.fY = m_tInfo.fY;
	m_tCollideInfo.fCX = m_tInfo.fCX;
	m_tCollideInfo.fCY = m_tInfo.fCY;

	
	m_tCollideRect.left		= (m_tCollideInfo.fX - m_tCollideInfo.fCX / 2.0f);
	m_tCollideRect.top		= (m_tCollideInfo.fY - m_tCollideInfo.fCY / 2.0f);
	m_tCollideRect.right	= (m_tCollideInfo.fX + m_tCollideInfo.fCX / 2.0f);
	m_tCollideRect.bottom	= (m_tCollideInfo.fY + m_tCollideInfo.fCY / 2.0f);
}
