#include "framework.h"
#include "CLongAttackCollider.h"

#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CEventManager.h"
#include "CCollider.h"
#include "CWhip.h"
#include "CPlayer.h"

CLongAttackCollider::CLongAttackCollider()
{
	m_pWhip = nullptr;
	m_layer = Layer::PlayerAttack;
	m_strName = L"PlayerAttack";
}

CLongAttackCollider::~CLongAttackCollider()
{
}

void CLongAttackCollider::Init()
{
	AddCollider(ColliderType::Rect, Vector(140, 20), Vector(0, 0));
}

void CLongAttackCollider::Update()
{
	if (m_pWhip == nullptr)
	{
		DELETEOBJECT(this);
	}
}

void CLongAttackCollider::Render()
{
}

void CLongAttackCollider::Release()
{
}

void CLongAttackCollider::SetWhip(CWhip* whip)
{
	m_pWhip = whip;
}