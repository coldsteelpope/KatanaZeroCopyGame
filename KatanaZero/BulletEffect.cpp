#include "pch.h"
#include "BulletEffect.h"
#include "BmpMgr.h"

CBulletEffect::CBulletEffect()
{
}

CBulletEffect::~CBulletEffect()
{
    Release();
}

void CBulletEffect::Initialize()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/effect/bullet/REFLECT_EFFECT.bmp", L"REFLECT_EFFECT");
    m_tInfo.fCX = BULLET_REFLECT_EFFECT_FCX;
    m_tInfo.fCY = BULLET_REFLECT_EFFECT_FCY;
    
    m_tFrame.iFrameStart = 0;
    m_tFrame.iFrameEnd = 4;
    m_tFrame.iMotion = 0;
    m_tFrame.dwTime = GetTickCount();
    m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;

    CObj::Update_Rect();
    CObj::Update_Render_Rect();

}

int CBulletEffect::Update()
{
    if (m_bDead)
    {
        return OBJ_DEAD;
    }

    CObj::Update_Rect();
    CObj::Update_Render_Rect();
    return OBJ_NO_EVENT;
}

void CBulletEffect::Late_Update()
{
    if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
    {
        m_bDead = true;
    }
    CObj::Move_Frame();
}

void CBulletEffect::Render(HDC _hDC)
{
    HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"REFLECT_EFFECT");
    
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

}

void CBulletEffect::Release()
{
}
