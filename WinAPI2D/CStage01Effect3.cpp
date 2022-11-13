#include "framework.h"
#include "CSceneStage01.h"
#include "CStage01Effect3.h"

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

CStage01Effect3::CStage01Effect3()
{
	m_layer = Layer::FarMap;
	m_pAnimator = nullptr;
	m_pImage = nullptr;
}

CStage01Effect3::~CStage01Effect3()
{
}

void CStage01Effect3::Init()
{
	m_pAnimator = new CAnimator();
	m_pImage = RESOURCE->LoadImg(L"stage01_Effect3", L"Image\\Stage_01Effect03.png");

	m_pAnimator->CreateAnimation(L"stage01_Effect3", m_pImage, Vector(0.f, 0.f), Vector(466.f, 12.f), Vector(0.f, 12.f), 0.08f, 3);

	m_pAnimator->Play(L"stage01_Effect3", false);
	AddComponent(m_pAnimator);
}

void CStage01Effect3::Update()
{
}

void CStage01Effect3::Render()
{
}

void CStage01Effect3::Release()
{
}
