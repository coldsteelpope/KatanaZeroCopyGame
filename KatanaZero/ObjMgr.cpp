#include "pch.h"
#include "Obj.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "SceneMgr.h"
#include "ThunderBreathingMgr.h"
#include "Scene.h"
#include "BossStage01.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}

CObjMgr::~CObjMgr()
{
	Release();
}

list<CObj*> CObjMgr::Get_Object_List(OBJ_ID _eID)
{
	return m_ObjList[_eID];
}

void CObjMgr::Add_Object(OBJ_ID _eID, CObj* _pObj)
{
	m_ObjList[_eID].push_back(_pObj);
}

void CObjMgr::Update()
{
	for (size_t i = 0; i < OBJ_ID_END; ++i)
	{
		if (OBJ_ID_ENEMY == (OBJ_ID)(i) || (OBJ_ID_BULLET == (OBJ_ID)(i)) || (OBJ_ID_BOSS == (OBJ_ID)(i)) || (OBJ_ID_LAZER == (OBJ_ID)(i)))
		{
			if (CThunderBreathingMgr::Get_Instance()->Get_Player_Thunder_Breathing_Motion() != PLAYER_THUNDER_BREATHING_MOTION::PLAYER_THUNDER_BREATHING_MOTION_END)
			{
				continue;
			}

		}		

		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end(); )
		{

			int iResult = (*iter)->Update();
			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else if (OBJ_EVENT_REWIND == iResult)
			{
				return;
			}
			else
				++iter;
		}
	}
}

void CObjMgr::Late_Update()
{

	for (size_t i = 0; i < OBJ_ID_END; ++i)
	{
		if (OBJ_ID_ENEMY == (OBJ_ID)(i) || (OBJ_ID_BULLET == (OBJ_ID)(i)) || (OBJ_ID_BOSS == (OBJ_ID)(i)) || (OBJ_ID_LAZER == (OBJ_ID)(i)))
		{
			if (CThunderBreathingMgr::Get_Instance()->Get_Player_Thunder_Breathing_Motion() != PLAYER_THUNDER_BREATHING_MOTION::PLAYER_THUNDER_BREATHING_MOTION_END)
			{
				continue;
			}

		}
		
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end(); ++iter)
		{



			(*iter)->Late_Update();


		}
	}

	if (CThunderBreathingMgr::Get_Instance()->Get_Player_Thunder_Breathing_Motion() == PLAYER_THUNDER_BREATHING_MOTION::PLAYER_THUNDER_BREATHING_MOTION_END)
	{
		// 가장 중요한 Collide
		CollisionMgr::Get_Instance()->Collide_Enemy_Ray_With_Door_Collide(m_ObjList[OBJ_ID::OBJ_ID_ENEMY], m_ObjList[OBJ_ID::OBJ_ID_DOOR]);
		CollisionMgr::Get_Instance()->Collide_Player_With_Enemy_Ray_Rect(m_ObjList[OBJ_ID::OBJ_ID_PLAYER], m_ObjList[OBJ_ID::OBJ_ID_ENEMY]);


		//CollisionMgr::Get_Instance()->Collide_Player_With_Wall_Tile(m_ObjList[OBJ_ID::OBJ_ID_PLAYER], m_ObjList[OBJ_ID::OBJ_ID_TILE]);
		CollisionMgr::Get_Instance()->Collide_Player_With_Enemy_Attack_Rect(m_ObjList[OBJ_ID::OBJ_ID_PLAYER], m_ObjList[OBJ_ID::OBJ_ID_ENEMY]);

		// Player Collision
		CollisionMgr::Get_Instance()->Collide_Player_Attack_Rect_With_Bullet(m_ObjList[OBJ_ID::OBJ_ID_PLAYER], m_ObjList[OBJ_ID::OBJ_ID_BULLET]);
		CollisionMgr::Get_Instance()->Collide_Explosive_With_Oil_Drum(m_ObjList[OBJ_ID::OBJ_ID_EXPLOSIVE_THROW], m_ObjList[OBJ_ID::OBJ_ID_OIL_DRUM]);
		CollisionMgr::Get_Instance()->Collide_Oil_Drum_With_Explosion(m_ObjList[OBJ_ID::OBJ_ID_OIL_DRUM], m_ObjList[OBJ_ID::OBJ_ID_EXPLOSION]);

		CollisionMgr::Get_Instance()->Collide_Player_Attack_Rect_With_Enemy(m_ObjList[OBJ_ID::OBJ_ID_PLAYER], m_ObjList[OBJ_ID::OBJ_ID_ENEMY]);
		CollisionMgr::Get_Instance()->Collide_Enemy_With_Explosion(m_ObjList[OBJ_ID::OBJ_ID_ENEMY], m_ObjList[OBJ_ID::OBJ_ID_EXPLOSION]);
		CollisionMgr::Get_Instance()->Collide_Enemy_Width_Pairing_Bullet(m_ObjList[OBJ_ID::OBJ_ID_ENEMY], m_ObjList[OBJ_ID::OBJ_ID_BULLET]);

		// Tile Collision
		CollisionMgr::Get_Instance()->Collide_Player_With_Wall_Tile(m_ObjList[OBJ_ID::OBJ_ID_PLAYER], m_ObjList[OBJ_ID::OBJ_ID_TILE]);
		CollisionMgr::Get_Instance()->Collide_Gernade_With_Tile(m_ObjList[OBJ_ID::OBJ_ID_GERNADE], m_ObjList[OBJ_ID::OBJ_ID_TILE]);
		CollisionMgr::Get_Instance()->Collide_Boss2_With_Tile(m_ObjList[OBJ_ID::OBJ_ID_BOSS], m_ObjList[OBJ_ID::OBJ_ID_TILE]);

		// pLAYER VS BOSS
		CollisionMgr::Get_Instance()->Collide_Player_Attack_Rect_With_Boss(m_ObjList[OBJ_ID::OBJ_ID_PLAYER], m_ObjList[OBJ_ID::OBJ_ID_BOSS]);

		// Door
		CollisionMgr::Get_Instance()->Collide_Player_With_Door_Collide(m_ObjList[OBJ_ID::OBJ_ID_PLAYER], m_ObjList[OBJ_ID::OBJ_ID_DOOR]);

		CollisionMgr::Get_Instance()->Collide_Player_Collider_With_Bullet(m_ObjList[OBJ_ID::OBJ_ID_PLAYER], m_ObjList[OBJ_ID::OBJ_ID_BULLET]);

		CollisionMgr::Get_Instance()->Collide_Player_Collider_With_Explosion(m_ObjList[OBJ_ID::OBJ_ID_PLAYER], m_ObjList[OBJ_ID::OBJ_ID_EXPLOSION]);
		CollisionMgr::Get_Instance()->Collide_Player_Collider_With_Lazer(m_ObjList[OBJ_ID::OBJ_ID_PLAYER], m_ObjList[OBJ_ID::OBJ_ID_LAZER]);
		CollisionMgr::Get_Instance()->Collide_Player_Collider_With_Boss_Bullet(m_ObjList[OBJ_ID::OBJ_ID_PLAYER], m_ObjList[OBJ_ID::OBJ_ID_BOSS_BULLET]);
		CollisionMgr::Get_Instance()->Collide_Player_Attack_Rect_With_Boss_Bullet(m_ObjList[OBJ_ID::OBJ_ID_PLAYER], m_ObjList[OBJ_ID::OBJ_ID_BOSS_BULLET]);

		CollisionMgr::Get_Instance()->Collide_Player_Collider_With_Explosive(m_ObjList[OBJ_ID::OBJ_ID_PLAYER], m_ObjList[OBJ_ID::OBJ_ID_EXPLOSIVE]);

		CollisionMgr::Get_Instance()->Collide_Boss_Head_Collider_With_Tile(m_ObjList[OBJ_ID::OBJ_ID_BOSS_HEAD], m_ObjList[OBJ_ID::OBJ_ID_TILE]);
		CollisionMgr::Get_Instance()->Collide_Thunder_Breathing_Collider_With_Enemy(m_ObjList[OBJ_ID::OBJ_ID_PLAYER], m_ObjList[OBJ_ID::OBJ_ID_ENEMY]);

		CollisionMgr::Get_Instance()->Collide_Slash_Collider_With_Enemy(m_ObjList[OBJ_ID::OBJ_ID_PLAYER], m_ObjList[OBJ_ID::OBJ_ID_ENEMY]);
	}
	else
	{
		CollisionMgr::Get_Instance()->Collide_Thunder_Breathing_Collider_With_Enemy(m_ObjList[OBJ_ID::OBJ_ID_PLAYER], m_ObjList[OBJ_ID::OBJ_ID_ENEMY]);
	}

}

void CObjMgr::Render(HDC _hDC)
{
	for (size_t i = 0; i < OBJ_ID_END; ++i)
	{
		if ((OBJ_ID)(i) == OBJ_ID::OBJ_ID_ENEMY)
		{
			if (static_cast<CBossStage01*>(CSceneMgr::Get_Instance()->Get_Active_Scene())->Get_Boss_Stage_One_Type() == BOSS_STAGE_ONE_TYPE::BOSS_STAGE_ONE_BOMB)
			{
				continue;
			}
		}

		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end(); ++iter)
		{
			if (i == OBJ_ID::OBJ_ID_TILE)
			{
				continue;
			}

			
			(*iter)->Render(_hDC);
			
		}
	}
}

void CObjMgr::Release()
{
	for (size_t i = 0; i < OBJ_ID_END; ++i)
	{
		if (i == OBJ_ID::OBJ_ID_TILE)
		{
			continue;
		}
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}
}

void CObjMgr::Clear_All_Object_List()
{
	for (size_t i = 0; i < OBJ_ID_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}
}
