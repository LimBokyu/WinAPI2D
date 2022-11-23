#include "framework.h"
#include "CStage01_1.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"
#include "CPathManager.h"

#include "CPlayer.h"

CStage01_1::CStage01_1()
{
	pPlayer = nullptr;
	m_pMap = nullptr;
}

CStage01_1::~CStage01_1()
{
}

void CStage01_1::Init()
{
	
}

void CStage01_1::Update()
{

}

void CStage01_1::Render()
{
}

void CStage01_1::Release()
{
}

void CStage01_1::SetPlayer(CPlayer* player)
{
	pPlayer = player;
}
