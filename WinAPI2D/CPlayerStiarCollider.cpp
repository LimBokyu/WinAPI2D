#include "framework.h"

#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CEventManager.h"
#include "CCollider.h"
#include "CPlayer.h"
#include "CPlayerStiarCollider.h"

CPlayerStiarCollider::CPlayerStiarCollider()
{
	m_layer = Layer::Player;
}

CPlayerStiarCollider::~CPlayerStiarCollider()
{
}

void CPlayerStiarCollider::Init()
{
	AddCollider(ColliderType::Rect, Vector(10, 50), Vector(0, 0));
}

void CPlayerStiarCollider::Update()
{
	m_vecPos = pPlayer->GetPos();
}

void CPlayerStiarCollider::Render()
{
}

void CPlayerStiarCollider::Release()
{
}

void CPlayerStiarCollider::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"Stair")
	{
		pPlayer->SetStairCollider(true);
	}
}

void CPlayerStiarCollider::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CPlayerStiarCollider::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"Stair")
	{
		pPlayer->SetStairCollider(false);
	}
}
