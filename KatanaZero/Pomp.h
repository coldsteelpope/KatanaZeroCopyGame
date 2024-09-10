#pragma once

#include "Obj.h"
class CPomp : public CObj
{
public:
	CPomp();
	virtual ~CPomp();

public:


	// CObj을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

private:
	void Jump();
	void Manage_Status();
	void Move();
	void Motion_Change();
	void Follow_Frame_Start();

private:
	DWORD dwIdleTime;
	FRAME m_tFollowFrame;
};

