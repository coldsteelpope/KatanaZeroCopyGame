#include "pch.h"
#include "Gernade.h"
#include "BmpMgr.h"
#include "BigExplosion.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"


CGernade::CGernade()
{
}

CGernade::~CGernade()
{
    Release();
}

void CGernade::Initialize()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/gernade/GERNADE.bmp", L"GERNADE");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/headHunter/gernade/GERNADE_CIRCLE.bmp", L"GERNADE_CIRCLE");
    
    m_tInfo.fCX = GERNADE_FCX;
    m_tInfo.fCY = GERNADE_FCY;
    m_fSpeed = 10.5f;

    switch (m_eObjCurDir)
    {
    case OBJ_DIR::LEFT:
    {
        // 180 ~ 270도
        // 210 ~ 240도
        int iRandomDegree = 180 + (rand() % 60);
        m_fAngle = iRandomDegree* (PI / 180.0f);
        break;
    }
    case OBJ_DIR::RIGHT:
    {
        // 270도 ~ 330도
        int iRandomDegree = 180 + (rand() % 60);
        m_fAngle = iRandomDegree * (PI / 180.0f);
        break;
    }
    }
}

int CGernade::Update()
{
    if (m_bDead)
    {
        return OBJ_DEAD;
    }

    CObj::Update_Rect();
    CObj::Update_Render_Rect();


    return OBJ_NO_EVENT;
}

void CGernade::Late_Update()
{
    Manage_State();
}

void CGernade::Render(HDC _hDC)
{
    HDC hCircleDC = CBmpMgr::Get_Instance()->Find_Img(L"GERNADE_CIRCLE");
    HDC hGernadeDC = CBmpMgr::Get_Instance()->Find_Img(L"GERNADE");
    CObj::Update_Rect();
    CObj::Update_Render_Rect();

    GdiTransparentBlt(
        _hDC,
        m_tRenderRect.left - GERNADE_CIRCLE_FCX / 2.0f + 10,
        m_tRenderRect.top - GERNADE_CIRCLE_FCY / 2.0f + 10,
        (int)GERNADE_CIRCLE_FCX,
        (int)GERNADE_CIRCLE_FCY,
        hCircleDC,
        0, 0,
        (int)GERNADE_CIRCLE_FCX,
        (int)GERNADE_CIRCLE_FCY,
        RGB(255, 0, 255)
    );
    
    GdiTransparentBlt(
        _hDC,
        m_tRenderRect.left,
        m_tRenderRect.top,
        (int)m_tInfo.fCX,
        (int)m_tInfo.fCY,
        hGernadeDC,
        0, 0,
        (int)m_tInfo.fCX,
        (int)m_tInfo.fCY,
        RGB(255, 0, 255)
    );
}

void CGernade::Release()
{
}

void CGernade::Manage_State()
{

    switch (m_eCurGernadeState)
    {
    case GERNADE_STATE::GENRADE_THROW_STATE:
    {
        switch (m_eObjCurDir)
        {
        case OBJ_DIR::LEFT:
        {
            m_tInfo.fX = m_tInfo.fX + std::cosf(m_fAngle) * m_fSpeed;
            m_tInfo.fY = m_tInfo.fY + std::sinf(m_fAngle) * m_fSpeed;
            m_fSpeed -= 0.1f;
            break;
        }
        case OBJ_DIR::RIGHT:
        {
            m_tInfo.fX = m_tInfo.fX - std::cosf(m_fAngle) * m_fSpeed;
            m_tInfo.fY = m_tInfo.fY + std::sinf(m_fAngle) * m_fSpeed;
            m_fSpeed -= 0.1f;
            break;
        }
        }

        if (m_fSpeed <= 0.f)
        {
            m_fSpeed = 0.f;
            m_eCurGernadeState = GERNADE_STATE::GERNADE_READY_STATE;
            dw_beforeBombTime = GetTickCount();
        }
        break;
    }
    case GERNADE_STATE::GERNADE_READY_STATE:
    {
        if (dw_beforeBombTime + 1000 < GetTickCount())
        {
            m_eCurGernadeState = GERNADE_STATE::GERNADE_BOMB_STATE;
        }
        break;
    }
    case GERNADE_STATE::GERNADE_BOMB_STATE:
    {
        // 폭발 생성하기 -> 해당 폭발은 Stage01과 Stage02에서 사용할 것
        CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_BIG_EXPLOSION,
            CAbstractFactory<CBigExplosion>::Create(m_tInfo.fX, m_tInfo.fY)
            );
        m_bDead = true;
        break;
    }
    }
}
