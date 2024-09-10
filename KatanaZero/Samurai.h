#pragma once

#include "Obj.h"
class CSamurai : public CObj
{
public:
	CSamurai();
	virtual ~CSamurai();

public:


	// CObj을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

};

