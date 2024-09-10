#include "pch.h"
#include "BossBullet.h"
#include "Obj.h"

CBossBullet::CBossBullet()
{
}

CBossBullet::~CBossBullet()
{
}

void CBossBullet::Initialize()
{
    m_tInfo.fCX = 33.f;
    m_tInfo.fCY = 1.f;
    m_fSpeed = 10.f;
}

int CBossBullet::Update()
{
    if (m_bDead)
    {
        return OBJ_DEAD;
    }
    
    m_tInfo.fX = m_tInfo.fX + m_fSpeed * std::cosf(m_fAngle);
    m_tInfo.fY = m_tInfo.fY + m_fSpeed * std::sinf(m_fAngle);
    
    CObj::Update_Rect();
    CObj::Update_Render_Rect();
    CBossBullet::Update_Collide_Rect_For_Boss_Bullet();

    return OBJ_NO_EVENT;
}

void CBossBullet::Late_Update()
{
    
}

void CBossBullet::Render(HDC _hDC)
{
    CObj::Update_Rect();
    CObj::Update_Render_Rect();
    CBossBullet::Update_Collide_Rect_For_Boss_Bullet();

    //Vec2 renderCollideRectTopLeft = CCamera::Get_Instance()->GetRenderPos(Vec2{ (float)m_tCollideRect.left, (float)m_tCollideRect.top });
    //Vec2 renderCollideRectRightBottom = CCamera::Get_Instance()->GetRenderPos(Vec2{ (float)m_tCollideRect.right, (float)m_tCollideRect.bottom });
    //::Rectangle(_hDC, renderCollideRectTopLeft.fX, renderCollideRectTopLeft.fY, renderCollideRectRightBottom.fX, renderCollideRectRightBottom.fY);


    HPEN bulletPen = ::CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
    HPEN oldPen = (HPEN)::SelectObject(_hDC, bulletPen);

    HBRUSH bulletBrush = ::CreateSolidBrush(RGB(255, 255, 0));
    HBRUSH oldBrush = (HBRUSH)::SelectObject(_hDC, bulletBrush);

    RECT rect = { m_tRenderRect.left, m_tRenderRect.top, m_tRenderRect.right, m_tRenderRect.bottom };
    POINT center = { m_tInfo.fX, m_tInfo.fY };
    
    Vec2 renderCenter = CCamera::Get_Instance()->GetRenderPos(Vec2{ (float)center.x, (float)center.y });
    POINT renderCenterPoint = { (LONG)renderCenter.fX, (LONG)renderCenter.fY };
    
    POINT points[4];
    RotateRect(&rect, renderCenterPoint, m_fAngle, points);
    Polygon(_hDC, points, 4);

    ::SelectObject(_hDC, oldBrush);
    ::DeleteObject(bulletBrush);
    ::SelectObject(_hDC, oldPen);
    ::DeleteObject(bulletPen);
}

void CBossBullet::Release()
{
    
}

void CBossBullet::Update_Collide_Rect_For_Boss_Bullet()
{
    m_tCollideInfo.fX = m_tInfo.fX;
    m_tCollideInfo.fY = m_tInfo.fY;
    m_tCollideInfo.fCX = m_tInfo.fCX / 2.0f;
    m_tCollideInfo.fCY = m_tInfo.fCX / 2.0f;

    m_tCollideRect.left = (long)(m_tCollideInfo.fX - m_tCollideInfo.fCX / 2.0f);
    m_tCollideRect.top = (long)(m_tCollideInfo.fY - m_tCollideInfo.fCY / 2.0f);
    m_tCollideRect.right = (long)(m_tCollideInfo.fX + m_tCollideInfo.fCX / 2.0f);
    m_tCollideRect.bottom = (long)(m_tCollideInfo.fY + m_tCollideInfo.fCY / 2.0f);

}


POINT CBossBullet::RotatePoint(POINT p, POINT center, float angle)
{
    float s = sin(angle);
    float c = cos(angle);

    p.x -= center.x;
    p.y -= center.y;

    float xNew = p.x * c - p.y * s;
    float yNew = p.x * s + p.y * c;

    p.x = xNew + center.x;
    p.y = yNew + center.y;

    

    return p;
}

void CBossBullet::RotateRect(RECT* rect, POINT center, float angle, POINT* points)
{
    POINT corners[4] = {
        { (float)rect->left, (float)rect->top },
        { (float)rect->right, (float)rect->top },
        { (float)rect->right, (float)rect->bottom },
        { (float)rect->left, (float)rect->bottom }
    };

    for (int i = 0; i < 4; ++i)
    {
        POINT rotated = RotatePoint(corners[i], center, angle);
        points[i].x = (LONG)rotated.x;
        points[i].y = (LONG)rotated.y;
    }
}