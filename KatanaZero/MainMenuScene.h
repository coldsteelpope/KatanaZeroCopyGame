#pragma once

#include "Scene.h"
class CMainMenuScene : public CScene
{
public:
	CMainMenuScene();
	virtual ~CMainMenuScene();

public:
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC _hDC) override;

	void Release() override;

public:
	void Key_Input();
};

