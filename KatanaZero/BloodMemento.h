#pragma once
#include "BmpMgr.h"
class CBloodMemento
{
public:
	CBloodMemento();
	CBloodMemento(FRAME _tFrame, TCHAR* _pFrameKey, RECT _tRect, INFO _tInfo, OBJ_DIR _eObjDir, LONG64 m_llFrameCount);
	~CBloodMemento();

public:
	void Print_Memento(HDC _hDC)
	{
		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Blood/blood_0_l.bmp", L"Blood_0", OBJ_DIR::LEFT);
		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Blood/blood_0_r.bmp", L"Blood_0", OBJ_DIR::RIGHT);

		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Blood/blood_1_l.bmp", L"Blood_1", OBJ_DIR::LEFT);
		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Blood/blood_1_r.bmp", L"Blood_1", OBJ_DIR::RIGHT);

		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Blood/blood_2_l.bmp", L"Blood_2", OBJ_DIR::LEFT);
		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Blood/blood_2_r.bmp", L"Blood_2", OBJ_DIR::RIGHT);

		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Blood/blood_3_l.bmp", L"Blood_3", OBJ_DIR::LEFT);
		CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Blood/blood_3_r.bmp", L"Blood_3", OBJ_DIR::RIGHT);


		HDC hCurrentDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey, m_eObjDir);
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

