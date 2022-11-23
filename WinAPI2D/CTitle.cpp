#include "framework.h"

#include "WinAPI.h"
#include "CRenderManager.h"
#include "CInputManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"
#include "CTitle.h"

CTitle::CTitle()
{
	m_pAnimator = nullptr;
	m_pTitle = nullptr;
	m_bTrigger = false;
}

CTitle::~CTitle()
{
}

void CTitle::Init()
{
	m_pAnimator = new CAnimator();
	m_pTitle = RESOURCE->LoadImg(L"Title", L"Image\\Title.png");

	m_pAnimator->CreateAnimation(L"TitleIdle", m_pTitle, Vector(0, 0), Vector(256, 224), Vector(256, 0), 0.5f, 2, true);
	m_pAnimator->CreateAnimation(L"TitleFast", m_pTitle, Vector(0, 0), Vector(256, 224), Vector(256, 0), 0.2f, 2, true);

	m_pAnimator->Play(L"TitleIdle");
	AddComponent(m_pAnimator);
}

void CTitle::Render()
{
}

void CTitle::Release()
{
}

void CTitle::Update()
{
	UpdateAnimation();
}


void CTitle::SetTrigger(bool trigger)
{
	m_bTrigger = trigger;
}

void CTitle::UpdateAnimation()
{
	wstring str = L"Title";

	if (m_bTrigger)
	{
		str += L"Fast";
	}
	else
	{
		str += L"Idle";
	}

	m_pAnimator->Play(str);
}
