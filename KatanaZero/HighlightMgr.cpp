#include "pch.h"
#include "HighlightMgr.h"
#include "SceneMgr.h"
#include "Camera.h"
#include "Stage01.h"
#include "Stage02.h"
#include "Stage03.h"
#include "BossStage01.h"
#include "BossStage02.h"
#include "TimeSlowMgr.h"
#include "BmpMgr.h"
#include "Obj.h"

CHighlightMgr* CHighlightMgr::m_pInstance = nullptr;

CHighlightMgr::CHighlightMgr()
{
}

CHighlightMgr::~CHighlightMgr()
{

}

bool CHighlightMgr::Is_Highlight()
{
	return m_bHighlightTime;
}




void CHighlightMgr::Print_Highlight(HDC _hDC, float _fX, float _fY, float _fWaitingTime, bool _bTimeSlow)
{
	if (m_bHighlightTime == false)
	{
		Vec2 vRenderPos = CCamera::Get_Instance()->GetRenderPos(Vec2{ _fX, _fY });
		m_fTargetFx = vRenderPos.fX;
		m_fTargetFy = vRenderPos.fY;
	}

	float fHopeWidth = 100.f;
	float fHopeHeight = 100.f;


	float iSrcLeft = m_fTargetFx - (fHopeWidth * m_fSmoothX) / 2.f;
	float iSrcTop = m_fTargetFy - (fHopeHeight * m_fSmoothY) / 2.f;
	float iSrcRight = m_fTargetFx + (fHopeWidth * m_fSmoothX) / 2.f;
	float iSrcBottom = m_fTargetFy + (fHopeHeight * m_fSmoothY) / 2.f;

	//if (iSrcLeft < 0) iSrcLeft = 0;
	//if (iSrcTop < 0) iSrcTop = 0;
	//if (iSrcRight > WINCX) iSrcRight = WINCX;
	//if (iSrcBottom > WINCY) iSrcBottom = WINCY;

	float iSrcWidth = iSrcRight - iSrcLeft;
	float iSrcHeight = iSrcBottom - iSrcTop;

	HDC hMemDC = CreateCompatibleDC(_hDC);
	HBITMAP hBitMap = CreateCompatibleBitmap(_hDC, WINCX, WINCY);
	::SelectObject(hMemDC, hBitMap);

	// 조정된 소스 영역을 화면 전체에 맞게 확대
	StretchBlt(hMemDC, 0, 0, WINCX, WINCY, _hDC, iSrcLeft, iSrcTop, iSrcWidth, iSrcHeight, SRCCOPY);
	BitBlt(_hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);


	bool bDead = true;
	switch (m_eSmoothStatus)
	{
	case START_ZOOM_IN_STATUS:
	{
		// init status
		m_bHighlightTime = true;
		m_bSmoothHighlight = true;

		m_eSmoothStatus = FAST_ZOOM_IN_STATUS;
		break;
	}
	case FAST_ZOOM_IN_STATUS:
	{
		if (m_dwSmoothTime + 1.5 < GetTickCount())
		{
			if (_fWaitingTime)
			{
				CTimeSlowMgr::Get_Instance()->Set_Slow_Interval_Time();
			}
			if (m_fSmoothX >= 1.5f)
			{
				m_fSmoothX -= 0.05f;
				m_fSmoothY -= 0.05f;
				m_dwSmoothTime = GetTickCount();
			}
			else
			{
				m_eSmoothStatus = END_ZOOM_IN_STATUS;
			}
		}
		break;
	}
	case END_ZOOM_IN_STATUS:
	{
		if (_fWaitingTime)
		{
			CTimeSlowMgr::Get_Instance()->Set_Normal_Interval_Time();
		}

		m_bHighlightTime = false;
		m_bSmoothHighlight = true;
		CSceneMgr::Get_Instance()->Get_Active_Scene()->Set_Highlight_Event(false);
		m_eSmoothStatus = START_ZOOM_IN_STATUS;

		int a = 3;
		break;
	}
	}


	// 메모리 DC와 비트맵 객체 해제
	DeleteObject(hBitMap);
	DeleteDC(hMemDC);
}




void CHighlightMgr::Set_Highlight(POINT tHighlightRenderPivot)
{
	m_tHighlightRenderPivot.x = tHighlightRenderPivot.x;
	m_tHighlightRenderPivot.y = tHighlightRenderPivot.y;
	m_bHighlightTime = true;

	if (m_bSmoothHighlight)
	{
		m_dwSmoothTime = GetTickCount();
	}
}




void CHighlightMgr::Print_Highlight_For_ThunderBreathing(HDC _hDC, float _fX, float _fY, PLAYER_THUNDER_BREATHING_MOTION _eThunderBreathingMotion)
{
	Vec2 vRenderPos = CCamera::Get_Instance()->GetRenderPos(Vec2{ _fX, _fY });
	m_fTargetFx = vRenderPos.fX;
	m_fTargetFy = vRenderPos.fY;

	float wantedWidth = 150.f;
	float wantedHeight = 150.f;

	float iSrcLeft = m_fTargetFx - (wantedWidth * m_fSmoothX) / 2.f;
	float iSrcTop = m_fTargetFy - (wantedHeight * m_fSmoothY) / 2.f;
	float iSrcRight = m_fTargetFx + (wantedWidth * m_fSmoothX) / 2.f;
	float iSrcBottom = m_fTargetFy + (wantedHeight * m_fSmoothY) / 2.f;

	float iSrcWidth = iSrcRight - iSrcLeft;
	float iSrcHeight = iSrcBottom - iSrcTop;

	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/effect/ThunderBreathingImage.bmp", L"THUNDER_BREATHING_IMAGE");
	HDC zenitchDC = CBmpMgr::Get_Instance()->Find_Img(L"THUNDER_BREATHING_IMAGE");

	HDC hMemDC = CreateCompatibleDC(_hDC);
	HBITMAP hBitMap = CreateCompatibleBitmap(_hDC, WINCX, WINCY);
	::SelectObject(hMemDC, hBitMap);

	// 조정된 소스 영역을 화면 전체에 맞게 확대
	StretchBlt(hMemDC, 0, 0, WINCX, WINCY, _hDC, iSrcLeft, iSrcTop, iSrcWidth, iSrcHeight, SRCCOPY);
	BitBlt(_hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);


	switch (_eThunderBreathingMotion)
	{
	case PLAYER_THUNDER_BREATHING_MOTION::PLAYER_SCRIPT:
	{
		BitBlt(_hDC, m_fHighlightOffsetX, m_fHighlightOffsetY, WINCX, WINCY, zenitchDC, 0, 0, SRCCOPY);
		if (m_dwSmoothTime + 10 < GetTickCount())
		{
			if (m_fSmoothX >= 0.4f)
			{
				m_fSmoothX -= 0.05f;
				m_fSmoothY -= 0.05f;
				m_dwSmoothTime = GetTickCount();
			}
		}

		switch (m_eSkillEffectSequence)
		{
		case SKILL_EFFECT_SEQUENCE::ENTRANCE:
		{
			m_fHighlightOffsetX = m_fHighlightOffsetX - 5 * m_fTime + (0.5) * 2.5 * m_fTime;
			if (m_fHighlightOffsetX <= 0)
			{
				m_eSkillEffectSequence = SKILL_EFFECT_SEQUENCE::WAITING;
				m_dwWaitingTime = GetTickCount();
			}
			break;
		}
		case SKILL_EFFECT_SEQUENCE::WAITING:
		{
			if (m_dwWaitingTime + 2000 < GetTickCount())
			{
				m_eSkillEffectSequence = SKILL_EFFECT_SEQUENCE::LEAVE;
				m_fTime = 0.f;
			}
			break;
		}
		case SKILL_EFFECT_SEQUENCE::LEAVE:
		{
			m_fHighlightOffsetX = m_fHighlightOffsetX - 5 * m_fTime + (0.5) * 2.5 *  m_fTime;
			break;
		}
		}
		m_fTime += 0.1f;

		break;
	}
	case PLAYER_THUNDER_BREATHING_MOTION::PLAYER_ATTACK_BEFORE:
	{
		m_fHighlightOffsetX = 800.f;
		m_fHighlightOffsetY = 225.f;
		m_fTime = 0.f;
		m_eSkillEffectSequence = SKILL_EFFECT_SEQUENCE::ENTRANCE;
		if (m_dwSmoothTime + 10 < GetTickCount())
		{
			if (m_fSmoothX <= 2.0f)
			{
				m_fSmoothX += 0.05f;
				m_fSmoothY += 0.05f;
			}
		}
		break;
	}
	case PLAYER_THUNDER_BREATHING_MOTION::PLAYER_ATTACK:
	{
		if (m_dwSmoothTime + 10 < GetTickCount())
		{

		}
		break;
	}
	}




	DeleteObject(hBitMap);
	DeleteDC(hMemDC);
}



void CHighlightMgr::Print_Highlight_For_DoorKick(HDC _hDC, float _fX, float _fY)
{
	Vec2 vRenderPos = CCamera::Get_Instance()->GetRenderPos(Vec2{ _fX, _fY });
	float m_fTargetFx = vRenderPos.fX;
	float m_fTargetFy = vRenderPos.fY;
}

void CHighlightMgr::Print_Battle_Scene(HDC _hDC, float _fX, float _fY)
{
	Vec2 vRenderPos = CCamera::Get_Instance()->GetRenderPos(Vec2{ _fX, _fY });
	float m_fTargetFx = vRenderPos.fX;
	float m_fTargetFy = vRenderPos.fY;

	float wantedWidth = 200.f;
	float wantedHeight = 150.f;

	float iSrcLeft = m_fTargetFx - (wantedWidth * m_fSmoothX) / 2.f;
	float iSrcTop = m_fTargetFy - (wantedHeight * m_fSmoothY) / 2.f;
	float iSrcRight = m_fTargetFx + (wantedWidth * m_fSmoothX) / 2.f;
	float iSrcBottom = m_fTargetFy + (wantedHeight * m_fSmoothY) / 2.f;

	float iSrcWidth = iSrcRight - iSrcLeft;
	float iSrcHeight = iSrcBottom - iSrcTop;

	HDC hMemDC = CreateCompatibleDC(_hDC);
	HBITMAP hBitMap = CreateCompatibleBitmap(_hDC, WINCX, WINCY);
	::SelectObject(hMemDC, hBitMap);

	// 조정된 소스 영역을 화면 전체에 맞게 확대
	StretchBlt(hMemDC, 0, 0, WINCX, WINCY, _hDC, iSrcLeft, iSrcTop, iSrcWidth, iSrcHeight, SRCCOPY);
	BitBlt(_hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);



	DeleteObject(hBitMap);
	DeleteDC(hMemDC);
}


