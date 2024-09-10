#pragma once

#include "BmpMgr.h"

class CItemMemento
{
public:
	CItemMemento();
	CItemMemento(FRAME _tFrame, TCHAR* _pFrameKey, RECT _tRect, INFO _tInfo, OBJ_DIR _eObjDir, LONG64 m_llFrameCount);
	~CItemMemento();

public:
	void Print_Memento(HDC _hDC)
	{
		HDC hCurrentDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

		if (lstrcmp(L"EXPLOSIVE", m_pFrameKey) == 0)
		{
			GdiTransparentBlt(
				_hDC,
				m_tRect.left,
				m_tRect.top,
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY,
				hCurrentDC,
				(int)m_tInfo.fCX * m_tFrame.iFrameStart,
				(int)m_tInfo.fCY * m_tFrame.iMotion,
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY,
				RGB(255, 0, 255)
			);
		}
		else
		{
			GdiTransparentBlt(
				_hDC,
				m_tRect.left,
				m_tRect.top,
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY,
				hCurrentDC,
				(int)m_tInfo.fCX * m_tFrame.iFrameStart,
				(int)m_tInfo.fCY * m_tFrame.iMotion,
				(int)m_tInfo.fCX,
				(int)m_tInfo.fCY,
				RGB(254, 6, 254)
			);
		}

	}

public:
	TCHAR* Get_Frame_Key() { return m_pFrameKey; }
	FRAME Get_Frame() { return m_tFrame; }
	LONG64 Get_Frame_Count() { return m_llFrameCount; }

private:
	RECT m_tRect;
	FRAME m_tFrame;
	TCHAR* m_pFrameKey;
	INFO m_tInfo;
	OBJ_DIR m_eObjDir;
	LONG64 m_llFrameCount;

};

