#include "pch.h"
#include "Line.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "Scene.h"
#include "SceneMgr.h"
#include "Camera.h"
#include "BossStage01.h"
#include <tchar.h>

#define MAX_LIMIT_SCOPE 200

CLineMgr* CLineMgr::m_pInstance = nullptr;
CLineMgr::CLineMgr() : m_pCurrentLine(nullptr), m_bEditMode(false)
{
	ZeroMemory(m_tLinePoint, sizeof(m_tLinePoint));
}

CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize()
{
	SCENE_ID eSceneId = CSceneMgr::Get_Instance()->Get_Cur_Scene_ID();
	switch (eSceneId)
	{
	case SCENE_ID::SC_STAGE_01:
	{
		LINEPOINT tLinePoints[7] = {
			{ 120, 525 },
			{ 740, 525 },
			{ 970, 295 },
			{ 1200, 295 },

			{ 520, 295},
			{ 970, 295},

			{120, 295}
		};

		m_LineList.push_back(new CLine(tLinePoints[0], tLinePoints[1], LINE_TYPE::SOLID));
		m_LineList.push_back(new CLine(tLinePoints[1], tLinePoints[2], LINE_TYPE::SOLID));
		m_LineList.push_back(new CLine(tLinePoints[2], tLinePoints[3], LINE_TYPE::SOLID));

		m_LineList.push_back(new CLine(tLinePoints[4], tLinePoints[5], LINE_TYPE::NORMAL));
		m_LineList.push_back(new CLine(tLinePoints[6], tLinePoints[4], LINE_TYPE::SOLID));

		break;
	}
	case SCENE_ID::SC_STAGE_02:
	{
		HANDLE		hFile = CreateFile(L"../Data/Line2.dat",		// 파일 경로와 이름을 명시
			GENERIC_READ,			// 파일 접근 모드(GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
			NULL,					// 공유 방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈 할 때 허가하는 것에 대해서 설정(null 지정 시 공유하지 않음)
			NULL,					// 보안 속성, NULL인 기본 값 설정 유지
			OPEN_EXISTING,			// 생성 방식( CREATE_ALWAYS : 파일이 없다면 생성, 있으면 덮어 쓰기, OPEN_EXISTING : 파일이 있을 경우에만 불러오기)
			FILE_ATTRIBUTE_NORMAL,	// 파일 속성( FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 파일)
			NULL);


		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, L"Load Failed", _T("error"), MB_OK);
			return;
		}

		DWORD	dwByte(0);
		STORED_LINE_DATA tLine{};

		while (true)
		{
			ReadFile(hFile, &tLine, sizeof(STORED_LINE_DATA), &dwByte, nullptr);
			if (0 == dwByte)
				break;
			m_LineList.push_back(new CLine(tLine.tLeft, tLine.tRight, tLine.eLineType));
		}

		CloseHandle(hFile);
		break;
	}
	case SCENE_ID::SC_STAGE_03:
	{
		HANDLE		hFile = CreateFile(L"../Data/Line3.dat",		// 파일 경로와 이름을 명시
			GENERIC_READ,			// 파일 접근 모드(GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
			NULL,					// 공유 방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈 할 때 허가하는 것에 대해서 설정(null 지정 시 공유하지 않음)
			NULL,					// 보안 속성, NULL인 기본 값 설정 유지
			OPEN_EXISTING,			// 생성 방식( CREATE_ALWAYS : 파일이 없다면 생성, 있으면 덮어 쓰기, OPEN_EXISTING : 파일이 있을 경우에만 불러오기)
			FILE_ATTRIBUTE_NORMAL,	// 파일 속성( FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 파일)
			NULL);


		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, L"Load Failed", _T("error"), MB_OK);
			return;
		}

		DWORD	dwByte(0);
		STORED_LINE_DATA tLine{};

		while (true)
		{
			ReadFile(hFile, &tLine, sizeof(STORED_LINE_DATA), &dwByte, nullptr);
			if (0 == dwByte)
				break;
			m_LineList.push_back(new CLine(tLine.tLeft, tLine.tRight, tLine.eLineType));
		}

		CloseHandle(hFile);


		// 수동 추가
		//LINEPOINT tLinePointsForNormal[10] = {
		//	{ 357, 207 },
		//	{ 426, 207 },
		//	
		//	{ 768, 207 },
		//	{ 836, 207 },
		//	
		//	{ 1005, 275 },
		//	{ 1180, 275 },
		//	
		//	{ 1508, 275 },
		//	{ 1669, 275 },
		//	
		//	{ 1927, 275 },
		//	{ 1997, 275 }
		//};

		//LINEPOINT tLinePointsForSolid[8] = {
		//	{ 305, 207 },
		//	{ 357, 207 },

		//	{ 427, 207 },
		//	{ 768, 207 },

		//	{ 954, 275 },
		//	{ 1005, 275 },

		//	{ 1669, 275 },
		//	{ 1927, 275 }
		//};

		//m_LineList.push_back(new CLine(tLinePointsForNormal[0], tLinePointsForNormal[1], LINE_TYPE::NORMAL));
		//m_LineList.push_back(new CLine(tLinePointsForNormal[2], tLinePointsForNormal[3], LINE_TYPE::NORMAL));
		//m_LineList.push_back(new CLine(tLinePointsForNormal[4], tLinePointsForNormal[5], LINE_TYPE::NORMAL));
		//m_LineList.push_back(new CLine(tLinePointsForNormal[6], tLinePointsForNormal[7], LINE_TYPE::NORMAL));
		//m_LineList.push_back(new CLine(tLinePointsForNormal[8], tLinePointsForNormal[9], LINE_TYPE::NORMAL));

		//m_LineList.push_back(new CLine(tLinePointsForSolid[0], tLinePointsForSolid[1], LINE_TYPE::SOLID));
		//m_LineList.push_back(new CLine(tLinePointsForSolid[2], tLinePointsForSolid[3], LINE_TYPE::SOLID));
		//m_LineList.push_back(new CLine(tLinePointsForSolid[4], tLinePointsForSolid[5], LINE_TYPE::SOLID));
		//m_LineList.push_back(new CLine(tLinePointsForSolid[6], tLinePointsForSolid[7], LINE_TYPE::SOLID));
		
		break;
	}
	case SCENE_ID::SC_BOSS_01:
	{

		switch (static_cast<CBossStage01*>(CSceneMgr::Get_Instance()->Get_Active_Scene())->Get_Boss_Stage_One_Type())
		{
		case BOSS_STAGE_ONE_TYPE::BOSS_STAGE_ONE_NORMAL:
		{
			LINEPOINT tLinePointsForSolid[2] = {
			{0, 380},
			{800, 380}
			};
			m_LineList.clear();
			m_LineList.push_back(new CLine(tLinePointsForSolid[0], tLinePointsForSolid[1], LINE_TYPE::SOLID));

			break;
		}
		case BOSS_STAGE_ONE_TYPE::BOSS_STAGE_ONE_BOMB:
		{
			LINEPOINT tLinePointsForSolid[2] = {
				{0, 1000},
				{800, 1000}
			};
			m_LineList.clear();
			m_LineList.push_back(new CLine(tLinePointsForSolid[0], tLinePointsForSolid[1], LINE_TYPE::SOLID));
			break;
		}
		}




		break;
	}
	case SCENE_ID::SC_BOSS_02:
	{
		LINEPOINT tLinePointsForSolid[2] = {
			{0, 420},
			{1028, 420}
		};
		
		m_LineList.push_back(new CLine(tLinePointsForSolid[0], tLinePointsForSolid[1], LINE_TYPE::SOLID));
		break;
	}
	}
}

int CLineMgr::Update()
{
	Key_Input();
	if (m_bEditMode)
	{
		POINT	pt{};
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		Vec2 realPos = CCamera::Get_Instance()->GetRealPos(Vec2{ (float)pt.x, (float)pt.y });

		if (CKeyMgr::Get_Instance()->Key_Down(VK_MBUTTON))
		{
			if ((!m_tLinePoint[LEFT].fX) && (!m_tLinePoint[LEFT].fY))
			{
				m_tLinePoint[LEFT].fX = (float)realPos.fX;
				m_tLinePoint[LEFT].fY = (float)realPos.fY;
			}

			else
			{
				m_tLinePoint[RIGHT].fX = (float)realPos.fX;
				m_tLinePoint[RIGHT].fY = (float)realPos.fY;
				m_LineList.push_back(new CLine(m_tLinePoint[LEFT], m_tLinePoint[RIGHT], m_eDrawLineType));

				m_tLinePoint[LEFT].fX = m_tLinePoint[RIGHT].fX;
				m_tLinePoint[LEFT].fY = m_tLinePoint[RIGHT].fY;
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
		{
			ZeroMemory(&m_tLinePoint, sizeof(m_tLinePoint));
		}
	}


	//Vec2 realPos = CCamera::Get_Instance()->GetRealPos(Vec2{ (float)pt.x, (float)pt.y });
	

	return 0;
}

void CLineMgr::Late_Update()
{
}

void CLineMgr::Render(HDC _hDC)
{

	for (auto& Line : m_LineList)
	{
		Line->Render(_hDC);
	}

}

void CLineMgr::Release()
{
	for_each(m_LineList.begin(), m_LineList.end(), Safe_Delete<CLine*>);
	m_LineList.clear();
	
}


bool CLineMgr::Collision_Line(float _fX, float _fSpeed, float _fFoot, float _fCY, float* pY, OBJ_STATUS _eObjStatus)
{
	vector<CLine*> vecValidLinesForX;
	for (auto& Line : m_LineList)
	{
		// 무조건 왼쪽 X가 오른쪽 X보다 작다고 가정
		bool bValidX = _fX >= Line->Get_Info().tLeft.fX && _fX <= Line->Get_Info().tRight.fX;
		if (bValidX)
		{
			vecValidLinesForX.push_back(Line);
		}
	}

	// 만약 X범위 내에서 없다면 앞으로 캐릭터가 서야 할 위치를 무한대로 설정
	if (vecValidLinesForX.size() == 0)
	{
		(*pY) = FLT_MAX;
		m_pCurrentLine = nullptr;
		return false;
	}
	

	
	// 단 이 방법 사용할 때, 벽 충돌시 선을 좀 더 길게 그어주자
	switch (_eObjStatus)
	{
	case OBJ_STATUS::FLIP:
	{
		//float y0 = _fFoot + (_fCY / 2.0f);
		float y0 = _fFoot - (_fCY / 2.5f);

		float x0 = _fX - _fSpeed;
		float x1 = _fX;

		CLine* pMinDistLine = nullptr;

		
		float fMinDist = FLT_MAX;

		for (int i = 0; i < vecValidLinesForX.size(); ++i)
		{
			CLine* pCurrentLine = vecValidLinesForX[i];

			float temp = pCurrentLine->Get_Y(x0);

			if (pCurrentLine->Get_Y(x0) < y0)
			{
				continue;
			}

			float fDist = std::abs(y0 - pCurrentLine->Get_Y(x0));

			if (fMinDist > fDist)
			{
				pMinDistLine = pCurrentLine;
				fMinDist = fDist;
			}
		}

		if (pMinDistLine != nullptr)
		{
			(*pY) = pMinDistLine->Get_Y(x1);
			m_pCurrentLine = pMinDistLine;
			return true;
		}
		break;
	}
	case OBJ_STATUS::FALL:
	{
		float y0 = _fFoot - (_fCY / 2.0f);
		float x0 = _fX - _fSpeed;
		float x1 = _fX;

		CLine* pMinDistLine = nullptr;
		float fMinDist = FLT_MAX;

		for (int i = 0; i < vecValidLinesForX.size(); ++i)
		{
			CLine* pCurrentLine = vecValidLinesForX[i];
			float fCurrentLineY = pCurrentLine->Get_Y(x0);
			if (pCurrentLine->Get_Y(x0) < y0)
			{
				continue;
			}
			
			float fDist = std::abs(y0 - pCurrentLine->Get_Y(x0));
			
			if (fMinDist > fDist)
			{
				pMinDistLine = pCurrentLine;
				fMinDist = fDist;
			}


		}



		if (pMinDistLine != nullptr)
		{
			(*pY) = pMinDistLine->Get_Y(x1);
			m_pCurrentLine = pMinDistLine;
			return true;
		}

		break;
	}
	default:
	{
		float x0 = _fX - _fSpeed;
		float y0 = _fFoot + (_fCY / 2.0f);
		float x1 = _fX;
		
		// 다음 y값이 현재 y값보다 너무 큰 경우 (서로 떨어진 지형일 경우)
		// 걷지 못하도록 설정 (기울기를 이용해서)
		vector<CLine*> vecValidLinesForScope;
		vector<float> vecValidLinesScopes;
		for (int i = 0; i < vecValidLinesForX.size(); ++i)
		{
			float y1 = vecValidLinesForX[i]->Get_Y(x1);
			float fScope = std::abs((y1 - y0) / (x1 - x0));

			if (MAX_LIMIT_SCOPE > fScope)
			{
				vecValidLinesForScope.push_back(vecValidLinesForX[i]);
				vecValidLinesScopes.push_back(fScope);
			}
		}
		

		if (vecValidLinesForScope.size() == 0)
		{
			(*pY) = FLT_MAX;
			m_pCurrentLine = nullptr;
			return false;
		}

		// 그 중에서 기울기가 가장 작은 쪽을 먼저 선택해서 이동하기
		// 즉 계단을 타서 위로 올라가면 더 이상 계단을 타지 않음
		CLine* pMinScopeLine = vecValidLinesForScope[0];
		float fMinScope = vecValidLinesScopes[0];

		for (int i = 0; i < vecValidLinesForScope.size(); ++i)
		{
			float y1 = vecValidLinesForScope[i]->Get_Y(x1);
			float fScope = std::abs((y1 - y0) / (x1 - x0));
			
			if (fMinScope > fScope)
			{
				pMinScopeLine = vecValidLinesForScope[i];
				fMinScope = fScope;
			}
		}
		
		if (pMinScopeLine != nullptr)
		{
			(*pY) = pMinScopeLine->Get_Y(x1);
			m_pCurrentLine = pMinScopeLine;
			return true;
		}
		break;
	}
	}
	return false;
}

bool CLineMgr::Collision_Line_Enemy(float _fX, float _fSpeed, float _fFoot, float _fCY, float* pY, OBJ_STATUS _eObjStatus)
{
	vector<CLine*> vecValidLinesForX;
	for (auto& Line : m_LineList)
	{
		// 무조건 왼쪽 X가 오른쪽 X보다 작다고 가정
		bool bValidX = _fX >= Line->Get_Info().tLeft.fX && _fX <= Line->Get_Info().tRight.fX;
		if (bValidX)
		{
			vecValidLinesForX.push_back(Line);
		}
	}

	// 만약 X범위 내에서 없다면 앞으로 캐릭터가 서야 할 위치를 무한대로 설정
	if (vecValidLinesForX.size() == 0)
	{
		(*pY) = FLT_MAX;
		m_pCurrentLine = nullptr;
		return false;
	}

	// AI는 해당 선 범위 내에서만 움직일 수 있도록 설정하기

	switch (_eObjStatus)
	{
	default:
		float x0 = _fX - _fSpeed;
		float y0 = _fFoot + (_fCY / 2.0f);
		float x1 = _fX;

		// 다음 y값이 현재 y값보다 너무 큰 경우 (서로 떨어진 지형일 경우)
		// 걷지 못하도록 설정 (기울기를 이용해서)
		vector<CLine*> vecValidLinesForScope;
		vector<float> vecValidLinesScopes;
		for (int i = 0; i < vecValidLinesForX.size(); ++i)
		{
			float y1 = vecValidLinesForX[i]->Get_Y(x1);
			float fScope = std::abs((y1 - y0) / (x1 - x0));

			if (MAX_LIMIT_SCOPE > fScope)
			{
				vecValidLinesForScope.push_back(vecValidLinesForX[i]);
				vecValidLinesScopes.push_back(fScope);
			}
		}

		// 만약 폭탄에 휘말린다면? -> 그냥 벽쪽으로 날아가도록 설정하기
		if (vecValidLinesForScope.size() == 0)
		{
			(*pY) = FLT_MAX;
			m_pCurrentLine = nullptr;
			return false;
		}

		// 그 중에서 기울기가 가장 작은 쪽을 먼저 선택해서 이동하기
		// 즉 계단을 타서 위로 올라가면 더 이상 계단을 타지 않음
		CLine* pMinScopeLine = nullptr;
		float fMinScope = FLT_MAX;

		for (int i = 0; i < vecValidLinesForScope.size(); ++i)
		{
			float y1 = vecValidLinesForScope[i]->Get_Y(x1);
			float fScope = std::abs((y1 - y0) / (x1 - x0));

			if (fMinScope > fScope)
			{
				pMinScopeLine = vecValidLinesForScope[i];
				fMinScope = fScope;
			}
		}

		if (pMinScopeLine != nullptr)
		{
			(*pY) = pMinScopeLine->Get_Y(x1);
			m_pCurrentLine = pMinScopeLine;
			return true;
		}
		break;
	}

	return false;
}


void CLineMgr::Save_Line()
{
	HANDLE		hFile = CreateFile(L"../Data/Line4.dat",		// 파일 경로와 이름을 명시
		GENERIC_WRITE,			// 파일 접근 모드(GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
		NULL,					// 공유 방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈 할 때 허가하는 것에 대해서 설정(null 지정 시 공유하지 않음)
		NULL,					// 보안 속성, NULL인 기본 값 설정 유지
		CREATE_ALWAYS,			// 생성 방식( CREATE_ALWAYS : 파일이 없다면 생성, 있으면 덮어 쓰기, OPEN_EXISTING : 파일이 있을 경우에만 불러오기)
		FILE_ATTRIBUTE_NORMAL,	// 파일 속성( FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 파일)
		NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(사용하지 않기 때문에 NULL)



	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Save Failed", _T("error"), MB_OK);
		return;
	}

	DWORD	dwByte(0);
	

	for (auto& pLine : m_LineList)
	{
		STORED_LINE_DATA storedLineData = { pLine->Get_Info().tLeft, pLine->Get_Info().tRight, pLine->Get_Line_Type() };

		WriteFile(hFile, &(storedLineData), sizeof(STORED_LINE_DATA), &dwByte, nullptr);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"save 완료", L"Success", MB_OKCANCEL);
}

void CLineMgr::Load_Line()
{
	HANDLE		hFile = CreateFile(L"../Data/Line4.dat",		// 파일 경로와 이름을 명시
		GENERIC_READ,			// 파일 접근 모드(GENERIC_WRITE : 쓰기 전용, GENERIC_READ : 읽기 전용)
		NULL,					// 공유 방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈 할 때 허가하는 것에 대해서 설정(null 지정 시 공유하지 않음)
		NULL,					// 보안 속성, NULL인 기본 값 설정 유지
		OPEN_EXISTING,			// 생성 방식( CREATE_ALWAYS : 파일이 없다면 생성, 있으면 덮어 쓰기, OPEN_EXISTING : 파일이 있을 경우에만 불러오기)
		FILE_ATTRIBUTE_NORMAL,	// 파일 속성( FILE_ATTRIBUTE_NORMAL : 아무런 속성이 없는 파일)
		NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(사용하지 않기 때문에 NULL)

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Load Failed", _T("error"), MB_OK);
		return;
	}

	DWORD	dwByte(0);
	STORED_LINE_DATA tLine{};
	
	while (true)
	{
		ReadFile(hFile, &tLine, sizeof(STORED_LINE_DATA), &dwByte, nullptr);

		if (0 == dwByte)
			break;
		m_LineList.push_back(new CLine(tLine.tLeft, tLine.tRight, tLine.eLineType));
	}

	CloseHandle(hFile);
	//MessageBox(g_hWnd, L"load 완료", L"Success", MB_OKCANCEL);

}

void CLineMgr::Key_Input()
{
	// Edit Mode ON!
	if (CKeyMgr::Get_Instance()->Key_Down('K'))
	{
		printf("[+] Edit Mode On!");
		m_bEditMode = !m_bEditMode;
	}
	
	if (m_bEditMode == true)
	{
		if (CKeyMgr::Get_Instance()->Key_Down('U'))
		{
			Save_Line();
		}

		if (CKeyMgr::Get_Instance()->Key_Down('L'))
		{
			Load_Line();
		}

		if (CKeyMgr::Get_Instance()->Key_Down('B'))
		{
			m_eDrawLineType = LINE_TYPE::NORMAL;
		}

		if (CKeyMgr::Get_Instance()->Key_Down('N'))
		{
			m_eDrawLineType = LINE_TYPE::SOLID;
		}

		if (CKeyMgr::Get_Instance()->Key_Down('Z'))
		{
			m_LineList.pop_back();
		}
	}
}
