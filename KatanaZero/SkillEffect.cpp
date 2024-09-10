#include "pch.h"
#include "BmpMgr.h"
#include "SkillEffect.h"

#define SKILL_EFFECT_FCX 800
#define SKILL_EFFECT_FCY 176

CSkillEffect::CSkillEffect()
{
}

CSkillEffect::~CSkillEffect()
{
	Release();
}

void CSkillEffect::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/effect/ThunderBreathingImage.bmp", L"THUNDER_BREATHING_IMAGE");
	
}

int CSkillEffect::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	return OBJ_NO_EVENT;
}

void CSkillEffect::Late_Update()
{
	
}

void CSkillEffect::Render(HDC _hDC)
{
	HDC skillEffectDC = CBmpMgr::Get_Instance()->Find_Img(L"THUNDER_BREATHING_IMAGE");

	Vec2 renderPos = CCamera::Get_Instance()->GetRenderPos(Vec2{ WINCX / 2.0f, WINCY / 2.0f });
	RECT renderRect = {
		renderPos.fX - SKILL_EFFECT_FCX / 2.0f,
		renderPos.fY - SKILL_EFFECT_FCY / 2.0f,
		renderPos.fX + SKILL_EFFECT_FCX / 2.0f,
		renderPos.fY + SKILL_EFFECT_FCY / 2.0f
	};

	GdiTransparentBlt(
		_hDC,
		renderRect.left,
		renderRect.top,
		SKILL_EFFECT_FCX,
		SKILL_EFFECT_FCY,
		skillEffectDC,
		0, 0,
		SKILL_EFFECT_FCX,
		SKILL_EFFECT_FCY,
		RGB(255, 0, 255)
	);
}

void CSkillEffect::Release()
{

}
