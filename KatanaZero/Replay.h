#pragma once

#include "Scene.h"

class CCameraMemento;
class CMemento;
class CCameraMemento;
class CEnemyMemento;
class CItemMemento;
class CBloodMemento;
class CDoorMemento;
class CBulletMemento;

class CReplay : public CScene
{
public:
	enum REPLAY_STATUS
	{
		PLAY,
		REWIND,
		STOP,
		REPLAY_STATUS_END
	};

public:
	CReplay();
	virtual ~CReplay();
public:
	// CScene��(��) ���� ��ӵ�
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

public:
	void Key_Input();

private:

	bool bRewind = false;
	// �ǰ��⸦ ���ؼ� ����Ѵ�
	vector<CCameraMemento*> m_vCameraStack;
	vector<CMemento*> m_vPlayerStack;
	vector<CMemento*> m_vEffectStack;
	vector<CEnemyMemento*> m_vEnemyStack;
	vector<CItemMemento*> m_vItemStack;
	vector<CBloodMemento*> m_vBloodStack;
	vector<CDoorMemento*> m_vDoorStack;
	vector<CBulletMemento*> m_vBulletStack;

	REPLAY_STATUS m_eReplayStatus = PLAY;


	DWORD dwYouCanDoThisTime;
	bool m_bShowVideo = false;

	SCENE_ID eReplaySceneID;
};

