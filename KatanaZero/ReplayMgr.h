#pragma once

class CMemento;
class CItemMemento;
class CEnemyMemento;
class CCameraMemento;

class CReplayMgr
{

private:
	CReplayMgr();
	~CReplayMgr();

public:
	static CReplayMgr* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CReplayMgr;
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

public:
	LONG Get_Full_Frame()
	{
		return m_llFullFrame;
	}

	float Get_Replay_Ratio()
	{
		return m_fReplayRatio;
	}
	
	void Set_Full_Frame(LONG _llFullFrame)
	{
		m_llFullFrame = _llFullFrame;
	}

	void Set_Replay_Ratio(float _fReplayRatio)
	{
		m_fReplayRatio = _fReplayRatio;
	}

	void Set_Scene_Width(int _iWidth) { m_iSceneWidth = _iWidth; }
	void Set_Scene_Height(int _iHeight) { m_iSceneHeight = _iHeight; }
	
	int Get_Scene_Width() { return m_iSceneWidth; }
	int Get_Scene_Height() { return m_iSceneHeight; }

	void Copy_Player_Mementos();
	void Copy_Effect_Mementos();
	void Copy_Camera_Mementos();
	void Copy_Enemy_Mementos();
	void Copy_Item_Mementos();
	
	void Release();


private:
	static CReplayMgr* m_pInstance;
	LONG m_llFullFrame;
	float m_fReplayRatio = 1.0f;

	
	int m_iSceneWidth;
	int m_iSceneHeight;

	deque<CMemento*> m_vPlayerMementos;
	deque<CCameraMemento*> m_vCameraMementos;
	deque<CMemento*> m_vEffectMementos;
	deque<CEnemyMemento*> m_vEnemyMementos;
	deque<CItemMemento*> m_vItemMementos;
};

