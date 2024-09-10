#pragma once

#include "Obj.h"
class CExplosion : public CObj
{
public:
	CExplosion();
	virtual ~CExplosion();

public:
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

private:
	DWORD dwExplosionTime;
};

