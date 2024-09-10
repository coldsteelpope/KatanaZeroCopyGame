#pragma once

#include "Scene.h"
class CObj;
class CBossStage02 : public CScene
{
public:


public:
	CBossStage02();
	virtual ~CBossStage02();

public:
	
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

public:
	void Damage_Boss() { --m_iBossHP; }
	CObj* Get_Player() { return m_pPlayer; }

	void Print_Store_Mementos(HDC _hDC);
	void Store_Mementos();

private:
	void Update_Portal_Rect();

private:
	CObj* m_pPlayer = nullptr;

	int m_iBossHP = 3;
	bool m_bBossHeadAppear = false;
	bool m_bAppearSamurai = false;

	INFO m_tPortalInfo;
	RECT m_tPortalRect;

	FRAME m_tSamuraiFrame;
};

