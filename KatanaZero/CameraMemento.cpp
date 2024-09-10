#include "pch.h"
#include "CameraMemento.h"

CCameraMemento::CCameraMemento()
{
}

CCameraMemento::CCameraMemento(Vec2 _vLookAt, Vec2 _vPrevLookAt, Vec2 _vDiff, LONG64 _llFrameCount)
	: m_vLookAt(_vLookAt), m_vPrevLookAt(_vPrevLookAt), m_vDiff(_vDiff), m_llFrameCount(_llFrameCount)
{
}

CCameraMemento::~CCameraMemento()
{
	
}
