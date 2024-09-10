#include "pch.h"
#include "BmpMgr.h"
#include "Door.h"
#include "Camera.h"

CDoor::CDoor()
{
}

CDoor::~CDoor()
{
}

void CDoor::Initialize()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/door/DOOR_LEFT.bmp", L"DOOR", OBJ_DIR::LEFT);
    
    
    m_tInfo.fCX = DOOR_FCX;
    m_tInfo.fCY = DOOR_FCY;
    m_pFrameKey = L"DOOR";
    m_tFrame.iFrameStart = 0;
    m_tFrame.iFrameEnd = 18;
    m_tFrame.iMotion = 0;
    m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
    m_tFrame.dwTime = GetTickCount();
    m_eObjCurDir = OBJ_DIR::LEFT;
}

int CDoor::Update()
{
    if (m_bDead)
    {
        return OBJ_DEAD;
    }

    CObj::Update_Rect();
    CObj::Update_Render_Rect();
    CDoor::Update_Collide_Rect_For_Door();
    return OBJ_NO_EVENT;
}

void CDoor::Late_Update()
{
    //CObj::Move_Frame();
    Manage_Status();
}

void CDoor::Render(HDC _hDC)
{
    HDC hDoorDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey, m_eObjCurDir);

    Vec2 renderCollideLeftTop = CCamera::Get_Instance()->GetRenderPos(Vec2{ (float)m_tCollideRect.left, (float)m_tCollideRect.top });
    Vec2 renderCollideRightBottom = CCamera::Get_Instance()->GetRenderPos(Vec2{ (float)m_tCollideRect.right, (float)m_tCollideRect.bottom });

    //::Rectangle(_hDC, renderCollideLeftTop.fX, renderCollideLeftTop.fY, renderCollideRightBottom.fX, renderCollideRightBottom.fY);


    GdiTransparentBlt(
        _hDC,
        m_tRenderRect.left,
        m_tRenderRect.top,
        (int)m_tInfo.fCX,
        (int)m_tInfo.fCY,
        hDoorDC,
        m_tInfo.fCX * m_tFrame.iFrameStart,
        m_tInfo.fCY * m_tFrame.iMotion,
        (int)m_tInfo.fCX,
        (int)m_tInfo.fCY,
        RGB(255, 0, 255)
    );
}

void CDoor::Release()
{
}

void CDoor::Update_Collide_Rect_For_Door()
{
    m_tCollideInfo.fX = m_tInfo.fX;
    m_tCollideInfo.fY = m_tInfo.fY;
    m_tCollideInfo.fCX = m_tInfo.fCX;
    m_tCollideInfo.fCY = m_tInfo.fCY;

    m_tCollideRect.left = (long)(m_tCollideInfo.fX - m_tCollideInfo.fCX / 2.0f);
    m_tCollideRect.top = (long)(m_tCollideInfo.fY - m_tCollideInfo.fCY / 2.0f);
    m_tCollideRect.right = (long)(m_tCollideInfo.fX + m_tCollideInfo.fCX / 2.0f);
    m_tCollideRect.bottom = (long)(m_tCollideInfo.fY + m_tCollideInfo.fCY / 2.0f);
}

void CDoor::Manage_Status()
{
    switch (m_eDoorType)
    {
    case DOOR_TYPE::CLOSE:
    {
        break;
    }
    case DOOR_TYPE::KICKED:
    {
        m_pFrameKey = L"DOOR";
        CObj::Move_Frame();
        if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
        {
            m_eDoorType = DOOR_TYPE::OPEN;
        }
        break;
    }
    case DOOR_TYPE::OPEN:
    {
        break;
    }
    }
}
