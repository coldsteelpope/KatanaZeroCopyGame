#pragma once

#include "Obj.h"
class CGernade : public CObj
{
public:
	CGernade();
	virtual ~CGernade();

public:
	

	// CObj을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

public:
	void Manage_State();

private:
	GERNADE_STATE m_eCurGernadeState = GERNADE_STATE::GENRADE_THROW_STATE;
	DWORD dw_beforeBombTime;
};

