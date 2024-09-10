#pragma once

#include "Obj.h"
#include "Explosive.h"
#include "Smoke.h"
#include "Lazer.h"

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory() {}
	~CAbstractFactory() {}

public:
	static CObj* Create()
	{
		CObj* pObj = new T;
		pObj->Initialize();
		return pObj;
	}

	static CObj* Create(float _fX, float _fY)
	{
		CObj* pObj = new T;
		pObj->Set_Position(_fX, _fY);
		pObj->Initialize();
		return pObj;
	}

	static CObj* Create(float _fX, float _fY, float _fAngle)
	{
		CObj* pObj = new T;
		pObj->Set_Position(_fX, _fY);
		pObj->Set_Angle(_fAngle);
		pObj->Initialize();
		return pObj;
	}

	static CObj* Create(float _fX, float _fY, OBJ_DIR _eObjDir)
	{
		CObj* pObj = new T;
		pObj->Set_Position(_fX, _fY);
		pObj->Set_Obj_Dir(_eObjDir);
		pObj->Initialize();
		return pObj;
	}

	static CObj* Create(float _fX, float _fY, float _fAngle, OBJ_DIR _eObjDir)
	{
		CObj* pObj = new T;
		pObj->Set_Position(_fX, _fY);
		pObj->Set_Angle(_fAngle);
		pObj->Set_Obj_Dir(_eObjDir);
		pObj->Initialize();
		return pObj;
	}


	static CObj* Create(float _fX, float _fY, LAZER_TYPE _eLazerType)
	{
		CObj* pObj = new CLazer;
		pObj->Set_Position(_fX, _fY);
		static_cast<CLazer*>(pObj)->Set_Lazer_Type(_eLazerType);
		pObj->Initialize();
		return pObj;
	}

	static CObj* Create(float _fX, float _fY, float _fCX, float _fCY, OBJ_DIR _eObjDir)
	{
		CObj* pObj = new T;
		pObj->Set_Position(_fX, _fY);
		pObj->Set_Scale(_fCX, _fCY);
		pObj->Set_Obj_Dir(_eObjDir);
		pObj->Initialize();
		return pObj;
	}

	// for blood effect
	static CObj* Create(float _fX, float _fY, ATTACK_TYPE _eAttackType, OBJ_DIR _eObjDir)
	{
		CObj* pObj = new T;
		pObj->Set_Position(_fX, _fY);
		pObj->Set_Obj_Dir(_eObjDir);
		pObj->Set_Attack_Type(_eAttackType);
		pObj->Initialize();
		return pObj;
	}

	static CObj* Create(float _fX, float _fY, float _fCX, float _fCY)
	{
		CObj* pObj = new T;
		pObj->Set_Position(_fX, _fY);
		pObj->Set_Scale(_fCX, _fCY);
		pObj->Initialize();
		return pObj;
	}
	
	static CObj* Create(float _fX, float _fY, float _fCX, float _fCY, float _fDegree)
	{
		CObj* pObj = new T;
		
		pObj->Set_Position(_fX, _fY);
		pObj->Set_Scale(_fCX, _fCY);
		pObj->Set_Degree(_fDegree);
		pObj->Initialize();

		return pObj;
	}

	static CObj* Create(float _fX, float _fY, float _fCX, float _fCY, float _fDegree, OBJ_DIR _eObjDir)
	{
		CObj* pObj = new T;
		pObj->Set_Position(_fX, _fY);
		pObj->Set_Scale(_fCX, _fCY);
		pObj->Set_Degree(_fDegree);
		pObj->Set_Obj_Dir(_eObjDir);
		pObj->Initialize();
		return pObj;
	}


	static CObj* Create(
		float _fX, 
		float _fY, 
		float _fCX, 
		float _fCY, 
		float _fDegree, 
		OBJ_DIR _eObjDir,
		TCHAR* _pFrameKey
	)
	{
		CObj* pObj = new T;

		pObj->Set_Position(_fX, _fY);
		pObj->Set_Scale(_fCX, _fCY);
		pObj->Set_Degree(_fDegree);
		pObj->Set_Obj_Dir(_eObjDir);
		pObj->Set_Frame_Key(_pFrameKey);

		pObj->Initialize();
		return pObj;
	}

	// Enemy Factory
	static CObj* Create(
		float _fX,
		float _fY,
		float _fCX,
		float _fCY,
		OBJ_DIR _eObjDir,
		ENEMY_TYPE _eEnemyType,
		float _fStartWalkPos,
		float _fEndWalkPos
	)
	{
		CObj* pObj = new T;
		pObj->Set_Position(_fX, _fY);
		pObj->Set_Scale(_fCX, _fCY);
		pObj->Set_Obj_Dir(_eObjDir);
		pObj->Set_Enemy_Type(_eEnemyType);
		pObj->Set_Start_Walk_Pos(_fStartWalkPos);
		pObj->Set_End_Walk_Pos(_fEndWalkPos);
		pObj->Set_Obj_Cur_Status(OBJ_STATUS::IDLE);
		pObj->Initialize();
		return pObj;
	}

	static CObj* Create(
		float _fX,
		float _fY,
		float _fSpeed,
		OBJ_DIR _eObjDir,
		Vec2 _vNormalVec
	)
	{
		CObj* pObj = new T;
		pObj->Set_Position(_fX, _fY);
		pObj->Set_Speed(_fSpeed);
		pObj->Set_Normal_Vec(_vNormalVec);
		pObj->Initialize();
		return pObj;
	}

	static CObj* Create(
		float _fX,
		float _fY,
		EXPLOSIVE_TYPE _eExplosiveType
	)
	{
		CObj* pObj = new CExplosive;
		pObj->Set_Position(_fX, _fY);
		static_cast<CExplosive*>(pObj)->Set_Explosive_Type(_eExplosiveType);
		pObj->Initialize();
		return pObj;
	}

	static CObj* Create(
		float _fX,
		float _fY,
		EXPLOSIVE_TYPE _eExplosiveType,
		Vec2 _vNormalVec
	)
	{
		CObj* pObj = new CExplosive;
		pObj->Set_Position(_fX, _fY);
		static_cast<CExplosive*>(pObj)->Set_Explosive_Type(_eExplosiveType);
		pObj->Set_Normal_Vec(_vNormalVec);
		pObj->Initialize();
		return pObj;
	}

	static CObj* Create(
		float _fX,
		float _fY,
		SMOKE_TYPE _eSmokeType
	)
	{

	}
};