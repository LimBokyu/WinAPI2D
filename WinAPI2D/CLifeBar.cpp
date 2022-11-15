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
	pPlayer = nullptr;
	m_pLifeBar = nullptr;
	m_pLifeBarGauge = nullptr;

	m_pItemDagger = nullptr;
	m_pItemAxe = nullptr;
	m_pItemBible = nullptr;
	m_pItemHollyWater = nullptr;
	m_pItemCross = nullptr;
	m_pItemClock = nullptr;

	m_layer = Layer::Interface;
	curLookAt = Vector(WINSIZEX/2,WINSIZEY/2);
	FirstLookAt = Vector(WINSIZEX / 2, WINSIZEY / 2);
}
CLifeBar::~CLifeBar()
{
}

void CLifeBar::Init()
{
	m_pLifeBar = RESOURCE->LoadImg(L"LifeBar", L"Image\\LifeBar.png");
	m_pLifeBarGauge = RESOURCE->LoadImg(L"LifeBarGauge", L"Image\\LifeBarFull.png");

	m_pItemDagger = RESOURCE->LoadImg(L"Dagger", L"Image\\ItemDagger.png");
	m_pItemAxe = RESOURCE->LoadImg(L"Axe", L"Image\\ItemAxe.png");
	m_pItemBible = RESOURCE->LoadImg(L"Bible", L"Image\\ItemBible.png");
	m_pItemClock = RESOURCE->LoadImg(L"Clock", L"Image\\ItemClock.png");
	m_pItemCross = RESOURCE->LoadImg(L"Cross", L"Image\\ItemCross.png");
	m_pItemHollyWater = RESOURCE->LoadImg(L"HollyWater", L"Image\\ItemHollyWater.png");
	
}

void CLifeBar::Update()
{
	curLookAt = CAMERA->GetLookAt();
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

void CLifeBar::SetPlayer(CPlayer* player)
{
	pPlayer = player;
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
			curLookAt.y - FirstLookAt.y + 42,
			curLookAt.x - FirstLookAt.x + m_pItemDagger->GetWidth() * 2 + 36,
			curLookAt.y - FirstLookAt.y + m_pItemDagger->GetHeight() * 2 + 42);
		break;

	case PlayerITEM::Axe:
		RENDER->Image(m_pItemAxe,
		curLookAt.x - FirstLookAt.x + 36,
		curLookAt.y - FirstLookAt.y + 42,
		curLookAt.x - FirstLookAt.x + m_pItemAxe->GetWidth() * 2 + 36,
		curLookAt.y - FirstLookAt.y + m_pItemAxe->GetHeight() * 2 + 42);
		break;

	case PlayerITEM::HolyWater:
		RENDER->Image(m_pItemHollyWater,
			curLookAt.x - FirstLookAt.x + 36,
			curLookAt.y - FirstLookAt.y + 42,
			curLookAt.x - FirstLookAt.x + m_pItemHollyWater->GetWidth() * 2 + 36,
			curLookAt.y - FirstLookAt.y + m_pItemHollyWater->GetHeight() * 2 + 42);
		break;

	case PlayerITEM::Cross:
		RENDER->Image(m_pItemCross,
			curLookAt.x - FirstLookAt.x + 36,
			curLookAt.y - FirstLookAt.y + 42,
			curLookAt.x - FirstLookAt.x + m_pItemCross->GetWidth() * 2 + 36,
			curLookAt.y - FirstLookAt.y + m_pItemCross->GetHeight() * 2 + 42);
		break;
	case PlayerITEM::Clock:
		RENDER->Image(m_pItemClock,
			curLookAt.x - FirstLookAt.x + 36,
			curLookAt.y - FirstLookAt.y + 42,
			curLookAt.x - FirstLookAt.x + m_pItemClock->GetWidth() * 2 + 36,
			curLookAt.y - FirstLookAt.y + m_pItemClock->GetHeight() * 2 + 42);

	case PlayerITEM::Bible:
		RENDER->Image(m_pItemBible,
			curLookAt.x - FirstLookAt.x + 36,
			curLookAt.y - FirstLookAt.y + 42,
			curLookAt.x - FirstLookAt.x + m_pItemBible->GetWidth() * 2 + 36,
			curLookAt.y - FirstLookAt.y + m_pItemBible->GetHeight() * 2 + 42);
	case PlayerITEM::Size:
		break;
	}
}