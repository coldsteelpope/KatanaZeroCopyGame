#pragma once
class CObj;
class CollisionMgr
{
private:
	CollisionMgr();
	~CollisionMgr();

public:
	// 벽력일섬 관련 함수도 추가해야 함
	
	void Collide_Slash_Collider_With_Enemy(list<CObj*> _pPlayerList, list<CObj*> _pEnemyList);

	void Collide_Thunder_Breathing_Collider_With_Enemy(list<CObj*> _pPlayerList, list<CObj*> _pEnemyList);
	void Collide_Boss_Head_Collider_With_Tile(list<CObj*> _pBossHeadList, list<CObj*> _pTileList);
	void Collide_Player_Collider_With_Explosive(list<CObj*> _pPlayerList, list<CObj*> _pExplosiveList);
	void Collide_Boss_With_Paired_Boss_Bullet(list<CObj*> _pBossList, list<CObj*> _pBossBullet);
	void Collide_Player_Attack_Rect_With_Boss_Bullet(list<CObj*> _pPlayerList, list<CObj*> _pBossBulletList);
	void Collide_Player_Collider_With_Boss_Bullet(list<CObj*> _pPlayerList, list<CObj*> _pBossBulletList);
	void Collide_Player_Collider_With_Lazer(list<CObj*> _pPlayerList, list<CObj*> _pLazer);
	void Collide_Player_Collider_With_Explosion(list<CObj*> _pPlayerList, list<CObj*> _pExplosionList);

	void Collide_Player_Collider_With_Enemy_On_Thunder_Breathing(list<CObj*> _pPlayerList, list<CObj*> _pEnemyList);
	void Collide_Player_Collider_With_Enemy_Attack_Area(list<CObj*> _pPlayerList, list<CObj*> _pEnemyList);
	void Collide_Player_Collider_With_Bullet(list<CObj*> _pPlayerList, list<CObj*> _pBulletList);

	void Collide_Boss2_With_Tile(list<CObj*> _pBossList, list<CObj*> _pTileList);
	void Collide_Gernade_With_Tile(list<CObj*> _pGernadeList, list<CObj*> _pTileList);

	void Collide_Enemy_Ray_With_Door_Collide(list<CObj*> _pEnemyList, list<CObj*> _pDoorList);
	void Collide_Player_Attack_Rect_With_Boss(list<CObj*> _pPlayerList, list<CObj*> _pBossList);
	void Collide_Player_With_Door_Collide(list<CObj*> _pPlayerList, list<CObj*> _pDoorList);
	void Collide_Player_With_Climb_Tile(list<CObj*> _pPlayerList, list<CObj*> _pTileList);
	void Collide_Enemy_Width_Pairing_Bullet(list<CObj*> _pEnemyList, list<CObj*> _pBulletList);
	void Collide_Enemy_With_Explosion(list<CObj*> _pEnemyList, list<CObj*> _pExplosionList);
	void Collide_Player_Attack_Rect_With_Enemy(list<CObj*> _pPlayerList, list<CObj*> _pEnemyList);
	void Collide_Oil_Drum_With_Explosion(list<CObj*> _pOilDrumList, list<CObj*> _pExplosiveList);
	void Collide_Explosive_With_Oil_Drum(list<CObj*> _pExplosiveList, list<CObj*> _pOilDrumList);
	void Collide_Player_Attack_Rect_With_Bullet(list<CObj*> _pPlayerList, list<CObj*> _pBulletList);
	void Collide_Player_With_Enemy_Attack_Rect(list<CObj*> _pPlayerList, list<CObj*> _pEnemyList);
	void Collide_Player_With_Enemy_Ray_Rect(list<CObj*> _pPlayerList, list<CObj*> _pEnemyList);
	void Collide_Player_With_Wall_Tile(list<CObj*> _pPlayerList, list<CObj*> _pWallTileList);


	bool Check_Rect_Collision(CObj* _pDst, CObj* _pSrc, RECT* _tRc);
	bool Check_Rect(CObj* _pDst, CObj* _pSrc, float* pX, float* pY);
	bool Check_Rect_With_Dst_Collider(CObj* _pDst, CObj* _pSrc, float* pX, float* pY);

public:
	static CollisionMgr* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CollisionMgr;
		}
		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static CollisionMgr* m_pInstance;

};
