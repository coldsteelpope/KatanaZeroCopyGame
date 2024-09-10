#pragma once

#include "Obj.h"
class CHitEffect : public CObj
{
public:
	CHitEffect();
	virtual ~CHitEffect();

public:
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

};

