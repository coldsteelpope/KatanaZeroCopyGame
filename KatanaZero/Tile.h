#pragma once

#include "Obj.h"
class CTile : public CObj
{
public:
	CTile();
	virtual ~CTile();
public:
	void Set_DrawID(TILE_TYPE _iDrawID) { m_iDrawID = _iDrawID; }
	void Set_Option(TILE_TYPE _iOption) { m_iOption = _iOption; }

	TILE_TYPE Get_DrawID() { return m_iDrawID; }
	TILE_TYPE Get_Option() { return m_iOption; }

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:
	TILE_TYPE m_iDrawID;
	TILE_TYPE m_iOption;
};

