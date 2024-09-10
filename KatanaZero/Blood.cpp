#include "pch.h"
#include "Blood.h"
#include "BmpMgr.h"

CBlood::CBlood()
{
}

CBlood::~CBlood()
{
	Release();
}

void CBlood::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Blood/blood_0_l.bmp", L"Blood_0", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Blood/blood_0_r.bmp", L"Blood_0", OBJ_DIR::RIGHT);
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Blood/blood_1_l.bmp", L"Blood_1", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Blood/blood_1_r.bmp", L"Blood_1", OBJ_DIR::RIGHT);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Blood/blood_2_l.bmp", L"Blood_2", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Blood/blood_2_r.bmp", L"Blood_2", OBJ_DIR::RIGHT);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Blood/blood_3_l.bmp", L"Blood_3", OBJ_DIR::LEFT);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Blood/blood_3_r.bmp", L"Blood_3", OBJ_DIR::RIGHT);


	switch (m_eAttackType)
	{
	case ATTACK_TYPE::NORMAL_ATTACK:
	{
		int iRandomBloodType = (rand() % 4);
		if (iRandomBloodType == 0)
		{
			m_pFrameKey = L"Blood_0";
			m_tInfo.fCX = BLOOD_0_FCX;
			m_tInfo.fCY = BLOOD_0_FCY;
		}
		else if (iRandomBloodType == 1)
		{
			m_pFrameKey = L"Blood_1";
			m_tInfo.fCX = BLOOD_1_FCX;
			m_tInfo.fCY = BLOOD_1_FCY;
		}
		else if (iRandomBloodType == 2)
		{
			m_pFrameKey = L"Blood_2";
			m_tInfo.fCX = BLOOD_2_FCX;
			m_tInfo.fCY = BLOOD_2_FCY;
		}
		else if (iRandomBloodType == 3)
		{
			m_pFrameKey = L"Blood_3";
			m_tInfo.fCX = BLOOD_3_FCX;
			m_tInfo.fCY = BLOOD_3_FCY;
		}
		break;
	}
	default:
	{
		break;
	}
	}

	CObj::Update_Rect();
	CObj::Update_Render_Rect();

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = DEFAULT_FRAME_DWSPEED;
	m_tFrame.iMotion = 0;
}

int CBlood::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}
	CObj::Update_Rect();
	CObj::Update_Render_Rect();
	return OBJ_NO_EVENT;
}

void CBlood::Late_Update()
{
	
}

void CBlood::Render(HDC _hDC)
{
	HDC hBloodDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey, m_eObjCurDir);
	GdiTransparentBlt(
		_hDC,
		m_tRenderRect.left,
		m_tRenderRect.top,
		m_tInfo.fCX,
		m_tInfo.fCY,
		hBloodDC,
		0, 0,
		m_tInfo.fCX,
		m_tInfo.fCY,
		RGB(255, 0, 255)
	);
}

void CBlood::Release()
{
}
