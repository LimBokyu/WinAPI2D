#include "framework.h"
#include "CBigHeart.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CResourceManager.h"
#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"

CBigHeart::CBigHeart()
{
	m_pAnimator = nullptr;
	m_pHeart = nullptr;
	m_layer = Layer::Item;
	m_strName = L"BigHeart";
}

CBigHeart::~CBigHeart()
{
}

void CBigHeart::Init()
{
	m_pAnimator = new CAnimator();

	m_pHeart = RESOURCE->LoadImg(L"BigHeart", L"Image\\Item\\BigHeart.png");

	m_pAnimator->CreateAnimation(L"BigHeart", m_pHeart, Vector(0, 0), Vector(12, 10), Vector(12, 0), 0.02f, 10, true);

	m_pAnimator->Play(L"BigHeart");
	AddComponent(m_pAnimator);
	AddCollider(ColliderType::Rect, Vector(20, 20), Vector(0, 0));
}

void CBigHeart::Update()
{
	m_vecPos.y += m_fVelocity * DT;
}

void CBigHeart::Render()
{
}

void CBigHeart::Release()
{
}

void CBigHeart::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"Tile")
	{
		m_fVelocity = 0;
	}
	else if (pOtherCollider->GetObjName() == L"Player")
	{
		DELETEOBJECT(this);
	}
}
