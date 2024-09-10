#pragma once
class CLine
{
public:

public:
	CLine();
	CLine(LINEPOINT& tLeft, LINEPOINT& tRight, LINE_TYPE _eLineType);
	~CLine();
public:
	LINE Get_Info() { return m_tInfo; }
	void Render(HDC _hDC);

	float Get_Scope();
	float Get_Y(float _fX);

	
	LINE_TYPE Get_Line_Type() { return m_eType; }

private:
	LINE_TYPE m_eType;
	LINE m_tInfo;
};

