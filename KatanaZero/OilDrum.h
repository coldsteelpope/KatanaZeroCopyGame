#pragma once

#include "Obj.h"
class COilDrum : public CObj
{
public:
	COilDrum();
	virtual ~COilDrum();

public:
	// CObj��(��) ���� ��ӵ�
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

};

