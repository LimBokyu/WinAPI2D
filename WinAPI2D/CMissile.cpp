#include "framework.h"
#include "CMissile.h"

#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CEventManager.h"
#include "CCollider.h"

CMissile::CMissile()
{
	m_vecScale = Vector(50, 10);
	m_vecDir = Vector(0, 0);

	m_fVelocity = 0;
	m_AttackTime = 0;

	m_layer = Layer::PlayerAttack;

	m_strName = L"�̻���";
}

CMissile::~CMissile()
{
}

void CMissile::Init()
{
	AddCollider(ColliderType::Rect, Vector(120, 10), Vector(40, 0));
}

void CMissile::Update()
{
	m_vecPos += m_vecDir * m_fVelocity * DT;

	m_AttackTime += DT;

	if (m_AttackTime >= 0.5)
	{
		DELETEOBJECT(this);
	}

	// ȭ������� ������� ����
}

void CMissile::Render()
{
	/*RENDER->FrameCircle(
		m_vecPos.x,
		m_vecPos.y,
		m_vecScale.x);*/
}

void CMissile::Release()
{
}

void CMissile::OnCollisionEnter(CCollider* pOtherCollider)
{
	Logger::Debug(L"�̻����� �浹ü�� �ε��� ������ϴ�.");
	DELETEOBJECT(this);
}

void CMissile::SetDir(Vector dir)
{
	//m_vecDir = dir.Normalized();
}

void CMissile::SetVelocity(float velocity)
{
	//m_fVelocity = velocity;
}
