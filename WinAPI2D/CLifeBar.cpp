#include "framework.h"
#include "CLifeBar.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CResourceManager.h"
#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"
#include "CPlayer.h"
#include "CGameObject.h"

CLifeBar::CLifeBar()
{
	pPlayer = new CPlayer();
	m_pLifeBar = nullptr;
	m_pLifeBarGauge = nullptr;
	m_pHeart = nullptr;
	m_pAnimator = nullptr;

	m_pItemDagger = nullptr;
	m_pItemAxe = nullptr;

	m_layer = Layer::Interface;
	curLookAt = Vector(WINSIZEX/2,WINSIZEY/2);
	FirstLookAt = Vector(WINSIZEX / 2, WINSIZEY / 2);
}
CLifeBar::~CLifeBar()
{
}

void CLifeBar::Init()
{
	m_pAnimator = new CAnimator();

	m_pLifeBar = RESOURCE->LoadImg(L"LifeBar", L"Image\\LifeBar.png");
	m_pLifeBarGauge = RESOURCE->LoadImg(L"LifeBarGauge", L"Image\\LifeBarFull.png");
	m_pHeart = RESOURCE->LoadImg(L"LifeBarHeart", L"Image\\LifeBarHeart.png");
	m_pItemDagger = RESOURCE->LoadImg(L"Dagger", L"Image\\ItemDagger.png");
	m_pItemAxe = RESOURCE->LoadImg(L"Axe", L"Image\\ItemAxe.png");

	m_pAnimator->CreateAnimation(L"Heart:Zero",  m_pHeart,	 Vector(0, 0),	 Vector(6, 6),  Vector(0, 9), 0.05f, 4);
	m_pAnimator->CreateAnimation(L"Heart:One",   m_pHeart,	 Vector(9, 0),	 Vector(15, 6), Vector(0, 9), 0.05f, 4);
	m_pAnimator->CreateAnimation(L"Heart:Two",   m_pHeart,	 Vector(18, 0),	 Vector(24, 6), Vector(0, 9), 0.05f, 4);
	m_pAnimator->CreateAnimation(L"Heart:Three", m_pHeart,	 Vector(27, 0),	 Vector(33, 6), Vector(0, 9), 0.05f, 4);
	m_pAnimator->CreateAnimation(L"Heart:Four",  m_pHeart,	 Vector(36, 0),	 Vector(42, 6), Vector(0, 9), 0.05f, 4);
	m_pAnimator->CreateAnimation(L"Heart:Five",  m_pHeart,	 Vector(45, 0),	 Vector(51, 6), Vector(0, 9), 0.05f, 4);
	m_pAnimator->CreateAnimation(L"Heart:Six",   m_pHeart,	 Vector(54, 0),	 Vector(60, 6), Vector(0, 9), 0.05f, 4);
	m_pAnimator->CreateAnimation(L"Heart:Seven", m_pHeart,	 Vector(63, 0),	 Vector(69, 6), Vector(0, 9), 0.05f, 4);
	m_pAnimator->CreateAnimation(L"Heart:Eight", m_pHeart,	 Vector(72, 0),	 Vector(78, 6), Vector(0, 9), 0.05f, 4);
	m_pAnimator->CreateAnimation(L"Heart:Nine",  m_pHeart,	 Vector(81, 0),	 Vector(87, 6), Vector(0, 9), 0.05f, 4);

	//m_pAnimator->Play(L"Heart:Zero");
}

void CLifeBar::Update()
{
	curLookAt = CAMERA->GetLookAt();

	UpdateAnimation();
	
}

void CLifeBar::Render()
{
	RENDER->Image(m_pLifeBar,
		curLookAt.x - FirstLookAt.x + 10,
		curLookAt.y - FirstLookAt.y + 20,
		curLookAt.x - FirstLookAt.x + m_pLifeBar->GetWidth()*2 + 10,
		curLookAt.y - FirstLookAt.y + m_pLifeBar->GetHeight()*2 + 20);

	RENDER->FrameImage(m_pLifeBarGauge,
		curLookAt.x - FirstLookAt.x + 17,
		curLookAt.y - FirstLookAt.y + 24,
		curLookAt.x - FirstLookAt.x + m_pLifeBarGauge->GetWidth()*2 + 17,
		curLookAt.y - FirstLookAt.y + m_pLifeBarGauge->GetHeight() * 2 + 24,
		0,0,
		4,93
		);
	ItemUpdate();
}
void CLifeBar::Release()
{

}

void CLifeBar::New()
{

}

void CLifeBar::Score()
{

}

void CLifeBar::UpdateAnimation()
{

}

void CLifeBar::ItemUpdate()
{
	switch (pPlayer->GetItem())
	{
	case PlayerITEM::None:

		break;
	case PlayerITEM::Dagger:
		RENDER->Image(m_pItemDagger,
			curLookAt.x - FirstLookAt.x + 36,
			curLookAt.y - FirstLookAt.y + 41,
			curLookAt.x - FirstLookAt.x + m_pItemDagger->GetWidth() * 2 + 36,
			curLookAt.y - FirstLookAt.y + m_pItemDagger->GetHeight() * 2 + 41);
		break;
	case PlayerITEM::Axe:

		break;
	case PlayerITEM::HolyWater:

		break;

	case PlayerITEM::Cross:

		break;
	}
}