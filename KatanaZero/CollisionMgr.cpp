#include "pch.h"
#include "Obj.h"
#include "CollisionMgr.h"
#include "Gangster.h"
#include "Bullet.h"
#include "ObjMgr.h"
#include "Explosion.h"
#include "Tile.h"
#include "AbstractFactory.h"
#include "Bullet.h"
#include "TileMgr.h"
#include "HighlightMgr.h"
#include "Boss.h"
#include "Blood.h"
#include "Door.h"
#include "MouseMgr.h"
#include "Boss2.h"
#include "BulletEffect.h"
#include "SceneMgr.h"
#include "BossStage01.h"
#include "BossStage02.h"
#include "BigExplosion.h"
#include "SoundMgr.h"
#include "KeyMgr.h"
#include "Player.h"
#include "HighlightMgr.h"
#include "BossHead.h"
#include "AttackMgr.h"
#include "ThunderBreathingMgr.h"
#include "LineMgr.h"
#include "ComboMgr.h"

CollisionMgr* CollisionMgr::m_pInstance = nullptr;

CollisionMgr::CollisionMgr()
{
}

CollisionMgr::~CollisionMgr()
{
	
}

void CollisionMgr::Collide_Slash_Collider_With_Enemy(list<CObj*> _pPlayerList, list<CObj*> _pEnemyList)
{
	for (auto pPlayer : _pPlayerList)
	{
		for (auto pEnemy : _pEnemyList)
		{
			if (pPlayer->Get_Obj_Cur_Status() == OBJ_STATUS::SLASH)
			{
				RECT temp;
				RECT tPlayerCollider = pPlayer->Get_Collide_Rect();
				RECT tEnemyCollider = pEnemy->Get_Collide_Rect();

				if (IntersectRect(&temp, &tPlayerCollider, &tEnemyCollider))
				{
					pEnemy->Set_Thunder_Breathing_Death();
				}
			}
		}
	}
}

void CollisionMgr::Collide_Thunder_Breathing_Collider_With_Enemy(list<CObj*> _pPlayerList, list<CObj*> _pEnemyList)
{
	for (auto pPlayer : _pPlayerList)
	{
		for (auto pEnemy : _pEnemyList)
		{
			if (pPlayer->Get_Obj_Cur_Status() == OBJ_STATUS::THUNDER_BREATHING_PROCESS)
			{
				RECT temp;
				RECT tPlayerCollider = pPlayer->Get_Collide_Rect();
				RECT tEnemyCollider = pEnemy->Get_Collide_Rect();
				
				if (IntersectRect(&temp, &tPlayerCollider, &tEnemyCollider))
				{
					pEnemy->Set_Thunder_Breathing_Death();
				}
			}
		}
	}
}

void CollisionMgr::Collide_Boss_Head_Collider_With_Tile(list<CObj*> _pBossHeadList, list<CObj*> _pTileList)
{
	float fX(0.f), fY(0.f);
	for (auto pBossHead : _pBossHeadList)
	{
		for (auto pTile : _pTileList)
		{
			if (Check_Rect_With_Dst_Collider(pBossHead, pTile, &fX, &fY))
			{
				if (static_cast<CTile*>(pTile)->Get_Option() == TILE_TYPE::CLIMB_WALL_TILE)
				{
					if (pBossHead->Get_Collide_Info().fX < pTile->Get_Info().fX)
					{
						INFO tBossHeadInfo = pBossHead->Get_Info();
						RECT tBossHeadRect = pBossHead->Get_Rect();
						RECT tBossHeadRenderRect = pBossHead->Get_Render_Rect();
						INFO tBossHeadCollideInfo = pBossHead->Get_Collide_Info();
						RECT tBossHeadCollideRect = pBossHead->Get_Collide_Rect();

						pBossHead->Set_Position(tBossHeadInfo.fX - fX, tBossHeadInfo.fY);
						pBossHead->Set_Rect(RECT{
							(LONG)(tBossHeadRect.left - fX),
							tBossHeadRect.top,
							(LONG)(tBossHeadRect.right - fX),
							tBossHeadRect.bottom
							});
						pBossHead->Set_RenderRect(RECT{
							(LONG)(tBossHeadRenderRect.left - fX),
							tBossHeadRenderRect.top,
							(LONG)(tBossHeadRenderRect.right - fX),
							tBossHeadRenderRect.bottom
							});

						pBossHead->Set_Collide_Pos(tBossHeadCollideInfo.fX - fX, tBossHeadCollideInfo.fY);
						pBossHead->Set_Collide_Rect(
							RECT{
								(LONG)(tBossHeadCollideRect.left - fX),
								tBossHeadCollideRect.top,
								(LONG)(tBossHeadCollideRect.right - fX),
								tBossHeadCollideRect.bottom
							}
						);

					}
					else
					{
						INFO tBossHeadInfo = pBossHead->Get_Info();
						RECT tBossHeadRect = pBossHead->Get_Rect();
						RECT tBossHeadRenderRect = pBossHead->Get_Render_Rect();
						INFO tBossHeadCollideInfo = pBossHead->Get_Collide_Info();
						RECT tBossHeadCollideRect = pBossHead->Get_Collide_Rect();

						pBossHead->Set_Position(tBossHeadInfo.fX + fX, tBossHeadInfo.fY);
						pBossHead->Set_Rect(RECT{
							(LONG)(tBossHeadRect.left + fX),
							tBossHeadRect.top,
							(LONG)(tBossHeadRect.right + fX),
							tBossHeadRect.bottom
							});
						pBossHead->Set_RenderRect(RECT{
							(LONG)(tBossHeadRenderRect.left + fX),
							tBossHeadRenderRect.top,
							(LONG)(tBossHeadRenderRect.right + fX),
							tBossHeadRenderRect.bottom
							});

						pBossHead->Set_Collide_Pos(tBossHeadCollideInfo.fX + fX, tBossHeadCollideInfo.fY);
						pBossHead->Set_Collide_Rect(
							RECT{
								(LONG)(tBossHeadCollideRect.left + fX),
								tBossHeadCollideRect.top,
								(LONG)(tBossHeadCollideRect.right + fX),
								tBossHeadCollideRect.bottom
							}
						);
					}
				}
			}
		}
	}
}

void CollisionMgr::Collide_Player_Collider_With_Explosive(list<CObj*> _pPlayerList, list<CObj*> _pExplosiveList)
{
	for (auto pPlayer : _pPlayerList)
	{
		for (auto pExplosive : _pExplosiveList)
		{
			RECT tIntersectedRect;
			RECT tplayerCollider = pPlayer->Get_Collide_Rect();
			RECT tExplosiveRect = pExplosive->Get_Rect();

			if (IntersectRect(&tIntersectedRect, &tplayerCollider, &tExplosiveRect))
			{
				if (CKeyMgr::Get_Instance()->Key_Down('F'))
				{
					static_cast<CPlayer*>(pPlayer)->Set_Inventory(ITEM_TYPE::ITEM_EXPLOSIVE);
					pExplosive->Set_Dead(true);
				}
			}
		}
	}
}

void CollisionMgr::Collide_Boss_With_Paired_Boss_Bullet(list<CObj*> _pBossList, list<CObj*> _pBossBullet)
{
	

}

// 플레이어 패링
void CollisionMgr::Collide_Player_Attack_Rect_With_Boss_Bullet(list<CObj*> _pPlayerList, list<CObj*> _pBossBulletList)
{
	for (auto pPlayer : _pPlayerList)
	{
		for (auto pBossBullet : _pBossBulletList)
		{
			RECT tIntersectedRect;
			RECT tPlayerAttackArea = pPlayer->Get_Attack_Area_Rect();
			RECT tBossBulletCollider = pBossBullet->Get_Collide_Rect();
			
			if (IntersectRect(&tIntersectedRect, &tPlayerAttackArea, &tBossBulletCollider))
			{
				pBossBullet->Set_Speed(-pBossBullet->Get_Speed());
				//int a = 3;
			}
		}
	}
}


void CollisionMgr::Collide_Player_Collider_With_Boss_Bullet(list<CObj*> _pPlayerList, list<CObj*> _pBossBulletList)
{
	for (auto pPlayer : _pPlayerList)
	{
		for (auto pBossBullet : _pBossBulletList)
		{
			RECT tIntersectedRect;
			RECT tPlayerCollider = pPlayer->Get_Collide_Rect();
			RECT tBossBulletCollider = pBossBullet->Get_Collide_Rect();

			if (IntersectRect(&tIntersectedRect, &tPlayerCollider, &tBossBulletCollider))
			{
				if 
				(
					pPlayer->Get_Obj_Cur_Status() != OBJ_STATUS::ROLL 
					&& pPlayer->Get_Obj_Cur_Status() != OBJ_STATUS::THUNDER_BREATHING_PROCESS 
					&& pPlayer->Get_Obj_Cur_Status() != OBJ_STATUS::THUNDER_BREATHING
				)
				{

					if (static_cast<CPlayer*>(pPlayer)->Get_No_Death())
					{
						break;
					}

					if (CThunderBreathingMgr::Get_Instance()->Get_Player_Thunder_Breathing_Motion() != PLAYER_THUNDER_BREATHING_MOTION_END)
					{
						break;
					}

					CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
					CSoundMgr::Get_Instance()->PlaySound(L"dragon_death.wav", PLAYER_EFFECT, 1.f);

					pPlayer->Set_Obj_Cur_Status(OBJ_STATUS::LAY_DOWN_START);
					pBossBullet->Set_Dead(true);
				}
			}
		}
	}
}

void CollisionMgr::Collide_Player_Collider_With_Lazer(list<CObj*> _pPlayerList, list<CObj*> _pLazer)
{
	for (auto pPlayer : _pPlayerList)
	{
		for (auto pLazer : _pLazer)
		{
			RECT tIntersectedRect;
			RECT tPlayerCollider = pPlayer->Get_Collide_Rect();
			RECT tLazerCollider = pLazer->Get_Collide_Rect();
			if (IntersectRect(&tIntersectedRect, &tPlayerCollider, &tLazerCollider))
			{
				if (
					pPlayer->Get_Obj_Cur_Status() != OBJ_STATUS::ROLL 
					&& pPlayer->Get_Obj_Cur_Status() != OBJ_STATUS::THUNDER_BREATHING_PROCESS 
					&& pPlayer->Get_Obj_Cur_Status() != OBJ_STATUS::THUNDER_BREATHING
				)
				{
					if (static_cast<CPlayer*>(pPlayer)->Get_No_Death())
					{
						break;
					}

					if (CThunderBreathingMgr::Get_Instance()->Get_Player_Thunder_Breathing_Motion() != PLAYER_THUNDER_BREATHING_MOTION_END)
					{
						break;
					}

					CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
					CSoundMgr::Get_Instance()->PlaySound(L"dragon_death.wav", PLAYER_EFFECT, 1.f);

					pPlayer->Set_Obj_Cur_Status(OBJ_STATUS::LAY_DOWN_START);
				}
			}
		}
	}
}

void CollisionMgr::Collide_Player_Collider_With_Explosion(list<CObj*> _pPlayerList, list<CObj*> _pExplosionList)
{
	for (auto pPlayer : _pPlayerList)
	{
		for (auto pExplosion : _pExplosionList)
		{
			RECT tIntersectedRect;
			RECT tPlayerCollider = pPlayer->Get_Collide_Rect();
			RECT tExplosionRect = pExplosion->Get_Rect();
			if (IntersectRect(&tIntersectedRect, &tPlayerCollider, &tExplosionRect))
			{
				switch (CSceneMgr::Get_Instance()->Get_Cur_Scene_ID())
				{
				case SCENE_ID::SC_BOSS_01:
				{
					break;
				}
				default:
				{
					if (
						pPlayer->Get_Obj_Cur_Status() != OBJ_STATUS::ROLL 
						&& pPlayer->Get_Obj_Cur_Status() != OBJ_STATUS::THUNDER_BREATHING_PROCESS 
						&& pPlayer->Get_Obj_Cur_Status() != OBJ_STATUS::THUNDER_BREATHING
					)
					{
						if (static_cast<CPlayer*>(pPlayer)->Get_No_Death())
						{
							return;
						}

						if (CThunderBreathingMgr::Get_Instance()->Get_Player_Thunder_Breathing_Motion() != PLAYER_THUNDER_BREATHING_MOTION_END)
						{
							break;
						}

						CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
						CSoundMgr::Get_Instance()->PlaySound(L"dragon_death.wav", PLAYER_EFFECT, 1.f);

						pPlayer->Set_Obj_Cur_Status(OBJ_STATUS::LAY_DOWN_START);
					}
					break;
				}
				}
			}
		}
	}
}

// Kicked Door ->에 붙어있는 적 죽일 수 있음

void CollisionMgr::Collide_Player_Attack_Rect_With_Boss(list<CObj*> _pPlayerList, list<CObj*> _pBossList)
{
	for (auto pPlayer : _pPlayerList)
	{
		for (auto pBoss : _pBossList)
		{
			RECT tIntersectedRect;
			RECT tPlayerAttackRect = pPlayer->Get_Attack_Area_Rect();
			RECT tBossCollideRect = pBoss->Get_Collide_Rect();

			if (IntersectRect(&tIntersectedRect, &tPlayerAttackRect, &tBossCollideRect))
			{

				switch (CSceneMgr::Get_Instance()->Get_Cur_Scene_ID())
				{
				case SCENE_ID::SC_BOSS_01:
				{
					CBoss* boss = static_cast<CBoss*>(pBoss);
					switch (boss->Get_Obj_Cur_Dir())
					{
					case OBJ_DIR::LEFT:
					{
						CSoundMgr::Get_Instance()->StopSound(BOSS_SPEAK_SOUND_EFFECT);
						CSoundMgr::Get_Instance()->PlaySound(L"huntress_hurt.wav", BOSS_SPEAK_SOUND_EFFECT, 1.f);


						boss->Set_Cur_Boss_Status(BOSS_STATUS::BOSS_RECOVER_LEFT);
						CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_BLOOD, CAbstractFactory<CBlood>::Create(boss->Get_Info().fX, boss->Get_Info().fY, ATTACK_TYPE::NORMAL_ATTACK, boss->Get_Obj_Cur_Dir()));
						static_cast<CBossStage01*>(CSceneMgr::Get_Instance()->Get_Active_Scene())->Damage_Boss();


						break;
					}
					case OBJ_DIR::RIGHT:
					{
						CSoundMgr::Get_Instance()->StopSound(BOSS_SPEAK_SOUND_EFFECT);
						CSoundMgr::Get_Instance()->PlaySound(L"huntress_hurt.wav", BOSS_SPEAK_SOUND_EFFECT, 1.f);


						boss->Set_Cur_Boss_Status(BOSS_STATUS::BOSS_RECOVER_RIGHT);
						CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_BLOOD, CAbstractFactory<CBlood>::Create(boss->Get_Info().fX, boss->Get_Info().fY, ATTACK_TYPE::NORMAL_ATTACK, boss->Get_Obj_Cur_Dir()));
						static_cast<CBossStage01*>(CSceneMgr::Get_Instance()->Get_Active_Scene())->Damage_Boss();

						break;
					}
					}

					CCamera::Get_Instance()->Camera_Shaking();
					Vec2 renderPos = CCamera::Get_Instance()->GetRenderPos(Vec2{ boss->Get_Info().fX, boss->Get_Info().fY });
					//CHighlightMgr::Get_Instance()->Set_Highlight(POINT{ (LONG)renderPos.fX, (LONG)renderPos.fY });

					break;
				}
				case SCENE_ID::SC_BOSS_02:
				{
					CBoss2* boss = static_cast<CBoss2*>(pBoss);
					switch (boss->Get_Obj_Cur_Dir())
					{
					case OBJ_DIR::LEFT:
					{
						switch (boss->Get_Boss_Cur_Status())
						{
						

						case BOSS_STATUS::BOSS_DEAD_BODY_RIGHT:
						{
							boss->Set_Cur_Boss_Status(BOSS_STATUS::BOSS_NO_HEAD_DEAD_BODY_LEFT);
							CObjMgr::Get_Instance()->Add_Object(OBJ_ID_BOSS_HEAD, CAbstractFactory<CBossHead>::Create(boss->Get_Info().fX, boss->Get_Info().fY, boss->Get_Obj_Cur_Dir()));
							

							break;
						}


						case BOSS_STATUS::BOSS_DEAD_BODY_LEFT:
						{
							boss->Set_Cur_Boss_Status(BOSS_STATUS::BOSS_NO_HEAD_DEAD_BODY_LEFT);
							CObjMgr::Get_Instance()->Add_Object(OBJ_ID_BOSS_HEAD, CAbstractFactory<CBossHead>::Create(boss->Get_Info().fX, boss->Get_Info().fY, boss->Get_Obj_Cur_Dir()));

							break;
						}
						default:
						{
							boss->Set_Cur_Boss_Status(BOSS_STATUS::BOSS_RECOVER_LEFT);
							CSoundMgr::Get_Instance()->StopSound(BOSS_SPEAK_SOUND_EFFECT);
							CSoundMgr::Get_Instance()->PlaySound(L"huntress_hurt.wav", BOSS_SPEAK_SOUND_EFFECT, 1.f);

							CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_BLOOD, CAbstractFactory<CBlood>::Create(boss->Get_Info().fX, boss->Get_Info().fY, ATTACK_TYPE::NORMAL_ATTACK, boss->Get_Obj_Cur_Dir()));
							static_cast<CBossStage02*>(CSceneMgr::Get_Instance()->Get_Active_Scene())->Damage_Boss();
							break;
						}
						}
						break;
					}
					case OBJ_DIR::RIGHT:
					{
						switch (boss->Get_Boss_Cur_Status())
						{
						case BOSS_STATUS::BOSS_DEAD_BODY_LEFT:
						{
							boss->Set_Cur_Boss_Status(BOSS_STATUS::BOSS_NO_HEAD_DEAD_BODY_RIGHT);
							CObjMgr::Get_Instance()->Add_Object(OBJ_ID_BOSS_HEAD, CAbstractFactory<CBossHead>::Create(boss->Get_Info().fX, boss->Get_Info().fY, boss->Get_Obj_Cur_Dir()));

							break;
						}
						case BOSS_STATUS::BOSS_DEAD_BODY_RIGHT:
						{
							boss->Set_Cur_Boss_Status(BOSS_STATUS::BOSS_NO_HEAD_DEAD_BODY_RIGHT);
							CObjMgr::Get_Instance()->Add_Object(OBJ_ID_BOSS_HEAD, CAbstractFactory<CBossHead>::Create(boss->Get_Info().fX, boss->Get_Info().fY, boss->Get_Obj_Cur_Dir()));


							break;
						}
						default:
						{
							boss->Set_Cur_Boss_Status(BOSS_STATUS::BOSS_RECOVER_RIGHT);
							CSoundMgr::Get_Instance()->StopSound(BOSS_SPEAK_SOUND_EFFECT);
							CSoundMgr::Get_Instance()->PlaySound(L"huntress_hurt.wav", BOSS_SPEAK_SOUND_EFFECT, 1.f);

							CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_BLOOD, CAbstractFactory<CBlood>::Create(boss->Get_Info().fX, boss->Get_Info().fY, ATTACK_TYPE::NORMAL_ATTACK, boss->Get_Obj_Cur_Dir()));
							static_cast<CBossStage02*>(CSceneMgr::Get_Instance()->Get_Active_Scene())->Damage_Boss();
							break;
						}
						}

					}
					}
					CCamera::Get_Instance()->Camera_Shaking();
					Vec2 renderPos = CCamera::Get_Instance()->GetRenderPos(Vec2{ boss->Get_Info().fX, boss->Get_Info().fY });
					//CHighlightMgr::Get_Instance()->Set_Highlight(POINT{ (LONG)renderPos.fX, (LONG)renderPos.fY });


					break;
				}
				}
				
			}
		}
	}
}

void CollisionMgr::Collide_Player_With_Door_Collide(list<CObj*> _pPlayerList, list<CObj*> _pDoorList)
{
	for (auto pPlayer : _pPlayerList)
	{
		for (auto pDoor : _pDoorList)
		{
			RECT tIntersectedRect;
			RECT tPlayerCollide = pPlayer->Get_Collide_Rect();
			RECT tDoorCollide = pDoor->Get_Collide_Rect();

			if (IntersectRect(&tIntersectedRect, &tPlayerCollide, &tDoorCollide) && static_cast<CDoor*>(pDoor)->Get_Door_Type() == DOOR_TYPE::CLOSE)
			{
				pPlayer->Set_Obj_Cur_Status(OBJ_STATUS::DOOR_KICK);
				static_cast<CDoor*>(pDoor)->Set_Door_Type(DOOR_TYPE::KICKED);

				CCamera::Get_Instance()->Camera_Shaking();

				Vec2 renderPos = CCamera::Get_Instance()->GetRenderPos(Vec2{ pPlayer->Get_Info().fX, pPlayer->Get_Info().fY });
				//CHighlightMgr::Get_Instance()->Set_Highlight(POINT{ (LONG)renderPos.fX, (LONG)renderPos.fY });
			}
		}
	}
}

void CollisionMgr::Collide_Player_With_Climb_Tile(list<CObj*> _pPlayerList, list<CObj*> _pTileList)
{
	for (auto pPlayer : _pPlayerList)
	{
		for (auto pTile : _pTileList)
		{
			RECT tIntersectedRect;
			if (static_cast<CTile*>(pTile)->Get_DrawID() == TILE_TYPE::CLIMB_WALL_TILE)
			{
				int a = 3;
			}
		}
	}
}

void CollisionMgr::Collide_Enemy_Width_Pairing_Bullet(list<CObj*> _pEnemyList, list<CObj*> _pBulletList)
{
	for (auto pEnemy : _pEnemyList)
	{
		for (auto pBullet : _pBulletList)
		{
			if (static_cast<CBullet*>(pBullet)->Get_Pairing() == false)
			{
				continue;
			}

			RECT tIntersectedRect;
			RECT tEnemyCollisionRect = pEnemy->Get_Collide_Rect();
			
			RECT tEnemyPairingCollisionRect = {
				tEnemyCollisionRect.left - 30,
				tEnemyCollisionRect.top - 30,
				tEnemyCollisionRect.right + 30,
				tEnemyCollisionRect.bottom + 30
			};

			RECT pBulletRect = pBullet->Get_Rect();
			
			// 패링 하이라이트 보여주기
			if (IntersectRect(&tIntersectedRect, &tEnemyPairingCollisionRect, &pBulletRect))
			{
				if (CSceneMgr::Get_Instance()->Get_Active_Scene()->Get_Highlight_Event() == false)
				{
					CSceneMgr::Get_Instance()->Get_Active_Scene()->Set_Highlight_Event(true);
					CSceneMgr::Get_Instance()->Get_Active_Scene()->Set_Highlight_Target_Pos(pBullet->Get_Info().fX, pBullet->Get_Info().fY);

				}
				pEnemy->Set_Obj_Cur_Status(OBJ_STATUS::DEAD);
				pBullet->Set_Dead(true);
			}

			// 진짜 충돌
			if (IntersectRect(&tIntersectedRect, &tEnemyCollisionRect, &pBulletRect))
			{
				pEnemy->Set_Obj_Cur_Status(OBJ_STATUS::DEAD);
				CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_BLOOD, CAbstractFactory<CBlood>::Create(pEnemy->Get_Info().fX, pEnemy->Get_Info().fY, ATTACK_TYPE::NORMAL_ATTACK, pEnemy->Get_Obj_Cur_Dir()));
				pBullet->Set_Dead(true);

			}
		}
	}
}

void CollisionMgr::Collide_Enemy_With_Explosion(list<CObj*> _pEnemyList, list<CObj*> _pExplosionList)
{
	for (auto pEnemy : _pEnemyList)
	{
		for (auto pExplosion : _pExplosionList)
		{
			RECT tIntersectedRect;
			RECT tEnemyCollisionRect = pEnemy->Get_Collide_Rect();
			RECT pExplosionRect = pExplosion->Get_Rect();

			if (IntersectRect(&tIntersectedRect, &tEnemyCollisionRect, &pExplosionRect))
			{
				pEnemy->Set_Obj_Cur_Status(OBJ_STATUS::DEAD);
			}
		}
	}
}

void CollisionMgr::Collide_Player_Attack_Rect_With_Enemy(list<CObj*> _pPlayerList, list<CObj*> _pEnemyList)
{
	for (auto pPlayer : _pPlayerList)
	{
		for (auto pEnemy : _pEnemyList)
		{
			RECT tIntersectedRect;
			RECT tPlayerAttackRect = pPlayer->Get_Attack_Area_Rect();
			RECT tEnemyRect = pEnemy->Get_Collide_Rect();
			
			if (IntersectRect(&tIntersectedRect, &tPlayerAttackRect, &tEnemyRect))
			{
				pEnemy->Set_Obj_Cur_Status(OBJ_STATUS::DEAD);
				
				POINT tMousePos = CMouseMgr::Get_Instance()->Get_Mouse_Pos();


				// 마우스 좌표를 이용해서 공격 이동을 표현해보자
				//printf("(%d, %d)\n ", tMousePos.x, tMousePos.y);

				CAttackMgr::Get_Instance()->Set_Attack_Time();
				CComboMgr::Get_Instance()->Kill_Enemy(pEnemy->Get_Info().fX, pEnemy->Get_Info().fY);
				
				switch (pPlayer->Get_Obj_Cur_Dir())
				{
				case OBJ_DIR::LEFT:
				{
					pEnemy->Set_KnockBack(-50.0f);
					float fY(0.f);
					CLineMgr::Get_Instance()->Collision_Line_Enemy(
						pEnemy->Get_Info().fX,
						-50,
						pEnemy->Get_Info().fY,
						pEnemy->Get_Info().fCY,
						&fY,
						pEnemy->Get_Obj_Cur_Status()
					);
					pEnemy->Set_Info(
						INFO{
							pEnemy->Get_Info().fX,
							fY - pEnemy->Get_Info().fCY / 2.0f,
							pEnemy->Get_Info().fCX,
							pEnemy->Get_Info().fCY
						}
					);

					break;
				}
				case OBJ_DIR::RIGHT:
				{
					pEnemy->Set_KnockBack(+50.f);
					float fY(0.f);
					CLineMgr::Get_Instance()->Collision_Line_Enemy(
						pEnemy->Get_Info().fX,
						50,
						pEnemy->Get_Info().fY,
						pEnemy->Get_Info().fCY,
						&fY,
						pEnemy->Get_Obj_Cur_Status()
					);
					pEnemy->Set_Info(
						INFO{
							pEnemy->Get_Info().fX,
							fY - pEnemy->Get_Info().fCY / 2.0f,
							pEnemy->Get_Info().fCX,
							pEnemy->Get_Info().fCY
						}
					);
					break;
				}
				}

				CSoundMgr::Get_Instance()->StopSound(ENEMY_DEAD_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"sound_enemy_bloodsplat_1.wav", ENEMY_DEAD_EFFECT, 1.f);
				CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_BLOOD, CAbstractFactory<CBlood>::Create(pEnemy->Get_Info().fX, pEnemy->Get_Info().fY, ATTACK_TYPE::NORMAL_ATTACK, pEnemy->Get_Obj_Cur_Dir()));
				CCamera::Get_Instance()->Camera_Shaking();
			}
		}
	}
}

void CollisionMgr::Collide_Oil_Drum_With_Explosion(list<CObj*> _pOilDrumList, list<CObj*> _pExplosionList)
{
	for (auto pOilDrum : _pOilDrumList)
	{
		for (auto pExplosion : _pExplosionList)
		{
			RECT tIntersectedRect;
			RECT tExplosionRect = pExplosion->Get_Rect();
			RECT tOilDrumRect = pOilDrum->Get_Rect();

			bool bOilDrumDead = pOilDrum->Get_Dead();
			bool bExplosionDead = pExplosion->Get_Dead();
			if (IntersectRect(&tIntersectedRect, &tExplosionRect, &tOilDrumRect) && bOilDrumDead == false && bExplosionDead == false)
			{
				pOilDrum->Set_Dead(true);
				CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_BIG_EXPLOSION, CAbstractFactory<CBigExplosion>::Create(pOilDrum->Get_Info().fX, pOilDrum->Get_Info().fY));
				CCamera::Get_Instance()->Camera_Shaking();
			}
		}
	}
}

void CollisionMgr::Collide_Explosive_With_Oil_Drum(list<CObj*> _pExplosiveList, list<CObj*> _pOilDrumList)
{
	for (auto pExplosive : _pExplosiveList)
	{
		for (auto pOilDrum : _pOilDrumList)
		{
			RECT tIntersectedRect;
			RECT tExplosiveRect = pExplosive->Get_Rect();
			RECT tOilDrumRect = pOilDrum->Get_Rect();

			if (IntersectRect(&tIntersectedRect, &tExplosiveRect, &tOilDrumRect))
			{
				pOilDrum->Set_Dead(true);
				pExplosive->Set_Dead(true);

				CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_BIG_EXPLOSION, CAbstractFactory<CBigExplosion>::Create(pOilDrum->Get_Info().fX, pOilDrum->Get_Info().fY));
				CCamera::Get_Instance()->Camera_Shaking();
			}
		}
	}
}

void CollisionMgr::Collide_Player_Attack_Rect_With_Bullet(list<CObj*> _pPlayerList, list<CObj*> _pBulletList)
{
	for (auto pPlayer : _pPlayerList)
	{
		for (auto pBullet : _pBulletList)
		{
			RECT tIntersectedRect;
			RECT tPlayerAttackAreaRect = pPlayer->Get_Attack_Area_Rect();
			RECT tBulletRect = pBullet->Get_Rect();
			
			bool bIntersectRect = IntersectRect(&tIntersectedRect, &tPlayerAttackAreaRect, &tBulletRect);
			bool bPairing = static_cast<CBullet*>(pBullet)->Get_Pairing();
		
			
			if (bIntersectRect && bPairing == false)
			{
				CSoundMgr::Get_Instance()->StopSound(BULLET_PAIRING_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"slash_bullet.wav", BULLET_PAIRING_EFFECT, 1.f);

				CAttackMgr::Get_Instance()->Set_Attack_Time();
				static_cast<CBullet*>(pBullet)->Set_Pairing(true);
				pBullet->Set_Speed(pBullet->Get_Speed() * -1.f);
				CObjMgr::Get_Instance()->Add_Object(OBJ_ID_BULLET_EFFECT, CAbstractFactory<CBulletEffect>::Create(pBullet->Get_Info().fX, pBullet->Get_Info().fY));
				Vec2 renderPos = CCamera::Get_Instance()->GetRenderPos(Vec2{ pBullet->Get_Info().fX, pBullet->Get_Info().fY });
				CCamera::Get_Instance()->Camera_Shaking();
			}
		}
	}
}

void CollisionMgr::Collide_Player_With_Enemy_Attack_Rect(list<CObj*> _pPlayerList, list<CObj*> _pEnemyList)
{
	for (auto pPlayer : _pPlayerList)
	{
		for (auto pEnemy : _pEnemyList)
		{
			RECT tIntersectedRect;
			RECT tPlayerCollisionRect = pPlayer->Get_Collide_Rect();
			RECT tEnemyAttackAreaRect = pEnemy->Get_Attack_Area_Rect();
			
			if (IntersectRect(&tIntersectedRect, &tPlayerCollisionRect, &tEnemyAttackAreaRect))
			{
				OBJ_STATUS pCurrentEnemyStatus = pEnemy->Get_Obj_Cur_Status();
				switch (pCurrentEnemyStatus)
				{
				case OBJ_STATUS::ATTACK:
				{
					if (pEnemy->Get_Damageable() && pPlayer->Get_Obj_Cur_Status() == OBJ_STATUS::ROLL)
					{
						CSceneMgr::Get_Instance()->Get_Active_Scene()->Set_Highlight_Event(true);
						CSceneMgr::Get_Instance()->Get_Active_Scene()->Set_Highlight_Target_Pos(pPlayer->Get_Info().fX, pPlayer->Get_Info().fY);
						continue;
					}

					if (pEnemy->Get_Damageable() 
						&& pPlayer->Get_Obj_Cur_Status() != OBJ_STATUS::ROLL 
						&& pPlayer->Get_Obj_Cur_Status() != OBJ_STATUS::THUNDER_BREATHING_PROCESS 
						&& pPlayer->Get_Obj_Cur_Status() != OBJ_STATUS::THUNDER_BREATHING
					)
					{
						if (static_cast<CPlayer*>(pPlayer)->Get_No_Death())
						{
							return;
						}

						if (CThunderBreathingMgr::Get_Instance()->Get_Player_Thunder_Breathing_Motion() != PLAYER_THUNDER_BREATHING_MOTION_END)
						{
							break;
						}

						CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
						CSoundMgr::Get_Instance()->PlaySound(L"dragon_death.wav", PLAYER_EFFECT, 1.f);

						pPlayer->Set_Obj_Cur_Status(OBJ_STATUS::LAY_DOWN_START);
					}
					break;
				}
				default:
				{
					pEnemy->Set_Obj_Cur_Status(OBJ_STATUS::ATTACK);
					break;
				}
				}
			}
		}
	}
}

// 벽력일섬 
void CollisionMgr::Collide_Player_Collider_With_Enemy_On_Thunder_Breathing(list<CObj*> _pPlayerList, list<CObj*> _pEnemyList)
{
	for (auto pPlayer : _pPlayerList)
	{
		for (auto pEnemy : _pEnemyList)
		{
			
		}
	}
}

void CollisionMgr::Collide_Player_Collider_With_Enemy_Attack_Area(list<CObj*> _pPlayerList, list<CObj*> _pEnemyList)
{
	for (auto pPlayer : _pPlayerList)
	{
		for (auto pEnemy : _pEnemyList)
		{
			if (pPlayer->Get_Obj_Cur_Status() == OBJ_STATUS::ROLL)
			{
				continue;
			}
			
			RECT tempRect;
			RECT pPlayerCollideRect = pPlayer->Get_Collide_Rect();
			
		}
	}
}

void CollisionMgr::Collide_Player_Collider_With_Bullet(list<CObj*> _pPlayerList, list<CObj*> _pBulletList)
{
	for (auto pPlayer : _pPlayerList)
	{
		for (auto pBullet : _pBulletList)
		{
			if (pPlayer->Get_Obj_Cur_Status() == OBJ_STATUS::ROLL || pPlayer->Get_Obj_Cur_Dir() == OBJ_STATUS::THUNDER_BREATHING || pPlayer->Get_Obj_Cur_Dir() == OBJ_STATUS::THUNDER_BREATHING_PROCESS)
			{
				continue;
			}

			RECT tempRect;
			RECT pPlayerCollideRect = pPlayer->Get_Collide_Rect();
			RECT pBulletCollideRect = pBullet->Get_Rect();

			if (IntersectRect(&tempRect, &pPlayerCollideRect, &pBulletCollideRect))
			{
				if (static_cast<CPlayer*>(pPlayer)->Get_No_Death())
				{
					break;
				}

				if (CThunderBreathingMgr::Get_Instance()->Get_Player_Thunder_Breathing_Motion() != PLAYER_THUNDER_BREATHING_MOTION_END)
				{
					break;
				}
				CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"dragon_death.wav", PLAYER_EFFECT, 1.f);

				pPlayer->Set_Obj_Cur_Status(OBJ_STATUS::LAY_DOWN_START);


				
			}
		}
	}
}

void CollisionMgr::Collide_Boss2_With_Tile(list<CObj*> _pBossList, list<CObj*> _pTileList)
{
	float fX(0.f), fY(0.f);
	for (auto pBoss : _pBossList)
	{
		for (auto pTile : _pTileList)
		{
			if (Check_Rect_With_Dst_Collider(pBoss, pTile, &fX, &fY))
			{
				if (static_cast<CTile*>(pTile)->Get_Option() == TILE_TYPE::CLIMB_WALL_TILE)
				{
					if (pBoss->Get_Collide_Info().fX < pTile->Get_Info().fX)
					{
						// 좌충돌
						INFO tGernadeInfo = pBoss->Get_Info();
						RECT tGernadeRect = pBoss->Get_Rect();
						RECT tRenderRect = pBoss->Get_Render_Rect();
						INFO tCollideInfo = pBoss->Get_Collide_Info();
						RECT tCollideRect = pBoss->Get_Collide_Rect();

						pBoss->Set_Position(tGernadeInfo.fX - fX, tGernadeInfo.fY);
						pBoss->Set_Rect(RECT{
							(LONG)(tGernadeRect.left - fX),
							tGernadeRect.top,
							(LONG)(tGernadeRect.right - fX),
							tGernadeRect.bottom
							});
						pBoss->Set_RenderRect(RECT{
							(LONG)(tRenderRect.left - fX),
							tRenderRect.top,
							(LONG)(tRenderRect.right - fX),
							tRenderRect.bottom
							});

						pBoss->Set_Collide_Pos(tCollideInfo.fX - fX, tCollideInfo.fY);
						pBoss->Set_Collide_Rect(
							RECT{
								(LONG)(tCollideRect.left - fX),
								tCollideRect.top,
								(LONG)(tCollideRect.right - fX),
								tCollideRect.bottom
							}
						);

						static_cast<CBoss2*>(pBoss)->Set_Boss_Pattern_3_Detail(CBoss2::BOSS_PATTERN_3_DETAIL::BOSS_JUMP_WALL_GRAB_LEFT);
						static_cast<CBoss2*>(pBoss)->Set_Grab_Time();
					}
					else
					{
						// 우충돌
						INFO tGernadeInfo = pBoss->Get_Info();
						RECT tGernadeRect = pBoss->Get_Rect();
						RECT tRenderRect = pBoss->Get_Render_Rect();
						INFO tCollideInfo = pBoss->Get_Collide_Info();
						RECT tCollideRect = pBoss->Get_Collide_Rect();


						pBoss->Set_Position(tGernadeInfo.fX + fX, tGernadeInfo.fY);
						pBoss->Set_Rect(RECT{
							(LONG)(tGernadeRect.left + fX),
							tGernadeRect.top,
							(LONG)(tGernadeRect.right + fX),
							tGernadeRect.bottom
							});
						pBoss->Set_RenderRect(RECT{
							(LONG)(tRenderRect.left + fX),
							tRenderRect.top,
							(LONG)(tRenderRect.right + fX),
							tRenderRect.bottom
							});

						pBoss->Set_Collide_Pos(tCollideInfo.fX + fX, tCollideInfo.fY);
						pBoss->Set_Collide_Rect(
							RECT{
								(LONG)(tCollideRect.left + fX),
								tCollideRect.top,
								(LONG)(tCollideRect.right + fX),
								tCollideRect.bottom
							}
						);
						static_cast<CBoss2*>(pBoss)->Set_Boss_Pattern_3_Detail(CBoss2::BOSS_PATTERN_3_DETAIL::BOSS_JUMP_WALL_GRAB_RIGHT);
						static_cast<CBoss2*>(pBoss)->Set_Grab_Time();
					}
				}
			}
		}
	}
}

void CollisionMgr::Collide_Gernade_With_Tile(list<CObj*> _pGernadeList, list<CObj*> _pTileList)
{
	float fX(0.f), fY(0.f);
	for (auto pGernade : _pGernadeList)
	{
		for (auto pTile : _pTileList)
		{
			if (Check_Rect(pGernade, pTile, &fX, &fY))
			{
				
				if (fX > fY)
				{
					if (pGernade->Get_Info().fY < pTile->Get_Info().fY)
					{
						// 상충돌
						INFO tGernadeInfo = pGernade->Get_Info();
						RECT tGernadeRect = pGernade->Get_Rect();
						RECT tRenderRect = pGernade->Get_Render_Rect();
						RECT tCollideRect = pGernade->Get_Collide_Rect();

						pGernade->Set_Position(tGernadeInfo.fX, tGernadeInfo.fY + fY);
						pGernade->Set_Rect(RECT{ 
							tGernadeRect.left, 
							(LONG)(tGernadeRect.top - fY), 
							tGernadeRect.right, 
							(LONG)(tGernadeRect.bottom - fY) 
						});
						pGernade->Set_RenderRect(RECT{
							tRenderRect.left,
							(LONG)(tRenderRect.top - fY),
							tRenderRect.right,
							(LONG)(tRenderRect.bottom - fY)
						});

						pGernade->Set_Angle(-pGernade->Get_Angle());
					}
					else
					{
						// 하충돌
						INFO tGernadeInfo = pGernade->Get_Info();
						RECT tGernadeRect = pGernade->Get_Rect();
						RECT tRenderRect = pGernade->Get_Render_Rect();
						RECT tCollideRect = pGernade->Get_Collide_Rect();
						
						pGernade->Set_Position(tGernadeInfo.fX, tGernadeInfo.fY + fY);
						pGernade->Set_Rect(RECT{ 
							tGernadeRect.left, 
							(LONG)(tGernadeRect.top + fY), 
							tGernadeRect.right, 
							(LONG)(tGernadeRect.bottom + fY) 
						});

						pGernade->Set_RenderRect(RECT{
							tRenderRect.left,
							(LONG)(tRenderRect.top + fY),
							tRenderRect.right,
							(LONG)(tRenderRect.bottom + fY)
						});

						pGernade->Set_Angle(-pGernade->Get_Angle());
					}


				}
				else
				{
					if (pGernade->Get_Info().fX < pTile->Get_Info().fX)
					{
						// 좌충돌
						INFO tGernadeInfo = pGernade->Get_Info();
						RECT tGernadeRect = pGernade->Get_Rect();
						RECT tRenderRect = pGernade->Get_Render_Rect();

						pGernade->Set_Position(tGernadeInfo.fX - fX, tGernadeInfo.fY);
						pGernade->Set_Rect(RECT{ 
							(LONG)(tGernadeRect.left - fX), 
							tGernadeRect.top, 
							(LONG)(tGernadeRect.right - fX), 
							tGernadeRect.bottom 
						});
						pGernade->Set_RenderRect(RECT{
							(LONG)(tRenderRect.left - fX),
							tRenderRect.top,
							(LONG)(tRenderRect.right - fX),
							tRenderRect.bottom
						});

						pGernade->Set_Angle(PI - pGernade->Get_Angle());
					}
					else
					{
						// 우충돌
						INFO tGernadeInfo = pGernade->Get_Info();
						RECT tGernadeRect = pGernade->Get_Rect();
						RECT tRenderRect = pGernade->Get_Render_Rect();

						pGernade->Set_Position(tGernadeInfo.fX + fX, tGernadeInfo.fY);
						pGernade->Set_Rect(RECT{
							(LONG)(tGernadeRect.left + fX),
							tGernadeRect.top,
							(LONG)(tGernadeRect.right + fX),
							tGernadeRect.bottom
							});
						pGernade->Set_RenderRect(RECT{
							(LONG)(tRenderRect.left + fX),
							tRenderRect.top,
							(LONG)(tRenderRect.right + fX),
							tRenderRect.bottom
						});

						pGernade->Set_Angle(PI - pGernade->Get_Angle());
					}
				}
			}
		}
	}
}

void CollisionMgr::Collide_Enemy_Ray_With_Door_Collide(list<CObj*> _pEnemyList, list<CObj*> _pDoorList)
{
	for (auto pEnemy : _pEnemyList)
	{
		for (auto pDoor : _pDoorList)
		{
			RECT tIntersectedRect;
			RECT tEnemyRayRect = pEnemy->Get_Ray_Rect();
			RECT tDoorCollisionRect = pDoor->Get_Collide_Rect();
			DOOR_TYPE eDoorType = static_cast<CDoor*>(pDoor)->Get_Door_Type();

			if (IntersectRect(&tIntersectedRect, &tEnemyRayRect, &tDoorCollisionRect) && eDoorType == DOOR_TYPE::CLOSE)
			{
				pEnemy->Set_Blind(true);
			}
		}
	}
}

void CollisionMgr::Collide_Player_With_Enemy_Ray_Rect(list<CObj*> _pPlayerList, list<CObj*> _pEnemyList)
{
	for (auto pPlayer : _pPlayerList)
	{
		for (auto pEnemy : _pEnemyList)
		{
			RECT tIntersectedRect;
			RECT tPlayerCollisionRect = pPlayer->Get_Collide_Rect();
			RECT tEnemyRayRect = pEnemy->Get_Ray_Rect();
			bool bEnemyBlind = pEnemy->Get_Blind();

			if (IntersectRect(&tIntersectedRect, &tPlayerCollisionRect, &tEnemyRayRect) && bEnemyBlind == false)
			{
				switch (pEnemy->Get_Obj_Cur_Status())
				{
				case OBJ_STATUS::ATTACK:
				{
					break;
				}
				default:
				{
					pEnemy->Set_Obj_Cur_Status(OBJ_STATUS::CHASE);
					pEnemy->Set_Target(pPlayer);
					break;
				}
				}
			}
		}
	}
}

void CollisionMgr::Collide_Player_With_Wall_Tile(list<CObj*> _pPlayerList, list<CObj*> _pWallTileList)
{
	for (auto pPlayer : _pPlayerList)
	{
		for (auto pWall : _pWallTileList)
		{
			RECT tIntersectedRect;

			if (Check_Rect_Collision(pPlayer, pWall, &tIntersectedRect))
			{
				TILE_TYPE eCurrentTileType = static_cast<CTile*>(pWall)->Get_DrawID();
				if (eCurrentTileType == TILE_TYPE::CLIMB_WALL_TILE)
				{
					pPlayer->Set_Wall_Grab();
					float fInterval = std::abs(tIntersectedRect.left - tIntersectedRect.right);
					pPlayer->Push_Out_Wall(fInterval);
				}
			}
		}
	}
}

bool CollisionMgr::Check_Rect_Collision(CObj* _pDst, CObj* _pSrc, RECT* _tRc)
{
	RECT tDstRect = _pDst->Get_Collide_Rect();
	RECT tSrcRect = _pSrc->Get_Rect();
	if (IntersectRect(_tRc, &tDstRect, &tSrcRect))
	{
		return true;
	}
	return false;
}

bool CollisionMgr::Check_Rect(CObj* _pDst, CObj* _pSrc, float* pX, float* pY)
{
	float fWidth = abs(_pDst->Get_Info().fX - _pSrc->Get_Info().fX);
	float fHeight = abs(_pDst->Get_Info().fY - _pSrc->Get_Info().fY);
	
	float fRadiusX = (_pDst->Get_Info().fCX + _pSrc->Get_Info().fCX) * 0.5f;
	float fRadiusY = (_pDst->Get_Info().fCY + _pSrc->Get_Info().fCY) * 0.5f;

	if ((fRadiusX > fWidth) && (fRadiusY > fHeight))
	{
		*pX = fRadiusX - fWidth;
		*pY = fRadiusY - fHeight;
		return true;
	}

	return false;
}

bool CollisionMgr::Check_Rect_With_Dst_Collider(CObj* _pDst, CObj* _pSrc, float* pX, float* pY)
{
	float fWidth = abs(_pDst->Get_Collide_Info().fX - _pSrc->Get_Info().fX);
	float fHeight = abs(_pDst->Get_Collide_Info().fY - _pSrc->Get_Info().fY);
	
	float fRadiusX = (_pDst->Get_Collide_Info().fCX + _pSrc->Get_Info().fCX) * 0.5f;
	float fRadiusY = (_pDst->Get_Collide_Info().fCY + _pSrc->Get_Info().fCY) * 0.5f;

	if ((fRadiusX > fWidth) && (fRadiusY > fHeight))
	{
		*pX = fRadiusX - fWidth;
		*pY = fRadiusY - fHeight;
		return true;
	}
	return false;
}
