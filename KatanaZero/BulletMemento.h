#pragma once

#include "BmpMgr.h"
class CBulletMemento
{
public:
	CBulletMemento();
	CBulletMemento(FRAME _tFrame, TCHAR* _pFrameKey, RECT _tRect, INFO _tInfo, OBJ_DIR _eObjDir, LONG64 m_llFrameCount);
	~CBulletMemento();

public:
	void Print_Memento(HDC _hDC)
	{
		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/bullet/bullet.bmp", L"BULLET");
		HDC hCurrentDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);
		GdiTransparentBlt(
			_hDC,
			m_tRect.left,
			m_tRect.top,
			m_tInfo.fCX,
			m_tInfo.fCY,
			hCurrentDC,
			0, 0,
			m_tInfo.fCX,
			m_tInfo.fCY,
			RGB(255, 0, 255)
		);
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

