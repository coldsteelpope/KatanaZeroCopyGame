#pragma once

#include "Obj.h"
class CGangster : public CObj
{
public:
	CGangster();
	virtual ~CGangster();
public:
	// CObj을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC _hDC) override;
	void Release() override;

public:
	void Set_Shoot_Time(DWORD _dwShootTime) { dwShootTime = _dwShootTime; }
	void Update_Collide_Rect()
	{
		m_tCollideInfo.fX = m_tInfo.fX;
		m_tCollideInfo.fY = m_tInfo.fY;
		m_tCollideInfo.fCX = GANGSTER_IDLE_FCX;
		m_tCollideInfo.fCY = GANGSTER_IDLE_FCY;
		
		m_tCollideRect.left = (long)(m_tCollideInfo.fX - m_tCollideInfo.fCX / 2.0f);
		m_tCollideRect.top = (long)(m_tCollideInfo.fY - m_tCollideInfo.fCX / 2.0f);
		m_tCollideRect.right = (long)(m_tCollideInfo.fX + m_tCollideInfo.fCX / 2.0f);
		m_tCollideRect.bottom = (long)(m_tCollideInfo.fY + m_tCollideInfo.fCX / 2.0f);
	}

private:
	void Jump();
	void Manage_Status();
	void Move();
	void Motion_Change();

	void Follow_Frame_Start();

private:
	DWORD dwIdleTime;
	DWORD dwShootTime;

	bool m_bBloodAppear = false;

	FRAME m_tFollowFrame;
};

