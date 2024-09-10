#pragma once

#include "Obj.h"
class CEffect : public CObj
{
public:
	CEffect();
	virtual ~CEffect();

public:
	// CObj��(��) ���� ��ӵ�
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

