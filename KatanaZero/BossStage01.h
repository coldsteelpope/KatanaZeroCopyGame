#pragma once

#include "Scene.h"

class CObj;
class CBossStage01 : public CScene
{
public:
	enum BOSS_STAGE_ENEMY
	{
		GRUNT,
		GANGSTER,
		POMP
	};

public:
	CBossStage01();
	virtual ~CBossStage01();

	// CScene을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;
public:
	BOSS_STAGE_ONE_TYPE Get_Boss_Stage_One_Type() { return m_eBossStageOneType; }
	void Damage_Boss() { --m_iBossHP; }
	
private:
	void Spawn_Enemies();

	void Print_Store_Mementos(HDC _hDC);
	void Store_Mementos();
	

private:
	int m_iBossHP = 3;
	bool m_bDamage = false;
	bool m_bInitBombSituation = false;
	
	bool m_bTimeToSpawn[4] = { 0, };
	DWORD dwGateExSpawnTimes[4] = {
		GetTickCount(),
		GetTickCount(),
		GetTickCount(),
		GetTickCount()
	};

	DWORD dwGateSpawanTime[4] = {
		3000,
		2000,
		3000,
		2000
	};

	BOSS_STAGE_ONE_TYPE m_eBossStageOneType = BOSS_STAGE_ONE_NORMAL;
	CObj* m_pPlayer = nullptr;
};

