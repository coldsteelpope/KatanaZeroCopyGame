#pragma once

#include "Obj.h"
class COilDrum : public CObj
{
public:
	COilDrum();
	virtual ~COilDrum();

public:
	// CObj을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

};

