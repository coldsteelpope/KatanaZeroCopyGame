#pragma once

#include "Obj.h"
class CSmoke : public CObj
{
public:
	CSmoke();
	virtual ~CSmoke();

public:
	// CObj��(��) ���� ��ӵ�
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

};

