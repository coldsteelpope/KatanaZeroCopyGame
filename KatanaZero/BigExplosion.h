#pragma once

#include "Obj.h"

class CBigExplosion : public CObj
{
public:
	CBigExplosion();
	virtual ~CBigExplosion();

public:


	// CObj��(��) ���� ��ӵ�
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

private:
	int iCurrentBombNumber = 0;
	int iLimitBombNumber = 10;
	DWORD m_dwLimitTime = 500;
	DWORD m_dwBombTime = GetTickCount();
};

