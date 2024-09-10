#pragma once

#include "BmpMgr.h"
class CDoorMemento
{
public:
	CDoorMemento();
	CDoorMemento(FRAME _tFrame, TCHAR* _pFrameKey, RECT _tRect, INFO _tInfo, OBJ_DIR _eObjDir, LONG64 m_llFrameCount);
	~CDoorMemento();

public:
	void Print_Memento(HDC _hDC)
	{
		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/door/DOOR_LEFT.bmp", L"DOOR", OBJ_DIR::LEFT);
		HDC hCurrentDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey, m_eObjDir);

		GdiTransparentBlt(
			_hDC,
			m_tRect.left,
			m_tRect.top,
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hCurrentDC,
			(int)m_tInfo.fCX * m_tFrame.iFrameStart,
			(int)m_tInfo.fCY * m_tFrame.iMotion,
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

