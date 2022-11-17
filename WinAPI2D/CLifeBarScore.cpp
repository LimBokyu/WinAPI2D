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

CLifeBarScore::CLifeBarScore()
{
	m_layer = Layer::Interface;

	m_pScoreBoard = nullptr;
	m_pRestBoard = nullptr;
	m_pScoreNum = nullptr;
	m_pAnimator = nullptr;
	m_pRestToScore = nullptr;
	m_pScoreToRest = nullptr;

	pPlayer = nullptr;

	m_fTimer = 0;
	m_bScoreBoard = true;
	m_bChangeOrder = false;

	m_StartLookAt = Vector(WINSIZEX * 0.5f, WINSIZEY * 0.5f);
	m_curLookAt = Vector(WINSIZEX * 0.5f, WINSIZEY * 0.5f);
}

CLifeBarScore::~CLifeBarScore()
{
}

void CLifeBarScore::Init()
{
	m_pAnimator = new CAnimator();
	m_pScoreBoard  = RESOURCE->LoadImg(L"ScoreBoard",	L"Image\\Interface\\ScoreBoardIdle.png");
	m_pRestBoard =   RESOURCE->LoadImg(L"RestBoard",    L"Image\\Interface\\RestBoardIdle.png");
	m_pScoreNum    = RESOURCE->LoadImg(L"ScoreNum",		L"Image\\Interface\\PlayerScoreNum.png");
	m_pScoreToRest = RESOURCE->LoadImg(L"ScoreToRest",	L"Image\\Interface\\ChangeBoardSR.png");
	m_pRestToScore = RESOURCE->LoadImg(L"RestToScore",	L"Image\\Interface\\ChangeBoardRS.png");

	m_pAnimator->CreateAnimation(L"ScoreBoardIdle", m_pScoreBoard, Vector(0, 0), Vector(64, 16), Vector(0, 16), 1, 1, false);
	m_pAnimator->CreateAnimation(L"RestBoard",		 m_pRestBoard, Vector(0, 0), Vector(64, 16), Vector(0, 16), 1, 1, false);

	m_pAnimator->CreateAnimation(L"ScoreToRest", m_pScoreToRest, Vector(0, 0), Vector(64, 16), Vector(0, 16), 0.044f, 11, false);
	m_pAnimator->CreateAnimation(L"RestToScore", m_pRestToScore, Vector(0, 0), Vector(64, 16), Vector(0, 16), 0.044f, 11, false);

	m_pAnimator->Play(L"ScoreBoardIdle");
	AddComponent(m_pAnimator);
}

void CLifeBarScore::Update()
{
	m_curLookAt = CAMERA->GetLookAt();
	m_vecPos = m_curLookAt - m_StartLookAt + Vector(137, 37);

	if (BUTTONDOWN('R'))
	{
		m_bChangeOrder = true;
	}

	if (m_bChangeOrder)
	{
		m_fTimer += DT;

		if (m_fTimer > 0.44f)
		{
			m_bChangeOrder = false;
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

	AnimationUpdate();
}

void CLifeBarScore::Render()
{

}

void CLifeBarScore::Release()
{

}

void CLifeBarScore::SetPlayer(CPlayer* player)
{
	pPlayer = player;
}

void CLifeBarScore::AnimationUpdate()
{
	wstring str = L"";

	if (m_bChangeOrder)
	{
		if (m_bScoreBoard)
		{
			str = L"ScoreToRest";
		}
		else
		{
			str = L"RestToScore";
		}
	}
	else if (m_bScoreBoard)
	{
		str = L"ScoreBoardIdle";
	}
	else
	{
		str = L"RestBoard";
	}

	m_pAnimator->Play(str,false);
}
