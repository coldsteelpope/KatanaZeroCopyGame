#pragma once

#include "Obj.h"
class CSkillEffect : public CObj
{


public:
	CSkillEffect();
	virtual ~CSkillEffect();

public:
	// CObj��(��) ���� ��ӵ�
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

};

