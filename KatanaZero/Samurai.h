#pragma once

#include "Obj.h"
class CSamurai : public CObj
{
public:
	CSamurai();
	virtual ~CSamurai();

public:


	// CObj��(��) ���� ��ӵ�
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

};

