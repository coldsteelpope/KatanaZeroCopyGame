#pragma once

#include "Obj.h"
class CBoss2 : public CObj
{
public:
	enum BOSS_2_STAGE_PATTERN
	{
		BOSS_ATTACKED,
		BOSS_IDLE_PATTERN,
		BOSS_PATTERN_1, // 레이저
		BOSS_PATTERN_2, // 점막 폭탄
		BOSS_PATTERN_3 // 게틀링건
	};

	enum BOSS_PATTERN_3_DETAIL
	{
		BOSS_PATTERN_3_IN,
		BOSS_JUMP_LEFT,
		BOSS_JUMP_RIGHT,
		BOSS_JUMP_WALL_GRAB_LEFT,
		BOSS_JUMP_WALL_GRAB_RIGHT,
		BOSS_WALL_JUMP_LEFT,
		BOSS_WALL_JUMP_RIGHT,
		BOSS_WALL_FALL_LEFT,
		BOSS_WALL_FALL_RIGHT,
		BOSS_WALL_LANDING_LEFT,
		BOSS_WALL_LANDING_RIGHT,
		BOSS_PATTERN_3_DETAIL_END
	};


	enum BOSS_PATTERN_2_DETAIL
	{
		BOSS_PATTERN_2_IN,
		TAKE_OUT_GUN_LEFT,
		SHOOT_GUN_LEFT,
		TAKE_OUT_GUN_RIGHT,
		SHOOT_GUN_RIGHT,
		BOSS_PATTERN_2_OUT_OF_PATTERN,
		BOSS_PATTERN_2_END
	};

	enum BOSS_PATTERN_1_DETAIL
	{
		TOP_LEFT_1_START,
		TOP_LEFT_1_END,

		TOP_LEFT_2_START,
		TOP_LEFT_2_END,

		TOP_RIGHT_1_START,
		TOP_RIGHT_1_END,

		TOP_RIGHT_2_START,
		TOP_RIGHT_2_END,

		GROUND_LEFT_SHOT_START,
		GROUND_LEFT_SHOT_END,

		GROUND_RIGHT_SHOT_START,
		GROUND_RIGHT_SHOT_END,
		
		LEFT_SWEEP_SHOT_START,
		LEFT_SWEEP_SHOT_END,

		RIGHT_SWEEP_SHOT_START,
		RIGHT_SWEEP_SHOT_END,
		
		BOSS_PATTERN_1_END,
	};

public:
	CBoss2();
	virtual ~CBoss2();

public:
	

	// CObj을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

	float Get_Jump_Time() { return m_fJumpTime; }
	void Set_Jump_Time(float _fJumpTime) { m_fJumpTime = _fJumpTime; }
	void Set_Grab_Time() { m_dwGrabTime = GetTickCount(); }
	BOSS_STATUS Get_Boss_Cur_Status() { return m_eBossCurStatus; }
	BOSS_PATTERN_3_DETAIL Get_Boss_Pattern_3_Detail() { return m_eBossPatternThreeDetail; }
	void Set_Boss_Pattern_3_Detail(BOSS_PATTERN_3_DETAIL _eBossPattern3) { m_eBossPatternThreeDetail = _eBossPattern3; }
	void Set_Start() { m_bStart = true; }
	void Set_Cur_Boss_Status(BOSS_STATUS _bossStatus) { m_eBossCurStatus = _bossStatus; }
	void Set_DeadScene() { m_bDeadScene = true; }

private:
	void Motion_Change();
	void Manage_Status();

	void Update_Collide_Rect_For_Boss2();
	void Manage_Pattern();
	void Jump();
	void Pattern_One();
	void Pattern_Two();
	void Pattern_Three();
	void All_Frame_Works();
	
	void Manage_Dead_Status();
	void All_Dead_Frame_Works();

private:
	

private:
	int m_iBossHp = 4;
	float m_fAngle;
	
	BOSS_STATUS m_eBossCurStatus = BOSS_STATUS::BOSS_IDLE_LEFT;
	BOSS_STATUS m_eBossPreStatus = BOSS_STATUS::BOSS_STATUS_END;
	BOSS_2_STAGE_PATTERN m_eCurrentPattern = BOSS_2_STAGE_PATTERN::BOSS_IDLE_PATTERN;

	BOSS_PATTERN_1_DETAIL m_eBossPatternOneDetail = BOSS_PATTERN_1_DETAIL::BOSS_PATTERN_1_END;
	BOSS_PATTERN_2_DETAIL m_eBossPatternTwoDetail = BOSS_PATTERN_2_DETAIL::BOSS_PATTERN_2_END;
	BOSS_PATTERN_3_DETAIL m_eBossPatternThreeDetail = BOSS_PATTERN_3_DETAIL::BOSS_PATTERN_3_DETAIL_END;

	// 예시
	POINT m_tPoint[3];
	int m_iFireNumber = 0;
	int m_iBeforeFrame = -1;
	float m_fJumpTime = 0.f;
	float m_fBossBulletAngle = -PI / 2.0f;

	DWORD m_dwGrabTime;

	bool m_bStart = false;
	bool m_bDeadScene = false;
	bool m_bShootGatling = false;
};

