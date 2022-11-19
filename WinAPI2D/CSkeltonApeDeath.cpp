#include "framework.h"
#include "CSkeltonApeDeath.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CResourceManager.h"
#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"

CSkeltonApeDeath::CSkeltonApeDeath()
{
	m_layer = Layer::Monster;
	m_pAnimator = nullptr;
	m_pDeathImage = nullptr;
}

CSkeltonApeDeath::~CSkeltonApeDeath()
{
}

void CSkeltonApeDeath::Init()
{
	m_pAnimator = new CAnimator;
	m_pDeathImage = RESOURCE->LoadImg(L"SkeltonApeDeath", 
		L"Image\\Monster\\SkeltonApe\\SkeltonApeDeath.png");

	m_pAnimator->CreateAnimation(L"SkeltonApeDeath", m_pDeathImage, Vector(0, 0), Vector(40, 80), Vector(40, 0), 0.07f, 8, false);
	m_pAnimator->Play(L"SkeltonApeDeath");
	AddComponent(m_pAnimator);
}

void CSkeltonApeDeath::Update()
{
	m_fTimer += DT;
	if (m_fTimer > 0.56f)
	{
		DELETEOBJECT(this);
	}
}

void CSkeltonApeDeath::Render()
{
}

void CSkeltonApeDeath::Release()
{
}
