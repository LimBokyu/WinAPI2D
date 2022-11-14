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
	m_pLifeBar = nullptr;
	m_pLifeBarGauge = nullptr;
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

	//RENDER->FrameImage(m_pLifeBarGauge,
	//	curLookAt.x - FirstLookAt.x + 20,
	//	curLookAt.y - FirstLookAt.y + 25,
	//	curLookAt.x - FirstLookAt.x + m_pLifeBarGauge->GetWidth()*2 + 20,
	//	curLookAt.y - FirstLookAt.y + m_pLifeBarGauge->GetHeight() * 2 + 25,

	//	);
}
void CLifeBar::Release()
{

}