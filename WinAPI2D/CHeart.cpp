#include "framework.h"
#include "CHeart.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CResourceManager.h"
#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"

CHeart::CHeart()
{
	m_pHeart = nullptr;
	m_pAnimator = nullptr;
	m_strName = L"Heart";
	m_layer = Layer::Item;

	m_bOnGround = false;
	m_bReverse = false;
}

CHeart::~CHeart()
{
}

void CHeart::Init()
{
	m_pAnimator = new CAnimator();
	m_pHeart = RESOURCE->LoadImg(L"Heart", L"Image\\Item\\Heart.png");

	m_pAnimator->CreateAnimation(L"Heart", m_pHeart, Vector(0, 0), Vector(8, 7), Vector(8, 0), 0.02f, 10, true);

	m_pAnimator->Play(L"Heart");
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(10, 10), Vector(0,0));
}

void CHeart::Update()
{
	m_fTimer += DT;

	if (!m_bOnGround)
	{
		m_vecPos.y += m_fVelocity * DT;
		m_vecPos.x += m_fSpeed * DT;

		if (m_fSpeed == 100)
		{
			m_bReverse = true;
		}
		else if (m_fSpeed == -100)
		{
			m_bReverse = false;
		}

		if (m_bReverse)
		{
			if (m_fTimer >= 0.01f)
			{
				m_fSpeed -=2;
				m_fTimer = 0;
			}
		}
		else
		{
			if (m_fTimer >= 0.01f)
			{
				m_fSpeed+=2;
				m_fTimer = 0;
			}
		}
	}

	if (m_vecPos.y < 0 ||
		m_vecPos.y > WINSIZEY)
		DELETEOBJECT(this);
}

void CHeart::Render()
{
}

void CHeart::Release()
{
}

void CHeart::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetOwner()->GetName() == L"Player")
	{
		DELETEOBJECT(this);
	}
	else if (pOtherCollider->GetOwner()->GetName() == L"Tile")
	{
		m_bOnGround = true;
		m_fVelocity = 0;
		m_fSpeed = 0;
		m_fTimer = 0;
	}
}
