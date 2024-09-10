#pragma once
#include "SoundMgr.h"

class CTimeRewindMgr
{
private:
	CTimeRewindMgr() : m_fRatio(1), m_bRewindTime(false) {};
	~CTimeRewindMgr() {};
public:
	void Rewind_Time() 
	{ 
		m_fRatio = 0.5f; 

	}
	void Normal_Time() { m_fRatio = 1.0f; }
	float Get_Ratio() { return m_fRatio; }
	bool Get_RewindTime() { return m_bRewindTime; }
	void Set_RewindTime(bool _bRewindTime) { m_bRewindTime = _bRewindTime; }
	
public:
	static CTimeRewindMgr* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CTimeRewindMgr;
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
	static CTimeRewindMgr* m_pInstance;
	float m_fRatio;
	bool m_bRewindTime;
};
