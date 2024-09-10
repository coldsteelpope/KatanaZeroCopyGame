#pragma once

#include "Obj.h"
class CLazer : public CObj
{
public:
	CLazer();
	virtual ~CLazer();

public:


	// CObj을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

public:
	void Set_Lazer_Type(LAZER_TYPE _eLazerTYPE) { m_eLazerType = _eLazerTYPE; }

private:
	void Set_Points();
	void Update_Collide_Rect_For_Lazer();
private:
	int m_iCount = 0;
	POINT		m_tPoints[3];
	LAZER_TYPE	m_eLazerType;
};

