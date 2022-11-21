#include "framework.h"
#include "CSceneStage01.h"
#include "CBGM.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"
#include "CPathManager.h"

CBGM::CBGM()
{
}

CBGM::~CBGM()
{
}

void CBGM::Init()
{
	CSound* BGM = RESOURCE->LoadSound(L"Stage_01", L"Sound\\04_Opposing Bloodlines.mp3");
	SOUND->Play(BGM, 0.5f, true);
}

void CBGM::Update()
{
}

void CBGM::Render()
{
}

void CBGM::Release()
{
}
