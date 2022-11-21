#include "framework.h"
#include "CCredit.h"

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
#include "CScoreText.h"

CCredit::CCredit()
{
	m_layer = Layer::Item;
	m_pAnimator = nullptr;
	m_pCredit = nullptr;
	pPlayer = nullptr;
}

CCredit::~CCredit()
{
}

void CCredit::Init()
{
	m_pAnimator = new CAnimator();
	m_pCredit = RESOURCE->LoadImg(L"Credit", L"Image\\Item\\Credit.png");

	m_pAnimator->CreateAnimation(L"CreditR", m_pCredit, Vector(0, 0), Vector(15, 14), Vector(15, 0), 1, 1, false);
	m_pAnimator->CreateAnimation(L"CreditB", m_pCredit, Vector(15, 0), Vector(15, 14), Vector(15, 0), 1, 1, false);
	m_pAnimator->CreateAnimation(L"CreditW", m_pCredit, Vector(30, 0), Vector(15, 14), Vector(15, 0), 1, 1, false);
	
	//m_pAnimator->Play(L"CreditR");
	AddComponent(m_pAnimator);
	AddCollider(ColliderType::Rect, Vector(15, 15), Vector(0, 0));
}

void CCredit::Update()
{
	m_vecPos.y += m_fVelocity * DT;
	UpdateAnimation();
}

void CCredit::Render()
{
}

void CCredit::Release()
{
}

void CCredit::SetCredit(int credit)
{
	m_Credit = credit;
}

void CCredit::UpdateAnimation()
{
	if (m_Credit == 100)
	{
		m_pAnimator->Play(L"CreditR",false);
	}
	else if (m_Credit == 400)
	{
		m_pAnimator->Play(L"CreditB", false);
	}
	else if (m_Credit == 700)
	{
		m_pAnimator->Play(L"CreditW", false);
	}
}

void CCredit::SetPlayer(CPlayer* player)
{
	pPlayer = player;
}

void CCredit::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"Tile")
	{
		m_fVelocity = 0;
	}
	else if (pOtherCollider->GetObjName() == L"Player")
	{
		pPlayer->SetCredit(pPlayer->GetCredit() + m_Credit);
		pPlayer->SetScore(pPlayer->GetScore() + m_Credit);
		CScoreText* text = new CScoreText();
		text->SetCredit(m_Credit);
		text->SetPos(m_vecPos);
		ADDOBJECT(text);

		DELETEOBJECT(this);
	}
}