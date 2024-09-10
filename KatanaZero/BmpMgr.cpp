#include "pch.h"
#include "BmpMgr.h"
#include "MyBmp.h"

CBmpMgr* CBmpMgr::m_pInstance = nullptr;

CBmpMgr::CBmpMgr()
{
}

CBmpMgr::~CBmpMgr()
{
	Release();
}

void CBmpMgr::Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey)
{
	auto iter = find_if(m_mapBit.begin(), m_mapBit.end(), [&](auto& MyPair)->bool {
		if (!lstrcmp(MyPair.first, pImgKey))
		{
			return true;
		}
		return false;
		});

	if (iter == m_mapBit.end())
	{
		CMyBmp* pBmp = new CMyBmp;
		pBmp->Load_Bmp(pFilePath);
		m_mapBit.emplace(pImgKey, pBmp);
	}
}

void CBmpMgr::Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey, OBJ_DIR _eObjDir)
{
	switch (_eObjDir)
	{
	case OBJ_DIR::LEFT:
	{
		auto iter = find_if(m_mapBitLeft.begin(), m_mapBitLeft.end(), [&](auto& MyPair)->bool {
			if (!lstrcmp(MyPair.first, pImgKey))
			{
				return true;
			}
			return false;
			});

		if (iter == m_mapBitLeft.end())
		{
			CMyBmp* pBmp = new CMyBmp;
			pBmp->Load_Bmp(pFilePath);
			m_mapBitLeft.emplace(pImgKey, pBmp);
		}
		break;
	}
	case OBJ_DIR::RIGHT:
	{
		auto iter = find_if(m_mapBitRight.begin(), m_mapBitRight.end(), [&](auto& MyPair)->bool {
			if (!lstrcmp(MyPair.first, pImgKey))
			{
				return true;
			}
			return false;
			});

		if (iter == m_mapBitRight.end())
		{
			CMyBmp* pBmp = new CMyBmp;
			pBmp->Load_Bmp(pFilePath);
			m_mapBitRight.emplace(pImgKey, pBmp);
		}
		break;
	}
	}

}

HDC CBmpMgr::Find_Img(const TCHAR* pImgKey)
{
	auto iter = find_if(m_mapBit.begin(), m_mapBit.end(), [&](auto& MyPair)->bool {
		if (!lstrcmp(MyPair.first, pImgKey))
		{
			return true;
		}
		return false;
		});


	if (iter == m_mapBit.end())
	{
		return nullptr;
	}

	return iter->second->Get_MemDC();
}

HDC CBmpMgr::Find_Img(const TCHAR* PImgKey, OBJ_DIR _eObjDir)
{
	switch (_eObjDir)
	{
	case OBJ_DIR::LEFT:
	{
		auto iter = find_if(m_mapBitLeft.begin(), m_mapBitLeft.end(), [&](auto& MyPair)->bool {
			if (!lstrcmp(MyPair.first, PImgKey))
			{
				return true;
			}
			return false;
			});


		if (iter == m_mapBitLeft.end())
		{
			return nullptr;
		}

		return iter->second->Get_MemDC();
	}
	case OBJ_DIR::RIGHT:
	{
		auto iter = find_if(m_mapBitRight.begin(), m_mapBitRight.end(), [&](auto& MyPair)->bool {
			if (!lstrcmp(MyPair.first, PImgKey))
			{
				return true;
			}
			return false;
			});


		if (iter == m_mapBitRight.end())
		{
			return nullptr;
		}

		return iter->second->Get_MemDC();
	}
	}
}

void CBmpMgr::Release()
{
	for_each(m_mapBit.begin(), m_mapBit.end(), [](auto& MyPair) {
		if (MyPair.second)
		{
			delete MyPair.second;
			MyPair.second = nullptr;
		}
		});

	for_each(m_mapBitLeft.begin(), m_mapBitLeft.end(), [](auto& MyPair) {
		if (MyPair.second)
		{
			delete MyPair.second;
			MyPair.second = nullptr;
		}
		});

	for_each(m_mapBitRight.begin(), m_mapBitRight.end(), [](auto& MyPair) {
		if (MyPair.second)
		{
			delete MyPair.second;
			MyPair.second = nullptr;
		}
		});

	m_mapBit.clear();
	m_mapBitLeft.clear();
	m_mapBitRight.clear();
}
