#pragma once

#include "Obj.h"

class CSmallLazer;
class CBoss : public CObj
{
public:
	CBoss();
	virtual ~CBoss();

public:
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

public:
	void Set_Cur_Boss_Status(BOSS_STATUS _bossStatus) { m_eBossCurStatus = _bossStatus; }
	BOSS_STATUS Get_Cur_Boss_Status() { return m_eBossCurStatus; }
	int Get_Boss_HP() { return m_iBossHp; }
	void Damage() { --m_iBossHp; }
private:
	void Motion_Change();
	void Manage_Status();
	void Set_Target(CObj* _pTarget);
	void Update_Collide_Rect_For_Boss();



private:
	int m_iBossHp = 4;
	int m_iAimLineWidth = 5;

	float m_fAngle;
	bool m_bFindTarget = false;
	bool m_bSearchStart = false;

	DWORD m_dwIDLETime = 0;
	DWORD m_dwAimTime = 0;
	DWORD m_dwShootTime = 0;
	DWORD m_dwDisappearingTime = 0;
	DWORD m_dwAimLineTime = 0;
	
	BOSS_STATUS m_eBossCurStatus = BOSS_STATUS::BOSS_IDLE_LEFT;
	BOSS_STATUS m_eBossPreStatus = BOSS_STATUS::BOSS_STATUS_END;

};

