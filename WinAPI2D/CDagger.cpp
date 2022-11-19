#include "framework.h"
#include "CDagger.h"

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

CDagger::CDagger()
{
	m_layer = Layer::Item;

	m_pAnimator = nullptr;
	m_pDagger = nullptr;
	pPlayer = nullptr;

	m_bChanged = false;
	m_bDelete = false;
	m_bTouchAble = true;
}

CDagger::~CDagger()
{
}

void CDagger::Init()
{
	m_pAnimator = new CAnimator;
	m_pDagger = RESOURCE->LoadImg(L"DaggerAni", L"Image\\Item\\Dagger.png");

	m_pAnimator->CreateAnimation(L"DaggerIdle", m_pDagger, Vector(0, 0), Vector(16, 21), Vector(16, 0), 1, 1, false);
	m_pAnimator->CreateAnimation(L"DaggerTwinkle", m_pDagger, Vector(0, 0), Vector(16, 21), Vector(16, 0), 0.02f, 2, true);

	m_pAnimator->Play(L"DaggerIdle");

	AddComponent(m_pAnimator);
	AddCollider(ColliderType::Rect, Vector(16, 16), Vector(0, 0));
}

void CDagger::Update()
{
	m_vecPos.y += m_fSpeed * DT;

	if (m_bChanged)
	{
		if (!pPlayer->GetReverse())
		{
			m_vecPos.x -= m_fThrow * DT;
		}
		else
		{
			m_vecPos.x += m_fThrow * DT;
		}
		
		if (m_fTimer > 0.1f && !m_fThrow == 0)
		{
			m_fThrow -= 2;
		}
	}

	if (m_bChanged && m_bDelete)
	{
		m_fTimer += DT;
		if (m_fTimer >= 2)
		{
			DELETEOBJECT(this);
		}
	}
	else if (m_bDelete)
	{
		m_fTimer += DT;
		if (m_fTimer >= 5)
		{
			DELETEOBJECT(this);
		}
	}
	UpdateAnimation();
}

void CDagger::Render()
{
}

void CDagger::Release()
{
}

void CDagger::Changed(bool trigger)
{
	m_bChanged = trigger;
	m_bTouchAble = false;
}

void CDagger::UpdateAnimation()
{
	wstring str = L"Dagger";

	if (m_bChanged || m_fTimer >= 3)
	{
		str += L"Twinkle";
	}
	else
	{
		str += L"Idle";
	}

	m_pAnimator->Play(str, false);
}

void CDagger::SetPlayer(CPlayer* player)
{
	pPlayer = player;
}

void CDagger::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"Tile")
	{
		m_bDelete = true;
		m_fSpeed = 0;
		m_fTimer = 0;
	}
	else if ((pOtherCollider->GetObjName() == L"Player"))
	{
		if (pPlayer->GetItem() != PlayerITEM::Dagger)
		{
			pPlayer->DropItem();
			pPlayer->SetItem(PlayerITEM::Dagger);
		}
		DELETEOBJECT(this);
	}
}

