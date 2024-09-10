#pragma once

class CObj;
class CScene abstract
{
public:
	CScene();
	virtual ~CScene();
public:
	virtual void Initialize() PURE;
	virtual int Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render(HDC _hDC) PURE;
	virtual void Release() PURE;

public:

	bool Get_Highlight_Event() { return m_bHighlightEvent; }
	void Set_Highlight_Event(bool _bEvent) { m_bHighlightEvent = _bEvent; }
	void Set_Highlight_Target_Pos(float _fX, float _fY) { m_Highlight_Target_fX = _fX; m_Highlight_Target_fY = _fY; }
	void Set_Highlight_Target(CObj* _pTarget) { m_pHighlightTarget = _pTarget; }

	void Set_BackgroundMusic(TCHAR* _pName) { backgroundMusic = _pName; }

public:

	TCHAR* Get_Background_Music() { return backgroundMusic; }
	void Set_Rewind(bool _bRewind)
	{
		m_bRewind = _bRewind;
	}

protected:
	bool m_bRewind;
	LONG64 m_llFrameCount = 0;

	bool m_bHighlightEvent = false;
	CObj* m_pHighlightTarget = nullptr;

	float m_Highlight_Target_fX = 0.f;
	float m_Highlight_Target_fY = 0.f;

	bool m_bBattleEvent = false;
	TCHAR* backgroundMusic;
};

