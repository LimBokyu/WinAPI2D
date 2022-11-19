#include "framework.h"

#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CEventManager.h"
#include "CCollider.h"
#include "CWhip.h"
#include "CPlayer.h"
#include "CAttackCollider.h"
#include "CLongAttackCollider.h"


CWhip::CWhip()
{
	m_vecScale = Vector(50, 10);
	m_vecDir = Vector(0, 0);
	m_vecLong = Vector(0, 0);
	m_vecDotFix = Vector(0, 0);

	m_fVelocity = 0;
	m_AttackTime = 0;

	m_layer = Layer::PlayerAttack;

	m_bReverse = false;
	m_bLongAttack = false;
	m_bDuck = false;
	m_bHit = true;
	m_bTriggerOnce = false;

	m_pNormalAttack = nullptr;
	m_pLongAttack = nullptr;
	m_pNormalAttackR = nullptr;
	m_pLongAttackR = nullptr;

	m_pDuckNormalAttack = nullptr;
	m_pDuckLongAttack = nullptr;

	m_pDuckNormalAttackR = nullptr;
	m_pDuckLongAttackR = nullptr;

	m_strName = L"�÷��̾� ����";
}

CWhip::~CWhip()
{
}

void CWhip::Init()
{
	m_pAnimator = new CAnimator();

	m_pNormalAttack = RESOURCE->LoadImg(L"Normal", L"Image\\Player\\NormalWhip.png");
	m_pLongAttack = RESOURCE->LoadImg(L"Long", L"Image\\Player\\LongWhip.png");
	m_pNormalAttackR = RESOURCE->LoadImg(L"NormalR", L"Image\\Player\\NormalWhipR.png");
	m_pLongAttackR = RESOURCE->LoadImg(L"LongR", L"Image\\Player\\LongWhipR.png");

	m_pDuckNormalAttack = RESOURCE->LoadImg(L"DuckNormal", L"Image\\Player\\DuckNormalWhip.png");
	m_pDuckLongAttack = RESOURCE->LoadImg(L"DuckLong", L"Image\\Player\\DuckLongWhip.png");

	m_pDuckNormalAttackR = RESOURCE->LoadImg(L"DuckNormalR", L"Image\\Player\\DuckNormalWhipR.png");
	m_pDuckLongAttackR = RESOURCE->LoadImg(L"DuckLongR", L"Image\\Player\\DuckLongWhipR.png");

	m_pAnimator->CreateAnimation(L"Normal", m_pNormalAttack, Vector(0, 0), Vector(55, 9), Vector(0, 9), 0.001f, 3, true);
	m_pAnimator->CreateAnimation(L"Long",   m_pLongAttack,   Vector(0, 0), Vector(64, 9), Vector(0, 9), 0.001f, 2, true);
	m_pAnimator->CreateAnimation(L"NormalR", m_pNormalAttackR, Vector(0, 0), Vector(55, 9), Vector(0, 9), 0.001f, 3, true);
	m_pAnimator->CreateAnimation(L"LongR", m_pLongAttackR, Vector(0, 0), Vector(64, 9), Vector(0, 9), 0.001f, 2, true);

	m_pAnimator->CreateAnimation(L"DuckNormal",  m_pDuckNormalAttack, Vector(0, 0), Vector(55, 9), Vector(0, 9), 0.001f, 3, true);
	m_pAnimator->CreateAnimation(L"DuckLong",    m_pDuckLongAttack, Vector(0, 0), Vector(64, 9), Vector(0, 9), 0.001f, 2, true);
	m_pAnimator->CreateAnimation(L"DuckNormalR", m_pDuckNormalAttackR, Vector(0, 0), Vector(55, 9), Vector(0, 9), 0.001f, 3, true);
	m_pAnimator->CreateAnimation(L"DuckLongR",   m_pDuckLongAttackR, Vector(0, 0), Vector(64, 9), Vector(0, 9), 0.001f, 2, true);

	AddComponent(m_pAnimator);
}

void CWhip::Update()
{
	m_bReverse = pPlayer->GetReverse();
	m_bDuck = pPlayer->GetDuck();

#pragma region ���� ����Ʈ�� �̹��� ���� ��ǥ ����

	if (m_bLongAttack)
	{
		if (m_bDuck && !m_bReverse)	// �ɾƼ� ����
		{
			m_vecPos = pPlayer->GetPos() + Vector(87, 11);
		}
		else if (m_bDuck && m_bReverse)	// �ɾƼ� �ĸ�
		{
			m_vecPos = pPlayer->GetPos() + Vector(-87, 10);
		}	
		else if (!m_bReverse)			// ���� ����
		{
			m_vecPos = pPlayer->GetPos() + Vector(92, -22);
		}
		else if (m_bReverse)			// ���� �ĸ�
		{	
			m_vecPos = pPlayer->GetPos() + Vector(-98, -22);
		}

		CLongAttackCollider* longatt = new CLongAttackCollider();
		longatt->SetPos(m_vecPos);
		ADDOBJECT(longatt);
	}
	else
	{
		if (m_bDuck && !m_bReverse)
		{
			m_vecPos = pPlayer->GetPos() + Vector(81, 11);
		}
		else if (m_bDuck && m_bReverse)
		{
			m_vecPos = pPlayer->GetPos() + Vector(-97, 10);
		}
		else if (!m_bReverse)
		{
			m_vecPos = pPlayer->GetPos() + Vector(83, -22);
		}
		else if (m_bReverse)
		{
			m_vecPos = pPlayer->GetPos() + Vector(-107, -22);
		}
		CAttackCollider* att = new CAttackCollider();
		att->SetPos(m_vecPos);
		ADDOBJECT(att);
	}

#pragma endregion

	m_AttackTime += DT;

	if (m_AttackTime >= 0.15f)
	{
		m_bLongAttack = false;
		DELETEOBJECT(this);
	}

	if (m_bReverse)
	{
		if (BUTTONDOWN(VK_LEFT))
		{
			m_bLongAttack = true;
			m_bTriggerOnce = true;
		}
	}
	else
	{
		if (BUTTONDOWN(VK_RIGHT))
		{
			m_bLongAttack = true;
			m_bTriggerOnce = true;
		}
	}

	UpdateAnimation();
}

void CWhip::Render()
{
}

void CWhip::Release()
{
}

void CWhip::SetPlayer(CPlayer* player)
{
	pPlayer = player;
}

void CWhip::UpdateAnimation()
{
	wstring str = L"";

	if (m_bDuck)
	{
		str += L"Duck";
	}

	if (m_bLongAttack)
	{
		str += L"Long";
	}
	else
	{
		str += L"Normal";
	}

	if (m_bReverse)
	{
		str += L"R";
	}

	m_pAnimator->Play(str, false);
}