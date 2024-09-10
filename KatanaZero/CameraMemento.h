#pragma once
class CCameraMemento
{
public:
	CCameraMemento();
	CCameraMemento(Vec2 _vLookAt, Vec2 _vPrevLookAt, Vec2 _vDiff, LONG64 _llFrameCount);
	~CCameraMemento();
public:
	Vec2 Get_Look_At() { return m_vLookAt; }
	Vec2 Get_Prev_Look_At() { return m_vPrevLookAt; }
	Vec2 Get_Diff() { return m_vDiff; }
	LONG64 Get_Frame_Count() { return m_llFrameCount; }

private:
	Vec2 m_vLookAt;
	Vec2 m_vPrevLookAt;
	Vec2 m_vDiff;
	LONG64 m_llFrameCount;
};

