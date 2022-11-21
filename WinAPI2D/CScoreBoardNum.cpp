#include "framework.h"
#include "CLifeBar.h"
#include "CLifeBarScore.h"

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
#include "CScoreBoardNum.h"

#define NUMX  6
#define NUMY  5
#define SCALE 16

CScoreBoardNum::CScoreBoardNum()
{
	m_layer = Layer::Interface;

	m_pAnimator = nullptr;
	pPlayer = nullptr;
	m_pNumIdle = nullptr;
	m_pNumOut = nullptr;
	m_pNumIn = nullptr;
	m_pNumNone = nullptr;

	m_Credit = 0;
	m_Rest = 0;
	m_Score = 0;
	m_TenScale = 1;

	m_bScoreBoard = true;
	m_bChangeBoard = false;
	m_bChangeTrigger = false;

	m_StartLookAt = Vector(WINSIZEX * 0.5f, WINSIZEY * 0.5f);
	m_curLookAt = Vector(WINSIZEX * 0.5f, WINSIZEY * 0.5f);
}

CScoreBoardNum::~CScoreBoardNum()
{
}

void CScoreBoardNum::Init()
{
	m_pAnimator = new CAnimator();

	m_pNumIdle = RESOURCE->LoadImg(L"NumIdle", L"Image\\Interface\\ScoreNumIdle.png");
	m_pNumOut  = RESOURCE->LoadImg(L"NumOut",  L"Image\\Interface\\ScoreNumChange1.png");
	m_pNumIn   = RESOURCE->LoadImg(L"NumIn",   L"Image\\Interface\\ScoreNumChange2.png");
	m_pNumNone = RESOURCE->LoadImg(L"NumNone", L"Image\\Interface\\NumNone.png");

	m_pAnimator->CreateAnimation(L"Idle:Zero",	 m_pNumIdle, Vector(NUMX * 0, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 1, 1, false, false);
	m_pAnimator->CreateAnimation(L"Idle:One",	 m_pNumIdle, Vector(NUMX * 1, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 1, 1, false, false);
	m_pAnimator->CreateAnimation(L"Idle:Two",	 m_pNumIdle, Vector(NUMX * 2, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 1, 1, false, false);
	m_pAnimator->CreateAnimation(L"Idle:Three",	 m_pNumIdle, Vector(NUMX * 3, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 1, 1, false, false);
	m_pAnimator->CreateAnimation(L"Idle:Four",	 m_pNumIdle, Vector(NUMX * 4, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 1, 1, false, false);
	m_pAnimator->CreateAnimation(L"Idle:Five",	 m_pNumIdle, Vector(NUMX * 5, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 1, 1, false, false);
	m_pAnimator->CreateAnimation(L"Idle:Six",	 m_pNumIdle, Vector(NUMX * 6, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 1, 1, false, false);
	m_pAnimator->CreateAnimation(L"Idle:Seven",	 m_pNumIdle, Vector(NUMX * 7, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 1, 1, false, false);
	m_pAnimator->CreateAnimation(L"Idle:Eight",	 m_pNumIdle, Vector(NUMX * 8, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 1, 1, false, false);
	m_pAnimator->CreateAnimation(L"Idle:Nine",	 m_pNumIdle, Vector(NUMX * 9, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 1, 1, false, false);

	m_pAnimator->CreateAnimation(L"In:Zero",    m_pNumIn, Vector(NUMX * 0, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false, false);
	m_pAnimator->CreateAnimation(L"In:One",     m_pNumIn, Vector(NUMX * 1, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false, false);
	m_pAnimator->CreateAnimation(L"In:Two",     m_pNumIn, Vector(NUMX * 2, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false, false);
	m_pAnimator->CreateAnimation(L"In:Three",   m_pNumIn, Vector(NUMX * 3, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false, false);
	m_pAnimator->CreateAnimation(L"In:Four",    m_pNumIn, Vector(NUMX * 4, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false, false);
	m_pAnimator->CreateAnimation(L"In:Five",    m_pNumIn, Vector(NUMX * 5, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false, false);
	m_pAnimator->CreateAnimation(L"In:Six",     m_pNumIn, Vector(NUMX * 6, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false, false);
	m_pAnimator->CreateAnimation(L"In:Seven",   m_pNumIn, Vector(NUMX * 7, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false, false);
	m_pAnimator->CreateAnimation(L"In:Eight",   m_pNumIn, Vector(NUMX * 8, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false, false);
	m_pAnimator->CreateAnimation(L"In:Nine",    m_pNumIn, Vector(NUMX * 9, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false, false);
																													   
	m_pAnimator->CreateAnimation(L"Out:Zero",  m_pNumOut, Vector(NUMX * 0, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false, false);
	m_pAnimator->CreateAnimation(L"Out:One",   m_pNumOut, Vector(NUMX * 1, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false, false);
	m_pAnimator->CreateAnimation(L"Out:Two",   m_pNumOut, Vector(NUMX * 2, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false, false);
	m_pAnimator->CreateAnimation(L"Out:Three", m_pNumOut, Vector(NUMX * 3, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false, false);
	m_pAnimator->CreateAnimation(L"Out:Four",  m_pNumOut, Vector(NUMX * 4, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false, false);
	m_pAnimator->CreateAnimation(L"Out:Five",  m_pNumOut, Vector(NUMX * 5, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false, false);
	m_pAnimator->CreateAnimation(L"Out:Six",   m_pNumOut, Vector(NUMX * 6, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false, false);
	m_pAnimator->CreateAnimation(L"Out:Seven", m_pNumOut, Vector(NUMX * 7, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false, false);
	m_pAnimator->CreateAnimation(L"Out:Eight", m_pNumOut, Vector(NUMX * 8, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false, false);
	m_pAnimator->CreateAnimation(L"Out:Nine",  m_pNumOut, Vector(NUMX * 9, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false, false);

	m_pAnimator->CreateAnimation(L"NumNone", m_pNumNone, Vector(NUMX, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 1, 1, false, false);

	m_pAnimator->Play(L"Idle:Zero", false);
	AddComponent(m_pAnimator);

}

void CScoreBoardNum::Update()
{
	m_curLookAt = CAMERA->GetLookAt();
	m_vecPos = m_curLookAt - m_StartLookAt + Vector(187 - float(SCALE*m_NumScale), 42);

	if (BUTTONDOWN('R'))
	{
		if (!m_bChangeBoard)
		{
			m_bChangeTrigger = true;
		}
		m_bChangeBoard = true;
	}

	if (m_bChangeBoard)
	{
		m_fTimer += UDT;

		if (m_fTimer > 0.16f && m_fTimer < 0.28)
		{
			if (m_bChangeTrigger)
			{
				ChangeBoard();
			}
		}

		if (m_fTimer > 0.45f)
		{
			m_bChangeBoard = false;
			m_fTimer = 0;
		}
	}

	UpdateAnimation();
}

void CScoreBoardNum::Render()
{
}

void CScoreBoardNum::Release()
{
}

void CScoreBoardNum::SetPlayer(CPlayer* player)
{
	pPlayer = player;
}

void CScoreBoardNum::SetScale(int scale)
{
	if (scale > 6 || scale < 0)
	{
		return;
	}

	m_NumScale = scale;
}

void CScoreBoardNum::ChangeBoard()
{
	m_bChangeTrigger = false;
	if (m_bScoreBoard)
	{
		m_bScoreBoard = false;
	}
	else
	{
		m_bScoreBoard = true;
	}
}

void CScoreBoardNum::UpdateAnimation()
{
	int repeat = m_NumScale;
	int credit = m_NumScale - 3;
	m_TenScale = 1;
	wstring str = L"";

	if (m_bScoreBoard)
	{
		m_Score = pPlayer->GetScore();
		while (repeat)
		{
			m_TenScale *= 10;
			repeat--;
		}
		m_OutputNum = m_Score / m_TenScale;
		m_OutputNum %= 10;
	}
	else
	{
		m_Rest = pPlayer->GetRest();
		m_Credit = pPlayer->GetCredit() / 100;

		while (repeat)
		{
			m_TenScale *= 10;
			repeat--;
		}
		m_OutputNum = m_Rest / m_TenScale;
		m_OutputNum %= 10;


		if (m_NumScale >= 3)
		{
			m_TenScale = 1;
			while (credit)
			{
				m_TenScale *= 10;
				credit--;
			}
			m_OutputNum = m_Credit / m_TenScale;
			m_OutputNum  %= 10;
		}
	}

	if(!m_bChangeBoard)
	{
		str += L"Idle:";
	}
	else
	{
		if (m_fTimer < 0.16f)
		{
			str += L"Out:";
		}
		else if(m_fTimer > 0.28f)
		{
			str += L"In:";
		}
	}

	switch (m_OutputNum)
	{
	case 0:
		str += L"Zero";
		break;
	case 1:
		str += L"One";
		break;
	case 2:
		str += L"Two";
		break;
	case 3:
		str += L"Three";
		break;
	case 4:
		str += L"Four";
		break;
	case 5:
		str += L"Five";
		break;
	case 6:
		str += L"Six";
		break;
	case 7:
		str += L"Seven";
		break;
	case 8:
		str += L"Eight";
		break;
	case 9:
		str += L"Nine";
		break;
	}

	if (m_NumScale == 2 && !m_bScoreBoard)
	{
		m_pAnimator->Play(L"NumNone", false);
	}
	else if (m_fTimer > 0.16f && m_fTimer < 0.28)
	{
		m_pAnimator->Play(L"NumNone", false);
	}
	else
	{
		m_pAnimator->Play(str, false);
	}
}

