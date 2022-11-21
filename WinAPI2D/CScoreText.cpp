#include "framework.h"
#include "CScoreText.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CResourceManager.h"
#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"

CScoreText::CScoreText()
{
	m_layer = Layer::Item;

	m_pAnimator = nullptr;
	m_pScore = nullptr;
	m_pCredit = nullptr;

	m_Credit = 0;
}

CScoreText::~CScoreText()
{
}

void CScoreText::Init()
{
	m_pAnimator = new CAnimator();
	m_pScore = RESOURCE->LoadImg(L"CreditText", L"Image\\Item\\CreditText.png");
	m_pAnimator->CreateAnimation(L"Credit100", m_pScore, Vector(0, 0), Vector(23, 15), Vector(23, 0), 1, 1, false);
	m_pAnimator->CreateAnimation(L"Credit400", m_pScore, Vector(23, 0), Vector(23, 15), Vector(23, 0), 1, 1, false);
	m_pAnimator->CreateAnimation(L"Credit700", m_pScore, Vector(46, 0), Vector(23, 15), Vector(23, 0), 1, 1, false);
	m_pAnimator->CreateAnimation(L"Credit1000", m_pScore, Vector(69, 0), Vector(23, 15), Vector(23, 0), 1, 1, false);

	AddComponent(m_pAnimator);
}

void CScoreText::Update()
{
	m_fTimer += DT;
	m_vecPos.y -= m_fSpeed* DT;
	if (m_fTimer >= 0.5f && m_fTimer < 0.7f)
	{
		m_fSpeed = 0;
	}
	else if (m_fTimer > 0.7f)
	{
		DELETEOBJECT(this);
	}

	UpdateAnimation();
}

void CScoreText::Render()
{
}

void CScoreText::Release()
{
}

void CScoreText::UpdateAnimation()
{
	wstring str = L"Credit";

	if (m_Credit == 100)
	{
		str += L"100";
	}
	else if (m_Credit == 400)
	{
		str += L"400";
	}
	else if (m_Credit == 700)
	{
		str += L"700";
	}
	else if (m_Credit == 1000)
	{
		str += L"1000";
	}
	m_pAnimator->Play(str);
}

void CScoreText::SetCredit(int credit)
{
	m_Credit = credit;
}
