#pragma once
class CBulletPairingHitMgr
{
private:
	CBulletPairingHitMgr();
	virtual ~CBulletPairingHitMgr();
public:
	void Set_Bullet_Pivot_Pos(float _fX, float _fY);
	void Set_Pairing_Bullet_Event(bool _bPairingBulletEvent) { m_bPairingBulletEvent = _bPairingBulletEvent; }
	bool Get_Pairing_Bullet_Event() { return m_bPairingBulletEvent; }

public:
	static CBulletPairingHitMgr* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CBulletPairingHitMgr;
		}
		return m_pInstance;
	}

	static void Destory_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static CBulletPairingHitMgr* m_pInstance;

	// 총알이 상대방에게 맞아 사라질 때, 다시 false로 바꿔주기
	bool m_bPairingBulletEvent = false;
	float m_fX;
	float m_fY;
	
};

