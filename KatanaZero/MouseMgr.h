#pragma once

class CObj;
class CMouseMgr
{
private:
	CMouseMgr();
	~CMouseMgr();

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC _hDC);
	void Release();

	POINT Get_Mouse_Pos() { return m_tMousePos; }
	void Set_Thunder_Breathing_Mode(bool _bOpen) { m_bThunderBreathing = _bOpen; }
	void Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }

public:
	static CMouseMgr* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CMouseMgr;
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
	static CMouseMgr* m_pInstance;
	POINT m_tMousePos;

	CObj* m_pTarget = nullptr;
	bool m_bThunderBreathing = false;
};

