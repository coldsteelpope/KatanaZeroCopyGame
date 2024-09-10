#include "pch.h"
#include "TileMgr.h"
#include "AbstractFactory.h"
#include "Camera.h"
#include "Tile.h"
#include "KeyMgr.h"
#include "Camera.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include <tchar.h>

CTileMgr* CTileMgr::m_pInstance = nullptr;
CTileMgr::CTileMgr()
{

}

CTileMgr::~CTileMgr()
{
	Release();
}

// Edit Mode를 사용하기 위해서는 불러와야 할 m_vecTile이 0개여야 한다.
void CTileMgr::Initialize()
{
	

	switch (CSceneMgr::Get_Instance()->Get_Cur_Scene_ID())
	{
	case SCENE_ID::SC_STAGE_03:
	{
		HANDLE hFile = CreateFile(L"../Data/Tile3.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, L"Load Failed", _T("error"), MB_OK);
			return;
		}

		DWORD dwByte(0);
		TILE_TYPE iDrawID(TILE_END), iOption(TILE_END);
		INFO tInfo{};

		Release();
		while (true)
		{
			ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
			ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);

			if (0 == dwByte)
			{
				// 아무것도 못읽어온것
				break;
			}

			CObj* pTile = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY);
			dynamic_cast<CTile*>(pTile)->Set_DrawID(iDrawID);
			dynamic_cast<CTile*>(pTile)->Set_Option(iOption);
			m_vecTile.push_back(pTile);
		}

		CloseHandle(hFile);

		for (int i = 0; i < m_vecTile.size(); ++i)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_TILE, m_vecTile[i]);
		}
		break;
	}
	case SCENE_ID::SC_BOSS_02:
	{
		HANDLE hFile = CreateFile(L"../Data/Tile4.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, L"Load Failed", _T("error"), MB_OK);
			return;
		}

		DWORD dwByte(0);
		TILE_TYPE iDrawID(TILE_END), iOption(TILE_END);
		INFO tInfo{};

		Release();
		while (true)
		{
			ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
			ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);

			if (0 == dwByte)
			{
				// 아무것도 못읽어온것
				break;
			}

			CObj* pTile = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY);
			dynamic_cast<CTile*>(pTile)->Set_DrawID(iDrawID);
			dynamic_cast<CTile*>(pTile)->Set_Option(iOption);
			m_vecTile.push_back(pTile);
		}

		CloseHandle(hFile);

		for (int i = 0; i < m_vecTile.size(); ++i)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_ID::OBJ_ID_TILE, m_vecTile[i]);
		}
		break;
		break;
	}
	}

	m_vecTile.clear();

	m_iTheNumberOfHeightTiles = m_iHeight / TILECY;
	m_iTheNumberOfWidthTiles = m_iWidth / TILECX;

	m_vecTile.reserve(m_iTheNumberOfHeightTiles * m_iTheNumberOfWidthTiles);
	for (int i = 0; i < m_iTheNumberOfHeightTiles; ++i)
	{
		for (int j = 0; j < m_iTheNumberOfWidthTiles; ++j)
		{
			float fX = float((TILECX >> 1) + (TILECX * j));
			float fY = float((TILECY >> 1) + (TILECY * i));

			CObj* pTile = CAbstractFactory<CTile>::Create(fX, fY);
			m_vecTile.push_back(pTile);
		}
	}
}

void CTileMgr::Update()
{
	Key_Input();

	for (auto& pTile : m_vecTile)
	{
		pTile->Update();
	}
}

void CTileMgr::Late_Update()
{
	for (auto& pTile : m_vecTile)
	{
		pTile->Late_Update();
	}
}

void CTileMgr::Render(HDC _hDC)
{
	if (m_bEditMode)
	{
		for (int i = 0; i < m_iHeight; i += 16)
		{
			for (int j = 0; j < m_iWidth; j += 16)
			{
				HPEN redPen = (HPEN)::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
				HPEN oldPen = (HPEN)::SelectObject(_hDC, redPen);

				Vec2 renderPos = CCamera::Get_Instance()->GetRenderPos(Vec2{ (float)j, (float)i });

				::MoveToEx(_hDC, (int)renderPos.fX, (int)renderPos.fY, nullptr);
				::LineTo(_hDC, (int)renderPos.fX, renderPos.fY + 16);
				::LineTo(_hDC, (int)renderPos.fX + 16, renderPos.fY + 16);
				::LineTo(_hDC, (int)renderPos.fX + 16, renderPos.fY);
				::LineTo(_hDC, (int)renderPos.fX, renderPos.fY);

				::SelectObject(_hDC, oldPen);
				::DeleteObject(redPen);
			}
		}
		for (auto pTile : m_vecTile)
		{
			pTile->Render(_hDC);
		}
	}


}

void CTileMgr::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<CObj*>);
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}

void CTileMgr::Picking_Tile(POINT _tPt, TILE_TYPE _iDrawID, TILE_TYPE _iOption)
{
	int x = _tPt.x / TILECX;
	int y = _tPt.y / TILECY;
	int iIndex = y * m_iTheNumberOfWidthTiles + x;
	if (0 > iIndex || (size_t)iIndex >= m_vecTile.size())
	{
		return;
	}
	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_DrawID(_iDrawID);
	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_Option(_iOption);
}

void CTileMgr::Save_Tile()
{
	HANDLE hFile = CreateFile(L"../Data/Tile5.dat", 
		GENERIC_WRITE,
		NULL,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	
	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"save failed", _T("error"), MB_OK);
		return;
	}

	DWORD dwByte(0);
	TILE_TYPE iDrawID(TILE_END), iOption(TILE_END); // drawID에 따라 색깔이 option에 따라 타일의 성질이 다르게 하자
	// 현재 해야 할 타일
	// 벽타기가 안되는 타일
	// 벽타기가 되는 타일

	for (auto& pTile : m_vecTile)
	{
		iDrawID = dynamic_cast<CTile*>(pTile)->Get_DrawID();
		iOption = dynamic_cast<CTile*>(pTile)->Get_Option();
		
		if (iDrawID != TILE_END)
		{
			WriteFile(hFile, &(pTile->Get_Info()), sizeof(INFO), &dwByte, nullptr);
			WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);
		}
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Tile Save 완료", L"Success", MB_OKCANCEL);
}

// 생각하고 사용할것
void CTileMgr::Load_Tile()
{
	HANDLE hFile = CreateFile(L"../Data/Tile5.dat",
		GENERIC_READ,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	
	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Load Failed", _T("error"), MB_OK);
		return;
	}

	DWORD dwByte(0);
	TILE_TYPE iDrawID(TILE_END), iOption(TILE_END);
	INFO tInfo{};

	Release();
	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
		{
			// 아무것도 못읽어온것
			break;
		}

		CObj* pTile = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY);
		dynamic_cast<CTile*>(pTile)->Set_DrawID(iDrawID);
		dynamic_cast<CTile*>(pTile)->Set_Option(iOption);
		m_vecTile.push_back(pTile);
	}

	CloseHandle(hFile);
}

void CTileMgr::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Down('J'))
	{
		m_bEditMode = !m_bEditMode;
	}

	if (m_bEditMode)
	{
		if (CKeyMgr::Get_Instance()->Key_Down('N'))
		{
			m_iDrawID = TILE_TYPE::SOLID_WALL_TILE;
			m_iOptionID = TILE_TYPE::SOLID_WALL_TILE;
		}

		if (CKeyMgr::Get_Instance()->Key_Down('M'))
		{
			m_iDrawID = TILE_TYPE::CLIMB_WALL_TILE;
			m_iOptionID = TILE_TYPE::CLIMB_WALL_TILE;
		}

		if (CKeyMgr::Get_Instance()->Key_Down('V'))
		{
			Save_Tile();
		}

		if (CKeyMgr::Get_Instance()->Key_Down('B'))
		{
			Load_Tile();
		}

		if (CKeyMgr::Get_Instance()->Key_Down('Z'))
		{
			m_vecTile.pop_back();
		}

		if (CKeyMgr::Get_Instance()->Key_Down(VK_MBUTTON))
		{
			POINT ps;
			GetCursorPos(&ps);
			ScreenToClient(g_hWnd, &ps);
			Vec2 realPs = CCamera::Get_Instance()->GetRealPos(Vec2{ (float)ps.x, (float)ps.y });
			Picking_Tile(POINT{ (LONG)realPs.fX, (LONG)realPs.fY }, m_iDrawID, m_iOptionID);
		}
	}
}
