#pragma once

#include "Obj.h"
class CBlood : public CObj
{
public:
	CBlood();
	virtual ~CBlood();

public:
	

	// CObj��(��) ���� ��ӵ�
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

};

