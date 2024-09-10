#include "pch.h"
#include "BulletMemento.h"

CBulletMemento::CBulletMemento()
{
}

CBulletMemento::CBulletMemento(FRAME _tFrame, TCHAR* _pFrameKey, RECT _tRect, INFO _tInfo, OBJ_DIR _eObjDir, LONG64 _llFrameCount)
{
	m_tFrame = _tFrame;
	m_pFrameKey = _pFrameKey;
	m_tInfo = _tInfo;
	m_eObjDir = _eObjDir;
	m_tRect = _tRect;
	m_llFrameCount = _llFrameCount;
}

CBulletMemento::~CBulletMemento()
{
}
