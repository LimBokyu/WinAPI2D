#include "framework.h"
#include "CAttackCollider.h"

#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CEventManager.h"
#include "CCollider.h"
#include "CWhip.h"
#include "CPlayer.h"

CAttackCollider::CAttackCollider()
{
	m_pWhip = nullptr;
	m_pSoundEffect = nullptr;
	m_layer = Layer::PlayerAttack;
	m_strName = L"PlayerAttack";
}

CAttackCollider::~CAttackCollider()
{
}

void CAttackCollider::Init()
{
	m_pSoundEffect = RESOURCE->LoadSound(L"AttackSound", L"Sound\\SE\\Attack.wav");
	SOUND->Play(m_pSoundEffect, 0.05f);
	AddCollider(ColliderType::Rect, Vector(100, 20), Vector(10, 0));
}

void CAttackCollider::Update()
{
	if (m_pWhip == nullptr)
	{
		DELETEOBJECT(this);
	}
}

void CAttackCollider::Render()
{
}

void CAttackCollider::Release()
{
}

void CAttackCollider::SetWhip(CWhip* whip)
{
	m_pWhip = whip;
}
