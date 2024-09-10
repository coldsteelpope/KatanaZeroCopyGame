#pragma once

class CObj;
class CUIMgr
{
private:
	CUIMgr();
	virtual ~CUIMgr();

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC _hDC);
	void Release();

	void Set_Player(CObj* _pPlayer)
	{
		m_pPlayer = _pPlayer;
	}

public:
	static CUIMgr* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CUIMgr;
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
	static CUIMgr* m_pInstance;
	CObj* m_pPlayer = nullptr;
	int m_iBatteryCharge = 10;
	ITEM_TYPE m_eItemType = ITEM_TYPE_END;
};

