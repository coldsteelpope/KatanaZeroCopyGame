#pragma once

class CLine;
class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	void Initialize();
	int Update();
	void Late_Update();
	void Render(HDC _hDC);
	void Release();
public:
	CLine* Get_Current_Line() { return m_pCurrentLine; }
	bool Collision_Line(float _fX, float _fSpeed, float _fFoot, float _fCY, float* pY, OBJ_STATUS _eObjStatus);

	bool Collision_Line_Enemy(float _fX, float _fSpeed, float _fFoot, float _fCY, float* pY, OBJ_STATUS _eObjStatus);


	void Save_Line();
	void Load_Line();

	void Key_Input();
public:
	static CLineMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CLineMgr;

		return m_pInstance;
	}

	static void		Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static CLineMgr* m_pInstance;
	CLine* m_pCurrentLine = nullptr;
	list<CLine*> m_LineList;
	LINEPOINT m_tLinePoint[MOUSE_DIRECTION::MOUSE_DIRECTION_END];
	
	bool m_bEditMode = false;
	LINE_TYPE m_eDrawLineType = LINE_TYPE::SOLID;
};

