#include "framework.h"
#include "CAxe.h"

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

CAxe::CAxe()
{
	m_layer = Layer::Item;
	
	m_strName = L"Axe";

	m_pAnimator = nullptr;
	m_pAxe = nullptr;

	m_bChanged = false;
	m_bDelete = false;
	m_bCollisionTrigger = false;

	m_bReverse = false;

	m_fTimer = 0;
	m_fSpeed = 300;
}

CAxe::~CAxe()
{
}

void CAxe::Init()
{
	m_pAnimator = new CAnimator();

	m_pAxe = RESOURCE->LoadImg(L"AxeAni", L"Image\\Item\\Axe.png");

	m_pAnimator->CreateAnimation(L"AxeIdle", m_pAxe, Vector(0, 0), Vector(16, 21), Vector(16, 0), 1, 1, false);
	m_pAnimator->CreateAnimation(L"AxeTwinkle", m_pAxe, Vector(0, 0), Vector(16, 21), Vector(16, 0), 0.02f, 2, true);

	m_pAnimator->Play(L"AxeIdle");

	AddComponent(m_pAnimator);
	AddCollider(ColliderType::Rect, Vector(16, 16), Vector(0, 0));

}

void CAxe::Update()
{
	m_vecPos.y += m_fSpeed * DT;

	if (m_bChanged)
	{
		m_bCollisionTrigger = true;
		if (m_bReverse)
		{
			m_vecPos.x += m_fThrow * DT;
		}
		else
		{
			m_vecPos.x -= m_fThrow * DT;
		}
		
		if (m_fTimer > 0.1f && !m_fThrow == 0)
		{
				 m_fThrow -= 2;

		}
	}

	if (m_bCollisionTrigger)
	{
		m_fTriggerTimer += DT;
		if (m_fTriggerTimer > 1)
		{
			m_bCollisionTrigger = false;
			m_fTriggerTimer = 0;
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

void CAxe::Render()
{
}

void CAxe::Release()
{
}

void CAxe::SetReverse(bool reverse)
{
	m_bReverse = reverse;
}

void CAxe::Changed(bool trigger)
{
	m_bChanged = trigger;
	m_bCollisionTrigger = true;
}

void CAxe::UpdateAnimation()
{
	wstring str = L"Axe";

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

void CAxe::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"Tile")
	{
		m_bDelete = true;
		m_fSpeed = 0;
		m_fTimer = 0;
	}
	else if ((pOtherCollider->GetObjName() == L"Player") && !m_bCollisionTrigger)
	{
		DELETEOBJECT(this);
	}
}
