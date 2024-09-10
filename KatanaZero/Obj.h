#pragma once

#include "Camera.h"
class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void Initialize() PURE;
	virtual int Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render(HDC _hDC) PURE;
	virtual void Release() PURE;

public:
	OBJ_DIR Get_Obj_Cur_Dir() { return m_eObjCurDir; }
	OBJ_STATUS	Get_Obj_Cur_Status() { return m_eObjCurStatus; }
	FRAME		Get_Frame() { return m_tFrame; }
	INFO		Get_Info() { return m_tInfo; }
	RECT		Get_Rect() { return m_tRect; }
	RECT		Get_Render_Rect() { return m_tRenderRect; }
	RECT		Get_Ray_Rect() { return m_tRayRect; }
	CObj*		Get_Target() { return m_pTarget; }

	TCHAR*		Get_Frame_Key() { return m_pFrameKey; }
	bool		Get_Dead() { return m_bDead; }
	ENEMY_TYPE Get_EnemyType() { return m_eEnemyType; }
	RECT		Get_Attack_Area_Rect() { return m_tAttackAreaRect; }
	Vec2		Get_Normal_Vec() { return m_vNormalVec; }
	INFO		Get_Collide_Info() { return m_tCollideInfo; }

	float Get_Start_Walk_Pos() { return m_fStartWalkPos; }
	float Get_End_Walk_Pos() { return m_fEndWalkPos; }
	float Get_Speed() { return m_fSpeed;  }
	float Get_Angle() { return m_fAngle; }

	bool Get_Blind() { return m_bBlind; }
	bool Get_Damageable() { return m_bDamageable; }

public:

	void Set_Dead(bool _bDead) { m_bDead = _bDead; }
	void Set_Speed(float _fSpeed) { m_fSpeed = _fSpeed; }
	void Set_Position(float _fX, float _fY) { m_tInfo.fX = _fX; m_tInfo.fY = _fY; }
	void Set_Scale(float _fCX, float _fCY) { m_tInfo.fCX = _fCX; m_tInfo.fCY = _fCY; }
	void Set_Obj_Cur_Status(OBJ_STATUS _eObjStatus) { m_eObjCurStatus = _eObjStatus; }
	void Set_Degree(float _fDegree) { m_fDegree = _fDegree; }
	void Set_Obj_Dir(OBJ_DIR _eObjDir) { m_eObjCurDir = _eObjDir; }
	void Set_Frame_Key(TCHAR* _pFrameKey) { m_pFrameKey = _pFrameKey; }
	void Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }
	void Set_Collide_Info(INFO _tInfo) { m_tCollideInfo = _tInfo; }
	void Set_Collide_Pos(float _fCollideFx, float _fCollideFy) { m_tCollideInfo.fX = _fCollideFx; m_tCollideInfo.fY = _fCollideFy; }
	void Set_Enemy_Type(ENEMY_TYPE _eEnemyType) { m_eEnemyType = _eEnemyType; }
	void Set_Start_Walk_Pos(float _fStartWalkPos) { m_fStartWalkPos = _fStartWalkPos; }
	void Set_End_Walk_Pos(float _fEndWalkPos) { m_fEndWalkPos = _fEndWalkPos; }
	void Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void Set_Collide_Rect(RECT _tCollideRect) { m_tCollideRect = _tCollideRect; }

	void Set_Normal_Vec(Vec2 _vNormalVec) { m_vNormalVec = _vNormalVec; }
	void Set_Rect(RECT _tRect) { m_tRect = _tRect; }
	void Set_RenderRect(RECT _tRect) { m_tRect = _tRect; }

	void Set_Attack_Type(ATTACK_TYPE _eAttackType) { m_eAttackType = _eAttackType; }
	void Set_Blind(bool _bBlind) { m_bBlind = _bBlind; }
	void Set_Info(INFO _tInfo) { m_tInfo = _tInfo; }
	void Set_KnockBack(float _fX) { m_tInfo.fX += _fX; }

	RECT Get_Collide_Rect() { return m_tCollideRect; }


	list<AFTER_IMAGE_INFO>* Get_After_Image_Info()
	{
		return &m_pAfterImageList;
	}

public:
	void Push_Out_Wall(float _fX)
	{
		switch (m_eObjCurDir)
		{
		case OBJ_DIR::LEFT:
		{
			m_tInfo.fX -= _fX;
			m_tRect.left -= _fX;
			m_tRect.right -= _fX;
			m_tRenderRect.left -= _fX;
			m_tRenderRect.right -= _fX;
			m_tCollideRect.left -= _fX;
			m_tCollideRect.right -= _fX;
			

			break;
		}
		case OBJ_DIR::RIGHT:
		{
			m_tInfo.fX += _fX;
			m_tRect.left += _fX;
			m_tRect.right += _fX;
			m_tRenderRect.left += _fX;
			m_tRenderRect.right += _fX;
			m_tCollideRect.left += _fX;
			m_tCollideRect.right += _fX;

			break;
		}
		}
	}

public:
	void Set_Wall_Grab() 
	{ 
		m_eObjPreStatus = m_eObjCurStatus;
		m_eObjCurStatus = OBJ_STATUS::WALL_GRAB;
		switch (m_eObjCurDir)
		{
		case OBJ_DIR::LEFT:
		{
			m_eObjPreDir = m_eObjCurDir;
			m_eObjCurDir = OBJ_DIR::RIGHT;
			break;
		}
		case OBJ_DIR::RIGHT:
		{
			m_eObjPreDir = m_eObjCurDir;
			m_eObjCurDir = OBJ_DIR::LEFT;
			break;
		}
		}
	}

	void Set_Thunder_Breathing_Death()
	{
		m_bThunderBreathingDeath = true;
		m_dwThunderBreathingDeath = GetTickCount();
	}

protected:
	void Update_Rect();
	void Update_Render_Rect();
	void Update_Collide_Rect();
	void Update_Attack_Rect();
	void Update_Player_Attack_Rect();
	void Update_Collide_Rect_Using_Info();


	void Move_Frame();
	void Move_Reverse_Frame(int _initFrame);

	void Update_Ray_Rect();

protected:
	void Store_After_Image(
		float _fCX,
		float _fCY,
		int _iFrameStart,
		int _iMotion,
		TCHAR* _pFrameKey
	);

	void Check_Delete_After_Image();

	void Clear_All_After_Images();

	

protected:
	bool m_bDead;
	float m_fDegree;
	float m_fAngle; // Theta
	float m_fSpeed;
	float m_fPower;
	float m_fJumpLeftRightSpeed;
	float m_fFlipSpeed;

	float m_fJumpTime;
	float m_fBeforeY;

	OBJ_DIR m_eObjPreDir;
	OBJ_DIR m_eObjCurDir;

	OBJ_STATUS m_eObjPreStatus;
	OBJ_STATUS m_eObjCurStatus;

	



	FRAME m_tFrame;
	INFO m_tInfo;
	RECT m_tRect;
	TCHAR* m_pFrameKey;

	INFO m_tCollideInfo;
	RECT m_tCollideRect;

	// Render Coordinates
	RECT m_tRenderRect;
	
	// ÀÜ»ó¿ë
	DWORD m_dwAfterImageTime;
	list<AFTER_IMAGE_INFO> m_pAfterImageList;

	float m_fAttackAreaHeight = 1.f;
	float m_fAttackRadius;
	RECT m_tAttackAreaRect;
	RECT m_tAttackAreaRenderRect;
	
	
	// Enemy Chase
	CObj* m_pTarget;
	float m_fRayRadius;
	RECT m_tRayRect; // »ç¿ë O
	RECT m_tRayRenderRect; // For Rendering


	// Enemy Walk
	float m_fStartWalkPos;
	float m_fEndWalkPos;
	
	ENEMY_TYPE m_eEnemyType;

	// Bullet
	Vec2 m_vNormalVec;

	INFO m_tItemPickInfo;
	RECT m_tItemPickRect;

	// Player Attack
	float m_fPlayerAttackSpeed = 2.f;
	
	// Blood
	ATTACK_TYPE m_eAttackType = ATTACK_TYPE::ATTACK_TYPE_END;

	// blind for door or etc
	bool m_bBlind = true;


	bool m_bDamageable = false;

	bool m_bThunderBreathingDeath = false;
	DWORD m_dwThunderBreathingDeath = 0;
};

