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
	m_MiddleMap = nullptr;
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

	m_MiddleMap = RESOURCE->LoadImg(L"stage01_map2", L"Image\\Stage_01M.png");

	startLook = Vector(WINSIZEX * 0.5, WINSIZEY * 0.5);
	curLook = CAMERA->GetLookAt();
}

void CStage01Effect3::Update()
{
	curLook = CAMERA->GetLookAt();
	Vector diff = (curLook - startLook) * 0.625f;
	m_vecPos = diff + Vector(465, 130);
	// 화면 스크롤 비율 0.625
	// 애니메이션 VEC 설정 X 465 Y 130
}

void CStage01Effect3::Render()
{
	RENDER->Image(
		m_MiddleMap,
		m_vecPos.x - 465,
		m_vecPos.y - 130 + 480 - (168 * 2),
		m_vecPos.x - 465 + m_MiddleMap->GetWidth() * 2,
		m_vecPos.y - 130 + (WINSIZEY - (168 * 2)) - (m_MiddleMap->GetHeight() * 2));
}

void CStage01Effect3::Release()
{
}
