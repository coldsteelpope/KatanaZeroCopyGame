#include "pch.h"
#include "MouseMgr.h"
#include "TimeSlowMgr.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "Player.h"
#include "Obj.h"
#include "SoundMgr.h"

CMouseMgr* CMouseMgr::m_pInstance = nullptr;

CMouseMgr::CMouseMgr()
{
	ZeroMemory(&m_tMousePos, sizeof(POINT));
}

CMouseMgr::~CMouseMgr()
{
	Release();
}

void CMouseMgr::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/effect/dragon/range/range.bmp", L"Thunder_Breathing_Range");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/effect/dragon/range/range_char_l.bmp", L"Thunder_Breathing_Range_Char", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/effect/dragon/range/range_char_r.bmp", L"Thunder_Breathing_Range_Char", OBJ_DIR::RIGHT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/cursor/mouseCursor.bmp", L"MOUSE_CURSOR");

	::GetCursorPos(&m_tMousePos);
	::ScreenToClient(g_hWnd, &m_tMousePos);
}

void CMouseMgr::Update()
{
	::GetCursorPos(&m_tMousePos);
	::ScreenToClient(g_hWnd, &m_tMousePos);
}

void CMouseMgr::Late_Update()
{
	if (m_bThunderBreathing)
	{
		
	}	
}



void CMouseMgr::Render(HDC _hDC)
{
	ShowCursor(false);
	HDC mouseCursorDC = CBmpMgr::Get_Instance()->Find_Img(L"MOUSE_CURSOR");
	GdiTransparentBlt(
		_hDC,
		m_tMousePos.x,
		m_tMousePos.y,
		25,
		25,
		mouseCursorDC,
		0, 0, 25, 25,
		RGB(255, 0, 255)
	);


	if (m_bThunderBreathing)
	{

		INFO hRangeInfo;

		hRangeInfo.fX = m_pTarget->Get_Info().fX;
		hRangeInfo.fY = m_pTarget->Get_Info().fY;
		hRangeInfo.fCX = RANGE_FCX;
		hRangeInfo.fCY = RANGE_FCY;

		Vec2 hRangeRenderPos = CCamera::Get_Instance()->GetRenderPos(Vec2{ hRangeInfo.fX, hRangeInfo.fY });
		hRangeInfo.fX = hRangeRenderPos.fX;
		hRangeInfo.fY = hRangeRenderPos.fY;

		RECT tRangeRenderRect;
		tRangeRenderRect.left = (hRangeInfo.fX - hRangeInfo.fCX / 2.0f);
		tRangeRenderRect.top = (hRangeInfo.fY - hRangeInfo.fCY / 2.0f);
		tRangeRenderRect.right = (hRangeInfo.fX + hRangeInfo.fCX / 2.0f);
		tRangeRenderRect.bottom = (hRangeInfo.fY + hRangeInfo.fCY / 2.0f);


		Vec2 vecMouseRealPos = CCamera::Get_Instance()->GetRealPos(Vec2{ (float)m_tMousePos.x, (float)m_tMousePos.y });


		float fWidth = vecMouseRealPos.fX - m_pTarget->Get_Info().fX;
		float fHeight = vecMouseRealPos.fY - m_pTarget->Get_Info().fY;
		float fRadius = sqrtf((fWidth * fWidth) + (fHeight * fHeight));

		if (fRadius > 300)
		{

			HDC hCharRangeDC = nullptr;
			if (fWidth > 0)
			{
				hCharRangeDC = CBmpMgr::Get_Instance()->Find_Img(L"Thunder_Breathing_Range_Char", OBJ_DIR::RIGHT);
			}
			else
			{
				hCharRangeDC = CBmpMgr::Get_Instance()->Find_Img(L"Thunder_Breathing_Range_Char", OBJ_DIR::LEFT);
			}

			INFO tCharRangeInfo;
			tCharRangeInfo.fX = m_tMousePos.x;
			tCharRangeInfo.fY = m_tMousePos.y;
			tCharRangeInfo.fCX = RANGE_CHAR_FCX;
			tCharRangeInfo.fCY = RANGE_CHAR_FCY;

			RECT tCharRangeRect;
			tCharRangeRect.left = long(tCharRangeInfo.fX - tCharRangeInfo.fCX / 2.0f);
			tCharRangeRect.top = long(tCharRangeInfo.fY - tCharRangeInfo.fCY / 2.0f);

			HPEN bluePen = ::CreatePen(PS_SOLID, 2, RGB(240, 206, 96));
			HPEN oldPen = (HPEN)::SelectObject(_hDC, bluePen);
			::MoveToEx(_hDC, hRangeInfo.fX, hRangeInfo.fY, nullptr);
			::LineTo(_hDC, m_tMousePos.x, m_tMousePos.y);
			::SelectObject(_hDC, oldPen);
			::DeleteObject(bluePen);

			GdiTransparentBlt(
				_hDC,
				tCharRangeRect.left,
				tCharRangeRect.top,
				RANGE_CHAR_FCX,
				RANGE_CHAR_FCY,
				hCharRangeDC,
				0, 0,
				RANGE_CHAR_FCX,
				RANGE_CHAR_FCY,
				RGB(255, 8, 255)
			);
		}
		else
		{

			HDC hCharRangeDC = nullptr;
			if (fWidth > 0)
			{
				hCharRangeDC = CBmpMgr::Get_Instance()->Find_Img(L"Thunder_Breathing_Range_Char", OBJ_DIR::RIGHT);
			}
			else
			{
				hCharRangeDC = CBmpMgr::Get_Instance()->Find_Img(L"Thunder_Breathing_Range_Char", OBJ_DIR::LEFT);
			}

			INFO tCharRangeInfo;
			tCharRangeInfo.fX = m_tMousePos.x;
			tCharRangeInfo.fY = m_tMousePos.y;
			tCharRangeInfo.fCX = RANGE_CHAR_FCX;
			tCharRangeInfo.fCY = RANGE_CHAR_FCY;

			RECT tCharRangeRect;
			tCharRangeRect.left = long(tCharRangeInfo.fX - tCharRangeInfo.fCX / 2.0f);
			tCharRangeRect.top = long(tCharRangeInfo.fY - tCharRangeInfo.fCY / 2.0f);

			HPEN bluePen = ::CreatePen(PS_SOLID, 2, RGB(179, 224, 255));
			HPEN oldPen = (HPEN)::SelectObject(_hDC, bluePen);
			::MoveToEx(_hDC, hRangeInfo.fX, hRangeInfo.fY, nullptr);
			::LineTo(_hDC, m_tMousePos.x, m_tMousePos.y);
			::SelectObject(_hDC, oldPen);
			::DeleteObject(bluePen);

			GdiTransparentBlt(
				_hDC,
				tCharRangeRect.left,
				tCharRangeRect.top,
				RANGE_CHAR_FCX,
				RANGE_CHAR_FCY,
				hCharRangeDC,
				0, 0,
				RANGE_CHAR_FCX,
				RANGE_CHAR_FCY,
				RGB(255, 8, 255)
			);
		}



	}


}

void CMouseMgr::Release()
{
}
