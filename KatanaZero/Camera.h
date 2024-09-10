#pragma once

class CObj;
class CCamera
{
private:
	CCamera() : m_pTargetObj(nullptr), m_fCameraSpeed(5.f), m_pCameraTargetObj(nullptr) {}
	~CCamera() {}

public:
	static CCamera* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CCamera;
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

public:
	void Update();
	void Late_Update();
	void Set_LookAt(float _fX, float _fY);

	void Camera_Shaking();
	void Camera_Zoomin();
	

	void Set_LookAt(Vec2 _vLookAt) { m_vLookAt = _vLookAt; }
	void Set_PrevLookAt(Vec2 _vPrevLookAt) { m_vPrevLookAt = _vPrevLookAt; }
	void Set_m_vDiff(Vec2 _vDiff) { m_vDiff; }

	Vec2 Get_LookAt() { return m_vLookAt; }
	Vec2 GetRenderPos(Vec2 _vObjPos);
	Vec2 GetRealPos(Vec2 _vRenderPos);
	void Set_Target(CObj* _pTarget);

	void Camera_Lock();
	void Set_SmallerX(float _fSmallerX) { m_fSmallerX = _fSmallerX; }
	
	void Set_Camera_Target(CObj* _pTarget);
	

public:
	Vec2 Get_PrevLookAt() { return m_vPrevLookAt; }
	Vec2 Get_Diff() { return m_vDiff; }

public:
	void CalDiff();
	void Set_Limit_X(float _fLimitX) { m_fLimitX = _fLimitX; }
	void Set_Limit_Y(float _fLimitY) { m_fLimitY = _fLimitY; }

private:
	void Key_Input();

private:
	static CCamera* m_pInstance;

private:
	Vec2 m_vLookAt; // 카메라가 보는 위치
	Vec2 m_vPrevLookAt;
	Vec2 m_vDiff; // 
	CObj* m_pTargetObj; // 카메라 타켓 오브젝트 (어소트)
	
	
	CObj* m_pCameraTargetObj;

	float m_fCameraSpeed;

	float m_fLimitX = -1.0f;
	float m_fLimitY = -1.0f;

	float m_fSmallerX = 0.f;
	float m_fShakeRadius = 12.f;

	bool m_bShake = false;


	Vec2 beforeShakeLookAt;
	DWORD dwShakeTime;
};

