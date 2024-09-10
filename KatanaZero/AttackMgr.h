#pragma once


class CAttackMgr
{
public:
	CAttackMgr();
	virtual ~CAttackMgr();

public:
	bool Is_Attack_Time()
	{
		return m_bAttackTime;
	}

	void Set_Attack_Time()
	{
		if (m_bAttackTime == false)
		{
			m_bAttackTime = true;
			m_dwAttackTime = GetTickCount();
		}
		
	}

	void Update_Attack_Time()
	{
		if (m_dwAttackTime + 200 < GetTickCount())
		{
			m_bAttackTime = false;
		}
	}

public:
	static CAttackMgr* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CAttackMgr;
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
	static CAttackMgr* m_pInstance;
	bool m_bAttackTime = false;
	DWORD m_dwAttackTime = 0.f;
};

