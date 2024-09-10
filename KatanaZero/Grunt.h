#pragma once

#include "Obj.h"
class CGrunt : public CObj
{
public:
	CGrunt();
	virtual ~CGrunt();
public:
	// CObj을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;
	
public:
	

private:
	void Jump();
	void Manage_Status();
	void Move();
	void Motion_Change();
	void Update_Collide_Rect();
	void Follow_Frame_Start();

private:
	DWORD dwIdleTime;
	FRAME m_tFollowFrame;
	

};

