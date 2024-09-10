#include "pch.h"
#include "MainGame.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "LineMgr.h"
#include "Camera.h"
#include "CollisionMgr.h"
#include "SoundMgr.h"
#include "KeyMgr.h"

CMainGame::CMainGame() :m_dwTime(GetTickCount()), m_iFps(0)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_DC = GetDC(g_hWnd);
	//CSceneMgr::Get_Instance()->Change_Scene(SCENE_ID::SC_STAGE_01);
	CSceneMgr::Get_Instance()->Change_Scene(SCENE_ID::SC_MAIN_MENU);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");
	CSoundMgr::Get_Instance()->Initialize();

#ifdef _DEBUG

	if (::AllocConsole() == TRUE)
	{
		FILE* nfp[3];
		freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
		freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
		freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
		std::ios::sync_with_stdio();
	}
#endif // _DEBUG
}

void CMainGame::Update()
{
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
	CSceneMgr::Get_Instance()->Late_Update();
	CKeyMgr::Get_Instance()->Key_Late_Update();
}

void CMainGame::Render()
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
	CSceneMgr::Get_Instance()->Render(hMemDC);

	
	
	BitBlt(m_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	++m_iFps;
	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFps);
		SetWindowText(g_hWnd, m_szFPS);
		m_iFps = 0;
		m_dwTime = GetTickCount();
	}
}

void CMainGame::Release()
{
#ifdef _DEBUG

	FreeConsole();

#endif // _DEBUG

	CLineMgr::Destroy_Instance();
	CBmpMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CScrollMgr::Destroy_Instance();
	CollisionMgr::Destroy_Instance();
	CSoundMgr::Destroy_Instance();
	
	
	ReleaseDC(g_hWnd, m_DC);
}

