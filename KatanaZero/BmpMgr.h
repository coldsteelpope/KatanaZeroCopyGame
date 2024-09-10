#pragma once

class CMyBmp;
class CBmpMgr
{
public:
	enum BMP_TYPE
	{
		LEFT_BMP_TYPE,
		RIGHT_BMP_TYPE,
		BMP_TYPE_END
	};

private:
	CBmpMgr();
	~CBmpMgr();

public:
	void Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey);
	void Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey, OBJ_DIR _eObjDir);
	
	HDC Find_Img(const TCHAR* pImgKey);
	HDC Find_Img(const TCHAR* PImgKey, OBJ_DIR _eObjDir);
	void Release();

public:
	static CBmpMgr* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CBmpMgr;
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
	static CBmpMgr* m_pInstance;
	map<const TCHAR*, CMyBmp*> m_mapBit;
	map<const TCHAR*, CMyBmp*> m_mapBitLeft;
	map<const TCHAR*, CMyBmp*> m_mapBitRight;
};

