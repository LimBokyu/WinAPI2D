#include "framework.h"
#include "CSceneStage01.h"
#include "CStage01Effect2.h"

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

CStage01Effect2::CStage01Effect2()
{
	m_layer = Layer::FarMap;
	m_pAnimator = nullptr;
	m_pImage = nullptr;
}

CStage01Effect2::~CStage01Effect2()
{
}

void CStage01Effect2::Init()
{
	m_pImage = RESOURCE->LoadImg(L"stage01_Effect2", L"Image\\Stage\\Stage_01Effect02.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"stage01_Effect2", m_pImage, Vector(0.f, 0.f), Vector(1200.f, 100.f), Vector(0.f, 100.f), 0.09f, 4);

	m_pAnimator->Play(L"stage01_Effect2", false);
	AddComponent(m_pAnimator);
}

void CStage01Effect2::Update()
{
}

void CStage01Effect2::Render()
{
}

void CStage01Effect2::Release()
{
}
