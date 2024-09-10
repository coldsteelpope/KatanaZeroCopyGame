#pragma once

#include "Obj.h"
class CBossBullet : public CObj
{
public:
	CBossBullet();
	virtual ~CBossBullet();

public:
	// CObj을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

public:
	void Update_Collide_Rect_For_Boss_Bullet();


private:
	POINT RotatePoint(POINT p, POINT center, float angle);
	void RotateRect(RECT* rect, POINT center, float angle, POINT* points);
};

