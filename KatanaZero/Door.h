#pragma once

#include "Obj.h"
class CDoor : public CObj
{
public:
	CDoor();
	virtual ~CDoor();
public:
	// CObj��(��) ���� ��ӵ�
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

public:
	void Update_Collide_Rect_For_Door();

	DOOR_TYPE Get_Door_Type() { return m_eDoorType; }
	void Set_Door_Type(DOOR_TYPE _eDoorType) { m_eDoorType = _eDoorType; }
	void Manage_Status();

private:
	DOOR_TYPE m_eDoorType = DOOR_TYPE::CLOSE;
};

