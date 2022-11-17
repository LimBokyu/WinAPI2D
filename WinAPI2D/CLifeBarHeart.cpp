#include "framework.h"
#include "CLifeBarHeart.h"

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
#include "CGameObject.h"

#define NUMX  6
#define NUMY  5

CLifeBarHeart::CLifeBarHeart()
{
	m_layer = Layer::Interface;
	m_pHeart = nullptr;
	m_pAnimator = nullptr;
	pPlayer = nullptr;
	Heart = NULL;
	type = Type::One;

	m_StartLookAt = Vector(WINSIZEX * 0.5f, WINSIZEY * 0.5f);
	m_curLookAt = Vector(WINSIZEX * 0.5f, WINSIZEY * 0.5f);
}

CLifeBarHeart::~CLifeBarHeart()
{

}

void CLifeBarHeart::Init()
{
	m_pAnimator = new CAnimator;

	m_pHeart = RESOURCE->LoadImg(L"LifeBarHeart", L"Image\\Interface\\LifeBarHeart.png");

	m_pAnimator->CreateAnimation(L"Heart:Zero",  m_pHeart,	 Vector(NUMX * 0, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.05f, 4);
	m_pAnimator->CreateAnimation(L"Heart:One",   m_pHeart,	 Vector(NUMX * 1, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.05f, 4);
	m_pAnimator->CreateAnimation(L"Heart:Two",   m_pHeart,	 Vector(NUMX * 2, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.05f, 4);
	m_pAnimator->CreateAnimation(L"Heart:Three", m_pHeart,	 Vector(NUMX * 3, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.05f, 4);
	m_pAnimator->CreateAnimation(L"Heart:Four",  m_pHeart,	 Vector(NUMX * 4, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.05f, 4);
	m_pAnimator->CreateAnimation(L"Heart:Five",  m_pHeart,	 Vector(NUMX * 5, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.05f, 4);
	m_pAnimator->CreateAnimation(L"Heart:Six",   m_pHeart,	 Vector(NUMX * 6, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.05f, 4);
	m_pAnimator->CreateAnimation(L"Heart:Seven", m_pHeart,	 Vector(NUMX * 7, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.05f, 4);
	m_pAnimator->CreateAnimation(L"Heart:Eight", m_pHeart,	 Vector(NUMX * 8, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.05f, 4);
	m_pAnimator->CreateAnimation(L"Heart:Nine",  m_pHeart,	 Vector(NUMX * 9, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.05f, 4);
	m_pAnimator->Play(L"Heart:Zero", false);
	AddComponent(m_pAnimator);
}

void CLifeBarHeart::Update()
{
	m_curLookAt = CAMERA->GetLookAt();
	
	if (type == Type::One)
	{
		m_vecPos = m_curLookAt - m_StartLookAt + Vector(60, 37);
		// 1의 자리수의 좌표
	}
	else
	{
		m_vecPos = m_curLookAt - m_StartLookAt + Vector(44, 37);
		// 10의 자리 수의 좌표
	}

	UpdateAnimation();
}

void CLifeBarHeart::Render()
{

}

void CLifeBarHeart::Release()
{

}

void CLifeBarHeart::SetPlayer(CPlayer* player)
{
	pPlayer = player;
}

void CLifeBarHeart::UpdateAnimation()
{
	if (type == Type::One)
	{
		Heart = pPlayer->GetHeart() % 10;
	}
	else
	{
		Heart = pPlayer->GetHeart() / 10;
	}
	
	switch (Heart)
	{
	case 0:
		m_pAnimator->Play(L"Heart:Zero",false);
		break;
	case 1:
		m_pAnimator->Play(L"Heart:One", false);
		break;
	case 2:
		m_pAnimator->Play(L"Heart:Two", false);
		break;
	case 3:
		m_pAnimator->Play(L"Heart:Three", false);
		break;
	case 4:
		m_pAnimator->Play(L"Heart:Four", false);
		break;
	case 5:
		m_pAnimator->Play(L"Heart:Five", false);
		break;
	case 6:
		m_pAnimator->Play(L"Heart:Six", false);
		break;
	case 7:
		m_pAnimator->Play(L"Heart:Seven", false);
		break;
	case 8:
		m_pAnimator->Play(L"Heart:Eight", false);
		break;
	case 9:
		m_pAnimator->Play(L"Heart:Nine", false);
		break;
	}

}

void CLifeBarHeart::OneOrTen(bool one)
{
	if (one)
	{
		type = Type::One;
	}
	else
	{
		type = Type::Ten;
	}
}
