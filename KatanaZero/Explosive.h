#pragma once

#include "Obj.h"
class CExplosive : public CObj
{
public:

public:
	CExplosive();
	virtual ~CExplosive();

public:
	EXPLOSIVE_TYPE Get_Explosive_Type() { return m_eExplosiveType; }
	void Set_Explosive_Type(EXPLOSIVE_TYPE _eExplosiveType) { m_eExplosiveType = _eExplosiveType; }
	

public:
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

private:
	void Move_Item_Arrow_Frame();

private:
	EXPLOSIVE_TYPE m_eExplosiveType;
	FRAME m_tItemArrowFrame;
};

