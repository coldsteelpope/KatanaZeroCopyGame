#pragma once
class CTimeSlowMgr
{
private:
	CTimeSlowMgr() : m_iRatio(1), dw_Power_Increase_Time(GetTickCount()), dw_Power_Decrease_Time(GetTickCount()), dw_Power_Stun_Time(GetTickCount()) {}
	~CTimeSlowMgr() {}

public:

	void Set_Slow_Interval_Time()
	{
		m_iSlowInterval = 200;
	}

	void Set_Normal_Interval_Time()
	{
		m_iSlowInterval = 0;
		m_bJustSlowTime = false;
	}

	void Slow_Time() 
	{ 
		m_iRatio = 5;
		m_bSlowTime = true;
	}
	
	void Normal_Time() 
	{ 
		m_iRatio = 1;
		m_bSlowTime = false;
	}

	int Get_Ratio() { return m_iRatio; }
	int Get_Slow_Interval() { return m_iSlowInterval; }

	bool Get_Slow_Time() { return m_bSlowTime; }
	bool Get_Just_Slow_Time() { return m_bJustSlowTime; }
	
	int Get_Power() { return m_iPower; }
	void Update()
	{
		if (m_bSlowTime)
		{
			if (dw_Power_Decrease_Time + 1000 < GetTickCount())
			{
				if (m_iPower > 0)
				{
					m_iPower -= 10;
				}
				dw_Power_Decrease_Time = GetTickCount();
			}
		}
		else
		{
			if (dw_Power_Increase_Time + 1000 < GetTickCount())
			{
				if (m_iPower < 100)
				{
					m_iPower += 10;
				}
				dw_Power_Increase_Time = GetTickCount();
			}
		}	
	}

	void Late_Update()
	{
		if (m_iPower <= 0)
		{
			m_iPower = 0;
			m_iRatio = 1;
			m_bSlowTime = false;
			dw_Power_Stun_Time = GetTickCount();
		}
	}
public:
	static CTimeSlowMgr* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CTimeSlowMgr;
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
	static CTimeSlowMgr* m_pInstance;
	bool m_bSlowTime = false;
	bool m_bJustSlowTime = false;
	int m_iSlowInterval = 0;

	int m_iRatio;

	
	int m_iPower = 100;
	DWORD dw_Power_Decrease_Time;
	DWORD dw_Power_Increase_Time;
	DWORD dw_Power_Stun_Time;
};

