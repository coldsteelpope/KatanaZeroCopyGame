#pragma once

#include "BmpMgr.h"
#include "EffectCareTaker.h"

class CMemento
{
public:
	CMemento();
	CMemento(FRAME _tFrame, TCHAR* _pFrameKey, RECT _tRect, INFO _tInfo, OBJ_DIR _eObjDir, LONG64 m_llFrameCount);
	~CMemento();

public:
	// Print Memento
	void Print_Memento(HDC _hDC)
	{
		HDC hCurrentDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey, m_eObjDir);
		if (true)
		{
			if (
				lstrcmp(L"Effect_Dragon_Attack", m_pFrameKey) == 0
				)
			{
				GdiTransparentBlt(
					_hDC,
					m_tRect.left,
					m_tRect.top,
					m_tInfo.fCX,
					m_tInfo.fCY,
					hCurrentDC,
					(int)m_tInfo.fCX * m_tFrame.iFrameStart,
					(int)m_tInfo.fCY * m_tFrame.iMotion,
					(int)m_tInfo.fCX,
					(int)m_tInfo.fCY,
					RGB(254, 0, 254)
				);
			}
			else
			{
				GdiTransparentBlt(
					_hDC,
					m_tRect.left,
					m_tRect.top,
					m_tInfo.fCX,
					m_tInfo.fCY,
					hCurrentDC,
					(int)m_tInfo.fCX * m_tFrame.iFrameStart,
					(int)m_tInfo.fCY * m_tFrame.iMotion,
					(int)m_tInfo.fCX,
					(int)m_tInfo.fCY,
					RGB(255, 0, 255)
				);
			}
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