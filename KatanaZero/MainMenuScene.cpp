#include "pch.h"
#include "MainMenuScene.h"
#include "BmpMgr.h"
#include "Camera.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

#define MAIN_MENU_SCENE_WIDTH		640
#define MAIN_MENU_SCENE_HEIGHT		720
#define MAIN_TITLE_WIDTH			166
#define MAIN_TITLE_HEIGHT			90
#define MAIN_GROSS_WIDTH			640
#define MAIN_GROSS_HEIGHT			255

CMainMenuScene::CMainMenuScene()
{
}

CMainMenuScene::~CMainMenuScene()
{
}

void CMainMenuScene::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/MAINUI/TITLE_BACKGROUND.bmp", L"MAIN_TITLE_BACKGROUND");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/MAINUI/TITLE.bmp", L"TITLE");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/MAINUI/BACKGROUND_GROSS.bmp", L"BACKGROUND_GROSS");

	CCamera::Get_Instance()->Set_LookAt(WINCX / 2.0f, WINCY / 2.f);

	CSoundMgr::Get_Instance()->Initialize();
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlaySound(L"song_nocturne.wav", SOUND_BGM, 1.f);
}

int CMainMenuScene::Update()
{
	CCamera::Get_Instance()->Update();
	Key_Input();
	return 0;
}

void CMainMenuScene::Late_Update()
{
	CCamera::Get_Instance()->Late_Update();
}

void CMainMenuScene::Render(HDC _hDC)
{
	Vec2 vLookAt = CCamera::Get_Instance()->Get_LookAt();
	HDC backgroundDC = CBmpMgr::Get_Instance()->Find_Img(L"MAIN_TITLE_BACKGROUND");
	HDC titleDC = CBmpMgr::Get_Instance()->Find_Img(L"TITLE");
	HDC backgroundGrossDC = CBmpMgr::Get_Instance()->Find_Img(L"BACKGROUND_GROSS");

	GdiTransparentBlt(
		_hDC,
		100, -100,
		MAIN_MENU_SCENE_WIDTH, 
		MAIN_MENU_SCENE_HEIGHT,
		backgroundDC,
		0, 0,
		MAIN_MENU_SCENE_WIDTH, MAIN_MENU_SCENE_HEIGHT,
		RGB(255, 0, 255)
	);

	GdiTransparentBlt(
		_hDC,
		WINCX / 2.0f - 120, WINCY / 2.0f - 120,
		MAIN_TITLE_WIDTH * 1.5f,
		MAIN_TITLE_HEIGHT * 1.5f,
		titleDC,
		0, 0,
		MAIN_TITLE_WIDTH, MAIN_TITLE_HEIGHT,
		RGB(255, 0, 255)
	);
}



void CMainMenuScene::Release()
{
	CCamera::Destroy_Instance();
}

void CMainMenuScene::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		CSceneMgr::Get_Instance()->Change_Scene(SCENE_ID::SC_STAGE_01);
	}
}

