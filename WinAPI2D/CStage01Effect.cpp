#include "framework.h"
#include "CSceneStage01.h"
#include "CStage01Effect.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"
#include "CPathManager.h"
#include "CStage01Map.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CCameraController.h"
#include "CButton.h"
#include "CPanel.h"

CStage01Effect::CStage01Effect()
{
	m_layer = Layer::MiddleMap;
	m_Fire01 = nullptr;
	m_pAnimator = nullptr;
}

CStage01Effect::~CStage01Effect()
{
}

void CStage01Effect::Init()
{
	m_Fire01 = RESOURCE->LoadImg(L"stage01_Effect1", L"Image\\Stage\\Stage_01Effect01.png");
	
	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"stage01_Effect1", m_Fire01, Vector(0.f, 0.f), Vector(1050.f, 50.f), Vector(0.f, 50.f), 0.09f, 4);

	m_pAnimator->Play(L"stage01_Effect1", false);
	AddComponent(m_pAnimator);

}

void CStage01Effect::Update()
{
}

void CStage01Effect::Render()
{
}

void CStage01Effect::Release()
{
}
