#pragma once

#include "SoundMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
class CThunderBreathingMgr
{
public:
	CThunderBreathingMgr();
	virtual ~CThunderBreathingMgr();

public:
	void Set_Thunder_Breathing_Mode_Off_Temp()
	{
		m_bThunderBreathingMode = false;
		m_bThunderBreathingScript = false;
	}

	void Set_ThunderBreathing_Mode_Off()
	{
		m_bThunderBreathingMode = false;
		m_bThunderBreathingScript = false;
		m_ePlayerBreathingMotion = PLAYER_THUNDER_BREATHING_MOTION_END;
		CSoundMgr::Get_Instance()->StopAll();
		CSoundMgr::Get_Instance()->PlaySound(CSceneMgr::Get_Instance()->Get_Active_Scene()->Get_Background_Music(), SOUND_BGM, 1.f);
		
	}

	void Set_ThunderBreathing_Mode()
	{
		m_bThunderBreathingMode = true;
		m_ePlayerBreathingMotion = PLAYER_IDLE_TO_CROUCH;
	}


	bool Get_ThunderBreathing_Mode()
	{
		return m_bThunderBreathingMode;
	}

	DWORD Get_ScriptTime()
	{
		return m_dwScriptSayTime;
	}

	PLAYER_THUNDER_BREATHING_MOTION Get_Player_Thunder_Breathing_Motion()
	{
		return m_ePlayerBreathingMotion;
	}

	void Set_Say_Script()
	{
		if (m_bThunderBreathingScript == false)
		{
			CSoundMgr::Get_Instance()->StopAll();

			CSoundMgr::Get_Instance()->PlaySound(L"thunderBreathing.wav", SOUND_BGM, 1.f);
			


			m_dwScriptSayTime = GetTickCount();

			m_bThunderBreathingScript = true;
		}
	}

	void Set_Player_Thunder_Breathing_Motion(PLAYER_THUNDER_BREATHING_MOTION _eThunderBreathingMotion)
	{
		m_ePlayerBreathingMotion = _eThunderBreathingMotion;
	}

	void Set_Thunder_Breathing_Info(
		float _fThunderBreathingX0,
		float _fThunderBreathingX1,
		float _fThunderBreathingY0,
		float _fThunderBreathingY1,
		OBJ_DIR _eObjDir,
		OBJ_TOP_DOWN_STATUS _eObjTopDown
		)
	{
		m_tThunderBreathingInfo.m_fThunderBreathingX0 = _fThunderBreathingX0;
		m_tThunderBreathingInfo.m_fThunderBreathingX1 = _fThunderBreathingX1;
		m_tThunderBreathingInfo.m_fThunderBreathingY0 = _fThunderBreathingY0;
		m_tThunderBreathingInfo.m_fThunderBreathingY1 = _fThunderBreathingY1;
		m_tThunderBreathingInfo.m_fThunderBreathingScope = (
			(m_tThunderBreathingInfo.m_fThunderBreathingY1 - m_tThunderBreathingInfo.m_fThunderBreathingY0) /
			(m_tThunderBreathingInfo.m_fThunderBreathingX1 - m_tThunderBreathingInfo.m_fThunderBreathingX0)
			);
		m_tThunderBreathingInfo.m_eThunderBreathingDir = _eObjDir;
		m_tThunderBreathingInfo.m_eThunderBreathingTopDown = _eObjTopDown;
	}

	THUNDER_BREATHING_INFO Get_Thunder_Breathing_Info()
	{
		return m_tThunderBreathingInfo;
	}

public:
	static CThunderBreathingMgr* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CThunderBreathingMgr;
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
	static CThunderBreathingMgr* m_pInstance;
	PLAYER_THUNDER_BREATHING_MOTION m_ePlayerBreathingMotion = PLAYER_THUNDER_BREATHING_MOTION_END;
	
	bool m_bThunderBreathingMode = false;
	bool m_bThunderBreathingScript = false;

	THUNDER_BREATHING_INFO m_tThunderBreathingInfo;

	DWORD m_dwScriptSayTime = 0;
};

