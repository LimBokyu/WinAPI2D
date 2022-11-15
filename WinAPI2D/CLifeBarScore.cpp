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
	m_pScoreNum = nullptr;
	m_pAnimator = nullptr;
	pPlayer = nullptr;

	m_StartLookAt = Vector(WINSIZEX * 0.5f, WINSIZEY * 0.5f);
	m_curLookAt = Vector(WINSIZEX * 0.5f, WINSIZEY * 0.5f);
}

CLifeBarScore::~CLifeBarScore()
{

}

void CLifeBarScore::Init()
{
	m_pScoreBoard = RESOURCE->LoadImg(L"ScoreBoard",L"Image\\PlayerScore.png");
	m_pScoreNum = RESOURCE->LoadImg(L"ScoreNum", L"Image\\PlayerScoreNum.png");
}

void CLifeBarScore::Update()
{
	m_vecPos = m_curLookAt - m_StartLookAt + Vector(0,0);
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