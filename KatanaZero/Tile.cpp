#include "pch.h"
#include "Tile.h"
#include "BmpMgr.h"
#include "Obj.h"
#include "ScrollMgr.h"

// 0: 벽타기가 불가능한 벽
// 1: 벽타기가 가능한 벽

CTile::CTile() : m_iDrawID(TILE_END), m_iOption(TILE_END)
{

}

CTile::~CTile()
{
	Release();
}

void CTile::Initialize()
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	m_pFrameKey = L"Tile";
}

int CTile::Update()
{
	CObj::Update_Rect();
	CObj::Update_Render_Rect();
	return OBJ_NO_EVENT;
}

void CTile::Late_Update()
{

}

void CTile::Render(HDC _hDC)
{
	switch (m_iOption)
	{
	case TILE_TYPE::SOLID_WALL_TILE:
	{
		HBRUSH redBrush = (HBRUSH)::CreateSolidBrush(RGB(255, 0, 0));
		HBRUSH oldBrush = (HBRUSH)::SelectObject(_hDC, redBrush);
		::Rectangle(_hDC, m_tRenderRect.left, m_tRenderRect.top, m_tRenderRect.right, m_tRenderRect.bottom);
		::SelectObject(_hDC, oldBrush);
		::DeleteObject(redBrush);

		break;
	}
	case TILE_TYPE::CLIMB_WALL_TILE:
	{
		HBRUSH blueBrush = (HBRUSH)::CreateSolidBrush(RGB(0, 255, 0));
		HBRUSH oldBrush = (HBRUSH)::SelectObject(_hDC, blueBrush);
		::Rectangle(_hDC, m_tRenderRect.left, m_tRenderRect.top, m_tRenderRect.right, m_tRenderRect.bottom);
		::SelectObject(_hDC, oldBrush);
		::DeleteObject(blueBrush);

		break;
	}
	}
}

void CTile::Release()
{
}
