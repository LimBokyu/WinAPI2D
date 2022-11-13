#include "framework.h"
#include "CSceneStage01.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"
#include "CPathManager.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CCameraController.h"
#include "CButton.h"
#include "CPanel.h"
#include "CStage01Map.h"
#include "CStage01Effect.h"
#include "CStage01Effect2.h"
#include "CStage01Effect3.h"

CSceneStage01::CSceneStage01()
{
	pPlayer = nullptr;
	Map = nullptr;
	//m_Map = nullptr;
}

CSceneStage01::~CSceneStage01()
{
}

void CSceneStage01::Init()
{
	pPlayer = new CPlayer();
	pPlayer->SetPos(150, 376);
	AddGameObject(pPlayer);

	CSound* BGM = RESOURCE->LoadSound(L"Stage_01", L"Sound\\04_Opposing Bloodlines.mp3");

	
	Map = new CStage01Map();
	AddGameObject(Map);

	SOUND->Play(BGM, 0.5f, true);

	CMonster* pMonster = new CMonster();
	pMonster->SetPos(1000, WINSIZEY * 0.5f);
	AddGameObject(pMonster);
	
	CCameraController* pCamController = new CCameraController;
	AddGameObject(pCamController);

	CStage01Effect* pEffect = new CStage01Effect();
	pEffect->SetPos(1050,350);
	AddGameObject(pEffect);

	CStage01Effect2* pEffect2 = new CStage01Effect2();
	pEffect2->SetPos(1200, 70);
	AddGameObject(pEffect2);

	CStage01Effect3* pEffect3 = new CStage01Effect3();
	pEffect3->SetPos(464, 131);
	AddGameObject(pEffect3);

}

void CSceneStage01::Enter()
{
	CAMERA->FadeIn(0.25f);
	LoadTile(GETPATH + L"Tile\\Stage01.tile");
}

void CSceneStage01::Update()
{
	if (BUTTONDOWN(VK_ESCAPE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Title, 0.25f);
	}
}

void CSceneStage01::Render()
{
}

void CSceneStage01::Exit()
{
}

void CSceneStage01::Release()
{
}
