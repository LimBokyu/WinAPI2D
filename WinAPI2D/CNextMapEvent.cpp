#include "framework.h"
#include "CNextMapEvent.h"
#include "CStage01_1.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"
#include "CPathManager.h"

#include "CPlayer.h"

CNextMapEvent::CNextMapEvent()
{
	m_vecPos = Vector(1800, WINSIZEY * 0.5f);
}

CNextMapEvent::~CNextMapEvent()
{
}

void CNextMapEvent::Init()
{
	AddCollider(ColliderType::Rect, Vector(50, WINSIZEY), Vector(0, 0));
}

void CNextMapEvent::Update()
{
}

void CNextMapEvent::Render()
{
}

void CNextMapEvent::Release()
{
}

void CNextMapEvent::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"Player")
	{
		// TODO : 다음맵으로 넘어가는 강제 이벤트 발생
	}
}
