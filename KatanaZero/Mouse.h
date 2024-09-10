#pragma once

#include "Obj.h"
class CMouse : public CObj
{
public:
	CMouse();
	virtual ~CMouse();

public:
	// CObj을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

public:
	POINT Get_Mouse_Pos() { return m_tMousePos; }

private:
	POINT m_tMousePos;
};

