#pragma once
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render();
	void Release();

private:
	HDC			m_DC;
	DWORD		m_dwTime;
	int			m_iFps;
	TCHAR		m_szFPS[32];
};

