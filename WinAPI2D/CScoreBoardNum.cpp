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

	m_Credit = 0;
	m_Rest = 0;

	m_bScoreBoard = true;
	m_bChangeBoard = false;

	m_StartLookAt = Vector(WINSIZEX * 0.5f, WINSIZEY * 0.5f);
	m_curLookAt = Vector(WINSIZEX * 0.5f, WINSIZEY * 0.5f);
}

CScoreBoardNum::~CScoreBoardNum()
{
}

void CScoreBoardNum::Init()
{
	m_pAnimator = new CAnimator();

	m_pNumIdle = RESOURCE->LoadImg(L"NumIdle", L"Image\\ScoreNumIdle.png");
	m_pNumOut  = RESOURCE->LoadImg(L"NumOut",  L"Image\\ScoreNumChange1.png");
	m_pNumIn   = RESOURCE->LoadImg(L"NumIn",   L"Image\\ScoreNumChange2.png");

	m_pAnimator->CreateAnimation(L"Idle:Zero",	 m_pNumIdle, Vector(NUMX * 0, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 1, 1, false);
	m_pAnimator->CreateAnimation(L"Idle:One",	 m_pNumIdle, Vector(NUMX * 1, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 1, 1, false);
	m_pAnimator->CreateAnimation(L"Idle:Two",	 m_pNumIdle, Vector(NUMX * 2, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 1, 1, false);
	m_pAnimator->CreateAnimation(L"Idle:Three",	 m_pNumIdle, Vector(NUMX * 3, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 1, 1, false);
	m_pAnimator->CreateAnimation(L"Idle:Four",	 m_pNumIdle, Vector(NUMX * 4, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 1, 1, false);
	m_pAnimator->CreateAnimation(L"Idle:Five",	 m_pNumIdle, Vector(NUMX * 5, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 1, 1, false);
	m_pAnimator->CreateAnimation(L"Idle:Six",	 m_pNumIdle, Vector(NUMX * 6, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 1, 1, false);
	m_pAnimator->CreateAnimation(L"Idle:Seven",	 m_pNumIdle, Vector(NUMX * 7, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 1, 1, false);
	m_pAnimator->CreateAnimation(L"Idle:Eight",	 m_pNumIdle, Vector(NUMX * 8, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 1, 1, false);
	m_pAnimator->CreateAnimation(L"Idle:Nine",	 m_pNumIdle, Vector(NUMX * 9, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 1, 1, false);

	m_pAnimator->CreateAnimation(L"In:Zero",    m_pNumIn, Vector(NUMX * 0, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false);
	m_pAnimator->CreateAnimation(L"In:One",     m_pNumIn, Vector(NUMX * 1, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false);
	m_pAnimator->CreateAnimation(L"In:Two",     m_pNumIn, Vector(NUMX * 2, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false);
	m_pAnimator->CreateAnimation(L"In:Three",   m_pNumIn, Vector(NUMX * 3, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false);
	m_pAnimator->CreateAnimation(L"In:Four",    m_pNumIn, Vector(NUMX * 4, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false);
	m_pAnimator->CreateAnimation(L"In:Five",    m_pNumIn, Vector(NUMX * 5, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false);
	m_pAnimator->CreateAnimation(L"In:Six",     m_pNumIn, Vector(NUMX * 6, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false);
	m_pAnimator->CreateAnimation(L"In:Seven",   m_pNumIn, Vector(NUMX * 7, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false);
	m_pAnimator->CreateAnimation(L"In:Eight",   m_pNumIn, Vector(NUMX * 8, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false);
	m_pAnimator->CreateAnimation(L"In:Nine",    m_pNumIn, Vector(NUMX * 9, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false);
																													   
	m_pAnimator->CreateAnimation(L"Out:Zero",  m_pNumOut, Vector(NUMX * 0, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false);
	m_pAnimator->CreateAnimation(L"Out:One",   m_pNumOut, Vector(NUMX * 1, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false);
	m_pAnimator->CreateAnimation(L"Out:Two",   m_pNumOut, Vector(NUMX * 2, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false);
	m_pAnimator->CreateAnimation(L"Out:Three", m_pNumOut, Vector(NUMX * 3, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false);
	m_pAnimator->CreateAnimation(L"Out:Four",  m_pNumOut, Vector(NUMX * 4, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false);
	m_pAnimator->CreateAnimation(L"Out:Five",  m_pNumOut, Vector(NUMX * 5, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false);
	m_pAnimator->CreateAnimation(L"Out:Six",   m_pNumOut, Vector(NUMX * 6, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false);
	m_pAnimator->CreateAnimation(L"Out:Seven", m_pNumOut, Vector(NUMX * 7, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false);
	m_pAnimator->CreateAnimation(L"Out:Eight", m_pNumOut, Vector(NUMX * 8, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false);
	m_pAnimator->CreateAnimation(L"Out:Nine",  m_pNumOut, Vector(NUMX * 9, 0), Vector(NUMX, NUMY), Vector(0, NUMY), 0.04f, 4, false);

	m_pAnimator->Play(L"Idle:Zero", false);
	AddComponent(m_pAnimator);

}

void CScoreBoardNum::Update()
{
	m_curLookAt = CAMERA->GetLookAt();
	m_vecPos = m_curLookAt - m_StartLookAt + Vector(187 - SCALE*m_NumScale, 42);

	if (BUTTONDOWN('R'))
	{
		m_bChangeBoard = true;
	}

	if (m_bChangeBoard)
	{
		m_fTimer += DT;
		if (m_fTimer > 0.45f)
		{
			m_bChangeBoard = false;
			if (m_bScoreBoard)
			{
				m_bScoreBoard = false;
			}
			else
			{
				m_bScoreBoard = true;
			}
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
	int Score;
	int repeat = m_NumScale;
	m_TenScale = m_NumScale;
	wstring str = L"";

	if (m_bScoreBoard)
	{
		Score = pPlayer->GetCredit();
	}
	else
	{
		Score = pPlayer->GetRest();
		
	}

	if (!m_NumScale)
	{
		m_OutputNum = Score % 10;
	}
	else
	{
		while (repeat)
		{
			m_TenScale *= 10;
			repeat--;
		}
		m_OutputNum = Score / m_TenScale;
	}

	if (!m_bChangeBoard)
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
		else
		{

		}
	}

	if (m_NumScale == 2)
	{
		return;
		// None Animation을 만들어서 재생시키게 해야할듯......
		// 변환부분도 None을 출력시키게 전환해야
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

	if (m_fTimer > 0.16f && m_fTimer < 0.28)
	{

	}
	else
	{
		m_pAnimator->Play(str, false);
	}
}

