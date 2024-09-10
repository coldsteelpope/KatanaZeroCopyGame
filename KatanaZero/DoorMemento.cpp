#include "pch.h"
#include "DoorMemento.h"

CDoorMemento::CDoorMemento()
{
}

CDoorMemento::CDoorMemento(FRAME _tFrame, TCHAR* _pFrameKey, RECT _tRect, INFO _tInfo, OBJ_DIR _eObjDir, LONG64 _llFrameCount)
{
	m_tFrame = _tFrame;
	m_pFrameKey = _pFrameKey;
	m_tInfo = _tInfo;
	m_eObjDir = _eObjDir;
	m_tRect = _tRect;
	m_llFrameCount = _llFrameCount;
}

CDoorMemento::~CDoorMemento()
{
}
