#pragma once

#include "Obj.h"
class CBulletEffect : public CObj
{
public:
	CBulletEffect();
	virtual ~CBulletEffect();
public:


	// CObj��(��) ���� ��ӵ�
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

};

