#pragma once
class CObj;
class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	
public:
	list<CObj*> Get_Object_List(OBJ_ID _eID);
	void Add_Object(OBJ_ID _eID, CObj* _pObj);
	void Update();
	void Late_Update();
	void Render(HDC _hDC);
	void Release();
	void Clear_All_Object_List();

public:
	static CObjMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;

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
	list<CObj*>		m_ObjList[OBJ_ID_END];
	static CObjMgr* m_pInstance;
};

