#pragma once

#include "Obj.h"
class CBattery : public CObj
{
public:
	CBattery();
	virtual ~CBattery();

public:
	// CObj��(��) ���� ��ӵ�
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

};

