#include "pch.h"
#include "Mouse.h"

CMouse::CMouse()
{
	ZeroMemory(&m_tMousePos, sizeof(POINT));
}

CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize()
{
	::GetCursorPos(&m_tMousePos);
	::ScreenToClient(g_hWnd, &m_tMousePos);
}

int CMouse::Update()
{
	::GetCursorPos(&m_tMousePos);
	::ScreenToClient(g_hWnd, &m_tMousePos);


	return OBJ_NO_EVENT;
}

void CMouse::Late_Update()
{

}

void CMouse::Render(HDC _hDC)
{
	int iCurrentX = m_tMousePos.x;
	int iCurrentY = m_tMousePos.y;
	
}

void CMouse::Release()
{
}
