#pragma once

#include "Obj.h"
class CMouse;
class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();
public:
	// CObj을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

public:
	void Set_Player_Mouse(CMouse* _pMouse) { m_pPlayerMouse = _pMouse; }

	void Jump();


	void Set_Inventory(ITEM_TYPE _eItemType) { m_bInventory[_eItemType] = true; }

	bool Get_No_Death() { return m_bNodeath; }

	void Set_No_Death() { m_bNodeath = true; }

private:
	void Motion_Change();

	void Key_Input();

	void Left_Key_Input();

	void Right_Key_Input();

	void Down_Key_Input();

	void Up_Key_Input();

	void Manage_Status();

	void LButton_Key_Input();

	void LShift_Key_Input();

	void Q_Key_Input();

	bool R_Key_Button_Key_Input();

	void RButton_Key_Input();

	void Item_Key_Input();

	void N_Key_Input();

	void Thunder_Breathing_Manage_Status();

private:
	void Move_Run_Effect_Frame();


	void Update_Player_Collide()
	{
		Vec2 realPos = CCamera::Get_Instance()->GetRealPos(Vec2{ m_tInfo.fX, m_tInfo.fY });
		m_tPlayerCollideInfo.fX = m_tInfo.fX;
		m_tPlayerCollideInfo.fY = m_tInfo.fY;
		m_tPlayerCollideInfo.fCX = m_tInfo.fCX;
		m_tPlayerCollideInfo.fCY = m_tInfo.fCY;

		m_tPlayerCollideRect.left = (long)(m_tPlayerCollideInfo.fX - PLAYER_IDLE_FCX / 2.0f);
		m_tPlayerCollideRect.top = (long)(m_tPlayerCollideInfo.fY - PLAYER_IDLE_FCY / 2.0f);
		m_tPlayerCollideRect.right = (long)(m_tPlayerCollideInfo.fX + PLAYER_IDLE_FCX / 2.0f);
		m_tPlayerCollideRect.bottom = (long)(m_tPlayerCollideInfo.fY + PLAYER_IDLE_FCY / 2.0f);

		
		
	}

public:
	bool m_bInventory[ITEM_TYPE_END] = { 0, };
private:
	CMouse* m_pPlayerMouse;
	bool m_bPlayerItemMode = false;


	FRAME m_tRunEffectFrame;
	bool m_bRunEffectActive = false;

	bool m_bThunderBreathingCheck = false;

	
	bool m_bThunderBreathing = false;
	float m_fThunderBreathingX0 = 0.f;
	float m_fThunderBreathingY0 = 0.f;
	float m_fThunderBreathingX1 = 0.f;
	float m_fThunderBreathingY1 = 0.f;
	float m_fThunderBreathingScope = 0.f;
	float m_fThunderBreathingSpeed = 35.f;

	
	// for slash
	float m_fMyInitPosX;
	float m_fMyInitPosY;
	float m_fSlashTargetX;
	float m_fSlashTargetY;
	OBJ_DIR m_eSlashDir = OBJ_DIR_END;
	OBJ_TOP_DOWN_STATUS m_eSlashTopDown = OBJ_TOP_DOWN_STATUS::TOP_DOWN_STATUS;



	INFO m_tPlayerCollideInfo;
	RECT m_tPlayerCollideRect;

	bool m_bPlayerLayDown = false;
	bool m_bNodeath = false;

	DWORD m_dwWaitingTime = 0;
	float m_fSlashSpeed = 10.f;
	
	float m_fSlashTime = 0.f;
};

