#include "pch.h"
#include "Obj.h"
#include "Camera.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "ThunderBreathingMgr.h"

CCamera* CCamera::m_pInstance = nullptr;

/*
���� ���� ��ǥ�� ������ ��ǥ ������ ��ġ�� ���� ī�޶� ��� �������� ���ΰ�?
���� �츮�� ī�޶� ��� ���� �ִٰ� �����ؾ� �ұ�?
�ػ� �� �߾� ��ġ�� ���� �־�� �Ѵ�.

*/
int countONe = 0;
void CCamera::Update()
{

	if (m_pTargetObj)
	{
		if (m_pTargetObj->Get_Dead())
		{
			/*
				���� Target�� ���� ��Ȳ�̶�� Ÿ���� ��������� �Ѵ�. -> īŸ���� �׷��ʿ� ����
			*/
			m_pTargetObj = nullptr;
		}
		else
		{
			// �Ѿƴٴϴ� Ÿ���� �ִٸ�, lookat�� �Ѿƴٴϴ� ����� ��ġ�� �����Ѵ�.
			m_vLookAt.fX = m_pTargetObj->Get_Info().fX;
			m_vLookAt.fY = m_pTargetObj->Get_Info().fY;
		}
	}
	


	// �÷��̾� ��ġ�� ���� ī�޶��� ��ġ�� �ٲٰ� �ϱ� (400 �̻� ����?, 300 �̻� ����?)
	//RECT tPlayerRect = m_pCameraTargetObj->Get_Render_Rect();

	if (CThunderBreathingMgr::Get_Instance()->Get_Player_Thunder_Breathing_Motion() == PLAYER_ATTACK)
	{
		int a = 3;
	}


	Key_Input();

	

	if (m_pCameraTargetObj != nullptr)
	{
		RECT tPlayerRenderRect = m_pCameraTargetObj->Get_Render_Rect();
		//
		if (tPlayerRenderRect.left > WINCX / 2.0f)
		{
			if (m_vLookAt.fX + m_fSmallerX < m_fLimitX - WINCX / 2.0f)
			{
				m_vLookAt.fX += m_fCameraSpeed;
				for (auto iter = (*m_pCameraTargetObj->Get_After_Image_Info()).begin(); iter != (*m_pCameraTargetObj->Get_After_Image_Info()).end(); ++iter)
				{
					(*iter).fX -= m_fCameraSpeed;

				}
			}
		}


		if (tPlayerRenderRect.right < WINCX / 2.0f)
		{
			if (m_vLookAt.fX - m_fSmallerX > WINCX / 2.0f)
			{
				m_vLookAt.fX -= m_fCameraSpeed;
				
				if (CThunderBreathingMgr::Get_Instance()->Get_ThunderBreathing_Mode())
				{
					int a = 3;
				}

				for (auto iter = (*m_pCameraTargetObj->Get_After_Image_Info()).begin(); iter != (*m_pCameraTargetObj->Get_After_Image_Info()).end(); ++iter)
				{
					(*iter).fX += m_fCameraSpeed;
				}
			}
		}

		SCENE_ID eSceneID = CSceneMgr::Get_Instance()->Get_Cur_Scene_ID();
		switch (eSceneID)
		{
		case SCENE_ID::SC_STAGE_02:
		{
			if (tPlayerRenderRect.top > WINCY / 2.0f)
			{
				m_vLookAt.fY += m_fCameraSpeed;
				if (m_vLookAt.fY > m_fLimitY - WINCY / 2.0f)
				{

					for (auto iter = (*m_pCameraTargetObj->Get_After_Image_Info()).begin(); iter != (*m_pCameraTargetObj->Get_After_Image_Info()).end(); ++iter)
					{
						(*iter).fY -= m_fCameraSpeed;
					}
				}
			}
			break;
		}
		default:
		{
			if (tPlayerRenderRect.top > WINCY / 2.0f)
			{
				if (m_vLookAt.fY > m_fLimitY - WINCY / 2.0f)
				{
					m_vLookAt.fY += m_fCameraSpeed;
					for (auto iter = (*m_pCameraTargetObj->Get_After_Image_Info()).begin(); iter != (*m_pCameraTargetObj->Get_After_Image_Info()).end(); ++iter)
					{
						(*iter).fY -= m_fCameraSpeed;
					}
				}
			}
			break;
		}
		}

		if (tPlayerRenderRect.bottom < WINCY / 2.0f)
		{
			if (m_vLookAt.fY < WINCY / 2.0f)
			{
				m_vLookAt.fY -= m_fCameraSpeed;
				for (auto iter = (*m_pCameraTargetObj->Get_After_Image_Info()).begin(); iter != (*m_pCameraTargetObj->Get_After_Image_Info()).end(); ++iter)
				{
					(*iter).fY += m_fCameraSpeed;
				}
			}
		}
	}




	// ī�޶�� �� ������Ʈ���� 
	// ȭ�� �߾� ��ǥ�� LookAt ��ǥ���� ���̰��� ����Ұ��̴�.

}

void CCamera::Late_Update()
{

	if (m_vLookAt.fX < WINCX / 2.0f)
	{
		m_vLookAt.fX = WINCX / 2.0f;
	}

	if (m_vLookAt.fY < WINCY / 2.0f)
	{
		m_vLookAt.fY = WINCY / 2.0f;
	}

	if (m_fLimitX == -1.0f)
	{
		m_vLookAt.fX = m_vLookAt.fX;
	}
	else
	{
		if (m_vLookAt.fX > m_fLimitX - WINCX / 2.0f)
		{
			m_vLookAt.fX = m_fLimitX - WINCX / 2.0f;
		}
	}

	if (m_fLimitY == -1.0f)
	{
		m_vLookAt.fY = m_vLookAt.fY;
	}
	else
	{
		if (m_vLookAt.fY > m_fLimitY - WINCY / 2.0f)
		{
			m_vLookAt.fY = m_fLimitY - WINCY / 2.0f;
		}
	}


	CalDiff();

	//printf("%d\n", m_bShake);
	// ī�޶� ��鸲 ���ֱ�
	if (m_bShake == true)
	{
		DWORD currentTickCount = GetTickCount();
		if (dwShakeTime + 250 < currentTickCount)
		{
			m_vLookAt.fX = beforeShakeLookAt.fX;
			m_vLookAt.fY = beforeShakeLookAt.fY;
			m_bShake = false;
		}
		else
		{
			float fPivotX = beforeShakeLookAt.fX;
			float fPivotY = beforeShakeLookAt.fY;

			float fMinX = fPivotX - m_fShakeRadius / 2.0f;
			float fMinY = fPivotY - m_fShakeRadius / 2.0f;

			float fNextX = fMinX + (rand() % (int)m_fShakeRadius);
			float fNextY = fMinY + (rand() % (int)m_fShakeRadius);

			m_vLookAt.fX = fNextX;
			m_vLookAt.fY = fNextY;
		}
	}

}



void CCamera::Set_LookAt(float _fX, float _fY)
{
	m_vLookAt.fX = _fX;
	m_vLookAt.fY = _fY;
}

void CCamera::Camera_Shaking()
{
	if (m_bShake == false)
	{
		beforeShakeLookAt.fX = m_vLookAt.fX;
		beforeShakeLookAt.fY = m_vLookAt.fY;
		m_bShake = true;
		dwShakeTime = GetTickCount();
	}

	//float iOffSetX = (float)(-10 + rand() % 10);

	float fPivotX = beforeShakeLookAt.fX;
	float fPivotY = beforeShakeLookAt.fY;
	float fShakeRadius = 38.f;

	float fMinX = fPivotX - m_fShakeRadius / 1.5f;
	float fMinY = fPivotY - m_fShakeRadius / 6.0f;

	float fNextX = fMinX + (rand() % (int)m_fShakeRadius);
	float fNextY = fMinY + (rand() % (int)m_fShakeRadius);

	m_vLookAt.fX = fNextX;
	m_vLookAt.fY = fNextY;
	
}

void CCamera::Camera_Zoomin()
{
	HDC tempDC = GetDC(g_hWnd);

}

Vec2 CCamera::GetRenderPos(Vec2 _vObjPos)
{
	Vec2 vRenderPos = {
		_vObjPos.fX - m_vDiff.fX,
		_vObjPos.fY - m_vDiff.fY
	};
	return vRenderPos;
}

Vec2 CCamera::GetRealPos(Vec2 _vRenderPos)
{
	Vec2 vRealPos = {
		_vRenderPos.fX + m_vDiff.fX,
		_vRenderPos.fY + m_vDiff.fY
	};
	return vRealPos;
}

void CCamera::Set_Target(CObj* _pTarget)
{
	m_pTargetObj = _pTarget;
}

void CCamera::Camera_Lock()
{
	
}

void CCamera::Set_Camera_Target(CObj* _pTarget)
{
	m_pCameraTargetObj = _pTarget;
}

void CCamera::CalDiff()
{
	Vec2 vCenter = { WINCX / 2.0f, WINCY / 2.0f };
	m_vDiff.fX = m_vLookAt.fX - vCenter.fX;
	m_vDiff.fY = m_vLookAt.fY - vCenter.fY;
}

void CCamera::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Press(VK_UP))
	{
		m_vLookAt.fY -= m_fCameraSpeed;
	}

	if (CKeyMgr::Get_Instance()->Key_Press(VK_LEFT))
	{
		m_vLookAt.fX -= m_fCameraSpeed;
	}

	if (CKeyMgr::Get_Instance()->Key_Press(VK_DOWN))
	{
		m_vLookAt.fY += m_fCameraSpeed;
	}

	if (CKeyMgr::Get_Instance()->Key_Press(VK_RIGHT))
	{
		m_vLookAt.fX += m_fCameraSpeed;
	}

	
}
