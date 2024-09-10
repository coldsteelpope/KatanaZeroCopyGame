#pragma once

#include "Scene.h"

class CObj;
class CStage03 : public CScene
{
public:
	CStage03();
	virtual ~CStage03();
public:
	// CScene을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;


private:
	void Print_Store_Mementos(HDC _hDC);
	void Store_Mementos();

private:
	CObj* m_pPlayer;

	float m_fTestX = 2.5f;
	float m_fTestY = 2.5f;
	DWORD dwTime = GetTickCount();

};

