#include "framework.h"
#include "CSkeltonApe.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CResourceManager.h"
#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"
#include "CSkeltonApeDeath.h"
#include "CPlayer.h"


CSkeltonApe::CSkeltonApe()
{
	m_layer = Layer::Monster;

	m_pAnimator = nullptr;
	m_pMonsterMove = nullptr;
	m_pMonsterIdle = nullptr;
	m_pMonsterFall = nullptr;
	m_pMonsterAttack = nullptr;
	m_pMonsterAttaking = nullptr;

	m_bMove = false;

	pPlayer = nullptr;

	m_fSpeed = 30;
}

CSkeltonApe::~CSkeltonApe()
{
}

void CSkeltonApe::Init()
{
	m_pAnimator = new CAnimator;

	m_pMonsterIdle = RESOURCE->LoadImg(L"SkeltonIdle", L"Image\\Monster\\SkeltonApe\\SkeltonApeIdle.png");
	m_pMonsterMove = RESOURCE->LoadImg(L"SkeltonMove", L"Image\\Monster\\SkeltonApe\\SkeltonApeMove.png");

	m_pAnimator->CreateAnimation(L"SkeltonApeIdle", m_pMonsterIdle, Vector(0, 0), Vector(80, 60), Vector(80, 0), 1, 1, false);
	m_pAnimator->CreateAnimation(L"SkeltonApeMove", m_pMonsterMove, Vector(0, 0), Vector(80, 60), Vector(80, 0), 0.1f,9, false);

	m_pAnimator->Play(L"SkeltonApeIdle");
	AddComponent(m_pAnimator);
	AddCollider(ColliderType::Rect, Vector(80, 110), Vector(0, 0));
}

void CSkeltonApe::Update()
{
	
	if (!m_bMove)
	{
		m_fTimer += DT;
		if (m_fTimer >= 0.2f)
		{
			m_fTimer = 0;
			m_bMove = true;
		}
	}
	else
	{
		m_vecPos.x -= m_fSpeed * DT;
		m_fTimer += DT;
		if (m_fTimer >= 0.9f)
		{
			m_fTimer = 0;
			m_bMove = false;
		}
	}
	UpdateAnimation();
}

void CSkeltonApe::Render()
{
}

void CSkeltonApe::Release()
{
}

void CSkeltonApe::SetPlayer(CPlayer* player)
{
	pPlayer = player;
}

void CSkeltonApe::UpdateAnimation()
{
	wstring str = L"SkeltonApe";

	if (m_bMove)
	{
		str += L"Move";
	}
	else
	{
		str += L"Idle";
	}

	m_pAnimator->Play(str, false);
}

void CSkeltonApe::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"PlayerAttack")
	{
		pPlayer->SetScore(pPlayer->GetScore() + 100);

		CSkeltonApeDeath* death = new CSkeltonApeDeath();
		death->SetPos(m_vecPos.x, m_vecPos.y-30);
		ADDOBJECT(death);

		DELETEOBJECT(this);
	}
}
