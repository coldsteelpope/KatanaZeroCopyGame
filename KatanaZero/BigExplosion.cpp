#include "pch.h"
#include "ObjMgr.h"
#include "BigExplosion.h"
#include "AbstractFactory.h"
#include "Explosion.h"
#include "SoundMgr.h"

CBigExplosion::CBigExplosion()
{
}

CBigExplosion::~CBigExplosion()
{
    Release();
}

void CBigExplosion::Initialize()
{
    CSoundMgr::Get_Instance()->StopSound(EXPLOSION_EFFECT);
    CSoundMgr::Get_Instance()->PlaySound(L"explosion_1.wav", EXPLOSION_EFFECT, 1.f);
}

int CBigExplosion::Update()
{
    if (m_bDead)
    {
        return OBJ_DEAD;
    }

    int offsetX = -35 + (rand() % 75);
    int offsetY = -35 + (rand() % 75);

    CObjMgr::Get_Instance()->Add_Object(
        OBJ_ID::OBJ_ID_EXPLOSION,
        CAbstractFactory<CExplosion>::Create(m_tInfo.fX + offsetX, m_tInfo.fY + offsetY)
    );

    return OBJ_NO_EVENT;
}

void CBigExplosion::Late_Update()
{
    if (iCurrentBombNumber >= iLimitBombNumber)
    {
        m_bDead = true;
        return;
    }
    ++iCurrentBombNumber;
}

void CBigExplosion::Render(HDC _hDC)
{
    
}

void CBigExplosion::Release()
{
}
