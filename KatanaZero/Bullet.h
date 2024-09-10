#pragma once

#include "Obj.h"
class CBullet : public CObj
{
public:
	CBullet();
	virtual ~CBullet();


public:
	// CObj을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

public:
	bool Get_Pairing() { return m_bPairing; }
	void Set_Pairing(bool _bPairing) { m_bPairing = _bPairing; }

	void Update_Collide_Rect_For_Bullet();
	
private:

	bool m_bPairing = false;
};

