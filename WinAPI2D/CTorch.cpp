#include "framework.h"
#include "CTorch.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CResourceManager.h"
#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"
#include "CHeart.h"
#include "CBigHeart.h"
#include "CCredit.h"
#include "CPlayer.h"
#include "CDagger.h"
#include "CAxe.h"

CTorch::CTorch()
{
	m_pAnimator = nullptr;
	m_pTorch = nullptr;
	pPlayer = nullptr;

	m_credit = 0;
	m_layer = Layer::Object;
	m_Item = ItemCase::Null;
}

CTorch::~CTorch()
{
}

void CTorch::Init()
{
	m_pAnimator = new CAnimator;
	m_pTorch = RESOURCE->LoadImg(L"Torch", L"Image\\Object\\Torch.png");

	m_pAnimator->CreateAnimation(L"Torch", m_pTorch, Vector(0, 0), Vector(24, 48), Vector(24, 0), 0.04f, 4, true);
	m_pAnimator->Play(L"Torch",false);

	AddComponent(m_pAnimator);
	AddCollider(ColliderType::Rect, Vector(50, 100), Vector(0, 0));
}

void CTorch::Update()
{
}

void CTorch::Render()
{
}

void CTorch::Release()
{
}

void CTorch::SetItem(ItemCase item)
{
	m_Item = item;
}

void CTorch::SetCredit(int credit)
{
	m_credit = credit;
}

void CTorch::CreateHeart()
{
	CHeart* heart = new CHeart();
	heart->SetPos(m_vecPos);
	ADDOBJECT(heart);
}

void CTorch::CreateBigHeart()
{
	CBigHeart* Big = new CBigHeart();
	Big->SetPos(m_vecPos);
	ADDOBJECT(Big);
}

void CTorch::CreateCredit()
{
	CCredit* Credit = new CCredit();
	Credit->SetPos(m_vecPos);
	Credit->SetCredit(m_credit);
	Credit->SetPlayer(pPlayer);
	ADDOBJECT(Credit);
}

void CTorch::CreateAxe()
{
	CAxe* axe = new CAxe();
	axe->SetPos(m_vecPos);
	ADDOBJECT(axe);
}

void CTorch::CreateDagger()
{
	CDagger* dagger = new CDagger();
	dagger->SetPos(m_vecPos);
	ADDOBJECT(dagger);
}

void CTorch::SetPlayer(CPlayer* player)
{
	pPlayer = player;
}

void CTorch::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"PlayerAttack")
	{
		switch (m_Item)
		{
		case ItemCase::Heart:
			CreateHeart();
			break;
		case ItemCase::BigHeart:
			CreateBigHeart();
			break;
		case ItemCase::Credit:
			CreateCredit();
			break;
		case ItemCase::Dagger:
			CreateDagger();
			break;
		case ItemCase::Axe:
			CreateAxe();
		}
		
		DELETEOBJECT(this);
	}
}
