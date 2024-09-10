#pragma once

#include "Obj.h"
class CBossHead : public CObj
{
public:
	CBossHead();
	virtual ~CBossHead();

public:


	// CObj을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;


public:
	void Motion_Change();
	void Move_Frames();

public:
	void Update_Collide_Rect_Using_Boss_Head_Info();

private:
	BOSS_HEAD_STATUS m_eBossHeadCurStatus = BOSS_HEAD_STATUS::BOSS_HEAD_STATE_END;
	BOSS_HEAD_STATUS m_eBossHeadPreStatus = BOSS_HEAD_STATUS::BOSS_HEAD_STATE_END;

	float m_fTheta = 45 * (PI / 180.0f);
	float m_fSpeed = 5.0f;
	float m_fJumpTime = 0.f;
	float m_fStopIFramtStart = -1.f;
};

