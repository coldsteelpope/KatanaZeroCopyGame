#pragma once
class CScene;
class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();
public:
	int Update();
	void Late_Update();
	void Render(HDC _hDC);
	void Release();

	void Change_Scene(SCENE_ID _eScene);
	void Renew_Scene(SCENE_ID _eScene);

	SCENE_ID Get_Cur_Scene_ID() { return m_eCurScene; }
	SCENE_ID Get_Prev_Scene_ID() { return m_ePreScene;  }

	CScene* Get_Active_Scene() { return m_pActiveScene; }

public:
	static CSceneMgr* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CSceneMgr;
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
	static CSceneMgr* m_pInstance;
	CScene* m_pActiveScene;

	SCENE_ID m_ePreScene;
	SCENE_ID m_eCurScene;
};

