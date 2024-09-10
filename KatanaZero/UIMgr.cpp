#include "pch.h"
#include "UIMgr.h"
#include "BmpMgr.h"
#include "TimeSlowMgr.h"
#include "Player.h"

#define NOTHING_BACKGROUND_WIDTH	224
#define NOTHING_BACKGROUND_HEIGHT	106

CUIMgr* CUIMgr::m_pInstance = nullptr;

CUIMgr::CUIMgr()
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/HUD.bmp", L"HUD");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/BATTERY.bmp", L"Battery");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/TIMER.bmp", L"Timer");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/MAINUI/nothing_background_ma.bmp", L"Nothing_Background");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/MAINUI/nothing_title.bmp", L"Nothing_Title");
}

void CUIMgr::Update()
{
	int iCurrentBattery = CTimeSlowMgr::Get_Instance()->Get_Power();
	m_iBatteryCharge = iCurrentBattery / 10;

	

	//if (m_pPlayer)
	//{
	//	for (int i = 0; i < ITEM_TYPE_END; ++i)
	//	{
	//		if (static_cast<CPlayer*>(m_pPlayer)->m_bInventory[i])
	//		{
	//			m_eItemType = (ITEM_TYPE)(i);
	//			break;
	//		}
	//	}
	//}

}



void CUIMgr::Late_Update()
{

}

void CUIMgr::Render(HDC _hDC)
{

	if (m_pPlayer->Get_Obj_Cur_Status() == OBJ_STATUS::LAY_DOWN || m_pPlayer->Get_Obj_Cur_Status() == OBJ_STATUS::LAY_DOWN_MIDDLE || m_pPlayer->Get_Obj_Cur_Status() == OBJ_STATUS::LAY_DOWN_START)
	{
		HDC hNothingTitleDC = CBmpMgr::Get_Instance()->Find_Img(L"Nothing_Title");
		GdiTransparentBlt(
			_hDC,
			WINCX / 2.0f - 100, WINCY / 2.0f - 50,
			NOTHING_BACKGROUND_WIDTH,
			NOTHING_BACKGROUND_HEIGHT,
			hNothingTitleDC,
			0, 0,
			NOTHING_BACKGROUND_WIDTH,
			NOTHING_BACKGROUND_HEIGHT,
			RGB(255, 0, 255)
		);
	}
	else
	{

		HDC hHUDDC = CBmpMgr::Get_Instance()->Find_Img(L"HUD");
		HDC hBatteryDC = CBmpMgr::Get_Instance()->Find_Img(L"Battery");
		HDC hTimerDC = CBmpMgr::Get_Instance()->Find_Img(L"Timer");

		GdiTransparentBlt(
			_hDC,
			0, 0,
			800, 42,
			hHUDDC,
			0, 0,
			800, 42,
			RGB(255, 0, 255)
		);

		// Battery
		for (int i = 0; i < m_iBatteryCharge; ++i)
		{
			int iBatteryOffsetX = 10;
			int iBatteryOffsetY = 6;
			GdiTransparentBlt(
				_hDC,
				iBatteryOffsetX + (i * 8), iBatteryOffsetY,
				6, 15,
				hBatteryDC,
				0, 0,
				6, 15,
				RGB(0, 0, 0)
			);
		}

		GdiTransparentBlt(
			_hDC,
			WINCX / 2.0f - 50.f, 3.0f,
			120, 16,
			hTimerDC,
			0, 0,
			120, 16,
			RGB(0, 0, 0)
		);
	}
}

void CUIMgr::Release()
{

}
