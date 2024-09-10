#pragma once

class CObj;
class CHighlightMgr
{
private:
	CHighlightMgr();
	virtual ~CHighlightMgr();

public:
	enum SMOOTH_HIGH_LIGHT_STATUS
	{
		START_ZOOM_IN_STATUS,
		FAST_ZOOM_IN_STATUS,
		SLOW_ZOOM_IN_STATUS,
		WAITING_ZOOM_IN_STATUS,
		FAST_ZOOM_OUT_STATUS,
		SLOW_ZOOM_OUT_STATUS,
		END_ZOOM_IN_STATUS,
		SMOOTH_HIGH_LIGHT_STATUS_END
	};

public:
	bool Is_Highlight();
	
	void Print_Highlight(HDC _hDC, float _fX, float _fY, float _fWaitingTime, bool _bTimeSlow = false);
	// 일단 렌더 피벗으로 하고 안되면 실제 위치값으로 ㄱㄱ // 시간도 느리게 가게 만들어보기
	void Set_Highlight(POINT tHighlightRenderPivot);
	void Set_HighlightTime(bool _bIsHighlight) { m_bHighlightTime = _bIsHighlight; }

	void Print_Highlight_For_ThunderBreathing(HDC _hDC, float _fX, float _fY, PLAYER_THUNDER_BREATHING_MOTION _eThunderBreathingMotion);
	void Print_Highlight_For_DoorKick(HDC _hDC, float _fX, float _fY);
	void Print_Battle_Scene(HDC _hDC, float _fX, float _fY);

	bool Is_Smooth() { return m_bSmoothHighlight; }

	float Get_SmoothX() { return m_fSmoothX; }
	float Get_SmoothY() { return m_fSmoothY; }
public:
	static CHighlightMgr* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CHighlightMgr;
		}
		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static CHighlightMgr* m_pInstance;

	//int iSrcFCXs[4] = {
	//	400,
	//	200,
	//	160,
	//	80
	//};
	//int iSrcFCYs[4] = {
	//	300,
	//	150,
	//	120,
	//	60
	//};

	//int iScaleRatios[4] = {
	//	2,
	//	4,
	//	5,
	//	10
	//};

	//int iSrcFCX = 160;
	//int iSrcFCY = 120;
	//int iScaleRatio = 5; // iScale만큼 확대 시작
	//int iScaleUpIdx = 0;

	// 위의 정보를 기반으로 구해야 할 데이터들
	//int iSrcLeft;
	//int iSrcTop;
	//int iDstWidth;
	//int iDstHeight;

	LONG m_lTargetFrame = -1;

	POINT m_tHighlightRenderPivot = { 0, };

	bool m_bHighlights[HIGHLIGHT_END] = { 0, };
	bool m_bHighlightTime = false;
	

	bool m_bSmoothHighlight = true;
	DWORD m_dwSmoothTime = GetTickCount();

	float m_fSmoothX = 2.0f;
	float m_fSmoothY = 2.0f;

	float m_fTargetFx;
	float m_fTargetFy;
	float m_fSrcLeft;
	float m_fSrcTop;
	float m_fSrcRight;
	float m_fSrBottom;
	float m_fSrcHeight;
	


	//float fHopeWidth = WINCX; // 처음 확대될 화면이기도 함
	//float fHopeHeight = WINCY; // 처음 


	CObj* m_pTarget;

	float fHopeWidth = 250.f;
	float fHopeHeight = 200.f;

	SMOOTH_HIGH_LIGHT_STATUS m_eSmoothStatus = START_ZOOM_IN_STATUS;

	float m_fHighlightOffsetX = 800.f;
	float m_fHighlightOffsetY = 225.f;
	float m_fTime = 0.0f;
	SKILL_EFFECT_SEQUENCE m_eSkillEffectSequence = SKILL_EFFECT_SEQUENCE::ENTRANCE;
	DWORD m_dwWaitingTime;
};

