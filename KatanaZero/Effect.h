#pragma once

#include "Obj.h"
class CEffect : public CObj
{
public:
	CEffect();
	virtual ~CEffect();

public:
	// CObj을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

public:
	void Set_Done(bool _bDone) { m_bDone = _bDone; }

private:
	bool m_bDone;
	POINT m_tPoint[3];
};

