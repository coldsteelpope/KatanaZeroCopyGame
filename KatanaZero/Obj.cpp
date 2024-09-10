#include "pch.h"
#include "Obj.h"
#include "ThunderBreathingMgr.h"
#include "TimeSlowMgr.h"

CObj::CObj() : m_bDead(false), m_dwAfterImageTime(GetTickCount())
{
	ZeroMemory(&m_tRenderRect, sizeof(RECT));
	ZeroMemory(&m_tRayRect, sizeof(RECT));
	ZeroMemory(&m_tAttackAreaRect, sizeof(RECT));
}

CObj::~CObj()
{
}

void CObj::Update_Rect()
{
	m_tRect.left	= (long)(m_tInfo.fX - m_tInfo.fCX / 2.0f);
	m_tRect.top		= (long)(m_tInfo.fY - m_tInfo.fCY / 2.0f);
	m_tRect.right	= (long)(m_tInfo.fX + m_tInfo.fCX / 2.0f);
	m_tRect.bottom	= (long)(m_tInfo.fY + m_tInfo.fCY / 2.0f);
}


void CObj::Update_Render_Rect()
{
	Vec2 vRenderPos = CCamera::Get_Instance()->GetRenderPos(Vec2{ m_tInfo.fX, m_tInfo.fY });
	m_tRenderRect.left = (vRenderPos.fX - m_tInfo.fCX / 2.0f);
	m_tRenderRect.top = (vRenderPos.fY - m_tInfo.fCY / 2.0f);
	m_tRenderRect.right = (vRenderPos.fX + m_tInfo.fCX / 2.0f);
	m_tRenderRect.bottom = (vRenderPos.fY + m_tInfo.fCY / 2.0f);
}

void CObj::Update_Collide_Rect()
{
	m_tCollideInfo.fX = m_tInfo.fX;
	m_tCollideInfo.fY = m_tInfo.fY;
	m_tCollideInfo.fCX = PLAYER_IDLE_FCX;
	m_tCollideInfo.fCY = PLAYER_IDLE_FCY;

	m_tCollideRect.left = (m_tInfo.fX - PLAYER_IDLE_FCX / 2.0f);
	m_tCollideRect.top = (m_tInfo.fY - PLAYER_IDLE_FCY / 2.0f);
	m_tCollideRect.right = (m_tInfo.fX + PLAYER_IDLE_FCX / 2.0f);
	m_tCollideRect.bottom = (m_tInfo.fY + PLAYER_IDLE_FCY / 2.0f);
}





void CObj::Move_Frame()
{
	if (m_eObjCurStatus == OBJ_STATUS::THUNDER_BREATHING_PROCESS)
	{
		Store_After_Image(
			m_tInfo.fCX,
			m_tInfo.fCY,
			m_tFrame.iFrameStart,
			m_tFrame.iMotion,
			m_pFrameKey
		);
		return;
	}
	else
	{
		if (m_tFrame.dwTime + (m_tFrame.dwSpeed * CTimeSlowMgr::Get_Instance()->Get_Ratio()) < GetTickCount())
		{
			++m_tFrame.iFrameStart;
			if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			{
				m_tFrame.iFrameStart = 0;
			}
			m_tFrame.dwTime = GetTickCount();
		}

		Store_After_Image(
			m_tInfo.fCX,
			m_tInfo.fCY,
			m_tFrame.iFrameStart,
			m_tFrame.iMotion,
			m_pFrameKey
		);
	}

	


}

void CObj::Move_Reverse_Frame(int _initFrame)
{

	if (m_tFrame.dwTime + (m_tFrame.dwSpeed * CTimeSlowMgr::Get_Instance()->Get_Ratio()) < GetTickCount())
	{
		--m_tFrame.iFrameStart;
		if (m_tFrame.iFrameStart < m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameStart = _initFrame;
		}
		m_tFrame.dwTime = GetTickCount();
	}
}

void CObj::Update_Player_Attack_Rect()
{

}

void CObj::Update_Collide_Rect_Using_Info()
{
	m_tCollideRect.left = long(m_tCollideInfo.fX - m_tCollideInfo.fCX / 2.0f);
	m_tCollideRect.top = long(m_tCollideInfo.fY - m_tCollideInfo.fCY / 2.0f);
	m_tCollideRect.right = long(m_tCollideInfo.fX + m_tCollideInfo.fCX / 2.0f);
	m_tCollideRect.bottom = long(m_tCollideInfo.fY + m_tCollideInfo.fCY / 2.0f);

}

void CObj::Update_Attack_Rect()
{
	switch (m_eObjCurDir)
	{
	case OBJ_DIR::RIGHT:
	{
		m_tAttackAreaRect.left = long(m_tInfo.fX);
		m_tAttackAreaRect.top = long(m_tInfo.fY - m_fAttackAreaHeight);
		m_tAttackAreaRect.right = long(m_tInfo.fX + 2 * m_fAttackRadius);
		m_tAttackAreaRect.bottom = long(m_tInfo.fY + m_fAttackAreaHeight);
		break;
	}
	case OBJ_DIR::LEFT:
	{
		m_tAttackAreaRect.left = long(m_tInfo.fX - 2 * m_fAttackRadius);
		m_tAttackAreaRect.top = long(m_tInfo.fY - m_fAttackAreaHeight);
		m_tAttackAreaRect.right = long(m_tInfo.fX);
		m_tAttackAreaRect.bottom = long(m_tInfo.fY + m_fAttackAreaHeight);
		break;
	}
	}

	Vec2 vRenderLeftTop = CCamera::Get_Instance()->GetRenderPos(Vec2{ (float)m_tAttackAreaRect.left, (float)m_tAttackAreaRect.top });
	Vec2 vRenderRightBottom = CCamera::Get_Instance()->GetRenderPos(Vec2{ (float)m_tAttackAreaRect.right, (float)m_tAttackAreaRect.bottom });

	m_tAttackAreaRenderRect.left = (long)vRenderLeftTop.fX;
	m_tAttackAreaRenderRect.top = (long)vRenderLeftTop.fY;
	m_tAttackAreaRenderRect.right = (long)vRenderRightBottom.fX;
	m_tAttackAreaRenderRect.bottom = (long)vRenderRightBottom.fY;
}



void CObj::Update_Ray_Rect()
{
	switch (m_eObjCurDir)
	{
	case OBJ_DIR::RIGHT:
	{
		m_tRayRect.left = long(m_tInfo.fX);
		m_tRayRect.top = long(m_tInfo.fY - 1.f);
		m_tRayRect.right = long(m_tInfo.fX + 2 * m_fRayRadius);
		m_tRayRect.bottom = long(m_tInfo.fY + 1.f);

		break;
	}
	case OBJ_DIR::LEFT:
	{
		m_tRayRect.left = long(m_tInfo.fX - 2 * m_fRayRadius);
		m_tRayRect.top = long(m_tInfo.fY - 1.f);
		m_tRayRect.right = long(m_tInfo.fX);
		m_tRayRect.bottom = long(m_tInfo.fY + 1.f);
		break;
	}
	}

	Vec2 vRenderLeftTop = CCamera::Get_Instance()->GetRenderPos(Vec2{ (float)m_tRayRect.left, (float)m_tRayRect.top });
	Vec2 vRenderRightBottom = CCamera::Get_Instance()->GetRenderPos(Vec2{ (float)m_tRayRect.right, (float)m_tRayRect.bottom });
	
	m_tRayRenderRect.left	= (long)vRenderLeftTop.fX;
	m_tRayRenderRect.top	= (long)vRenderLeftTop.fY;
	m_tRayRenderRect.right	= (long)vRenderRightBottom.fX;
	m_tRayRenderRect.bottom = (long)vRenderRightBottom.fY;
}

void CObj::Store_After_Image(
	float _fCX,
	float _fCY,
	int _iFrameStart,
	int _iMotion,
	TCHAR* _pFrameKey
)
{
	Vec2 vRenderPos = CCamera::Get_Instance()->GetRenderPos(Vec2{ m_tInfo.fX, m_tInfo.fY });



	switch (m_eObjCurStatus)
	{
	case OBJ_STATUS::IDLE:
	{
		break;
	}
	case OBJ_STATUS::SLASH:
	{
		if (m_dwAfterImageTime + 70 < GetTickCount())
		{
			AFTER_IMAGE_INFO tAfterImageInfo;
			tAfterImageInfo.fX = vRenderPos.fX;
			tAfterImageInfo.fY = vRenderPos.fY;
			tAfterImageInfo.fCX = _fCX;
			tAfterImageInfo.fCY = _fCY;
			tAfterImageInfo.iFrameStart = _iFrameStart;
			tAfterImageInfo.iMotion = _iMotion;
			tAfterImageInfo.iLimitNumber = 0;
			tAfterImageInfo.m_pFrameKey = _pFrameKey;
			tAfterImageInfo.m_eObjDir = m_eObjCurDir;

			m_pAfterImageList.push_back(tAfterImageInfo);
			m_dwAfterImageTime = GetTickCount();
		}

		break;
	}
	case OBJ_STATUS::THUNDER_BREATHING_PROCESS:
	{
		if (m_dwAfterImageTime + 70 < GetTickCount())
		{
			AFTER_IMAGE_INFO tAfterImageInfo;
			tAfterImageInfo.fX = vRenderPos.fX;
			tAfterImageInfo.fY = vRenderPos.fY;
			tAfterImageInfo.fCX = _fCX;
			tAfterImageInfo.fCY = _fCY;
			tAfterImageInfo.iFrameStart = _iFrameStart;
			tAfterImageInfo.iMotion = _iMotion;
			tAfterImageInfo.iLimitNumber = 0;
			tAfterImageInfo.m_pFrameKey = _pFrameKey;
			tAfterImageInfo.m_eObjDir = m_eObjCurDir;

			m_pAfterImageList.push_back(tAfterImageInfo);
			m_dwAfterImageTime = GetTickCount();
		}
		break;
	}

	default:
	{
		if (m_dwAfterImageTime + 70 < GetTickCount())
		{
			AFTER_IMAGE_INFO tAfterImageInfo;
			tAfterImageInfo.fX = vRenderPos.fX;
			tAfterImageInfo.fY = vRenderPos.fY;
			tAfterImageInfo.fCX = _fCX;
			tAfterImageInfo.fCY = _fCY;
			tAfterImageInfo.iFrameStart = _iFrameStart;
			tAfterImageInfo.iMotion = _iMotion;
			tAfterImageInfo.iLimitNumber = 0;
			tAfterImageInfo.m_pFrameKey = _pFrameKey;
			tAfterImageInfo.m_eObjDir = m_eObjCurDir;

			m_pAfterImageList.push_back(tAfterImageInfo);
			m_dwAfterImageTime = GetTickCount();
		}
		break;
	}
	}
}

void CObj::Check_Delete_After_Image()
{
	for (auto& iter = m_pAfterImageList.begin(); iter != m_pAfterImageList.end();)
	{
		bool bDeleteInfo = false;
		AFTER_IMAGE_INFO tAfterImageInfo = (*iter);
		
		if (CThunderBreathingMgr::Get_Instance()->Get_ThunderBreathing_Mode())
		{
			if (tAfterImageInfo.iLimitNumber > 50)
			{
				bDeleteInfo = true;
			}
		}
		else
		{
			if (tAfterImageInfo.iLimitNumber > 15)
			{
				bDeleteInfo = true;
			}
		}
	

		if (bDeleteInfo)
		{
			iter = m_pAfterImageList.erase(iter);
		}
		else
		{
			(*iter).iLimitNumber += 1;
			++iter;
		}
	}
}

void CObj::Clear_All_After_Images()
{
	m_pAfterImageList.clear();
}
