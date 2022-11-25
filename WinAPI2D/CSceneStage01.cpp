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
#include "CLifeBar.h"
#include "CLifeBarHeart.h"
#include "CLifeBarScore.h"
#include "CScoreBoardNum.h"
#include "CTorch.h"
#include "CSkeltonApe.h"
#include "CStair.h"
#include "CBGM.h"
#include "CObstacle.h"

CSceneStage01::CSceneStage01()
{
	pPlayer = nullptr;
	Map = nullptr;
}

CSceneStage01::~CSceneStage01()
{
}

void CSceneStage01::Init()
{
	pPlayer = new CPlayer();
	pPlayer->SetPos(150, 376);
	AddGameObject(pPlayer);

#pragma region 라이프바와 스코어바 본체와 숫자의 구현

	CLifeBar* Lifebar = new CLifeBar();
	Lifebar->SetPlayer(pPlayer);
	AddGameObject(Lifebar);

	CLifeBarHeart* Heart = new CLifeBarHeart();
	Heart->SetPlayer(pPlayer);
	Heart->OneOrTen(true);
	AddGameObject(Heart);

	CLifeBarHeart* Heart10 = new CLifeBarHeart();
	Heart10->SetPlayer(pPlayer);
	Heart10->OneOrTen(false);
	AddGameObject(Heart10);

	CLifeBarScore* ScoreBoard = new CLifeBarScore();
	ScoreBoard->SetPlayer(pPlayer);
	AddGameObject(ScoreBoard);

	CScoreBoardNum* Num = new CScoreBoardNum();
	Num->SetPlayer(pPlayer);
	AddGameObject(Num);

	CScoreBoardNum* Num1 = new CScoreBoardNum();
	Num1->SetPlayer(pPlayer);
	Num1->SetScale(1);
	AddGameObject(Num1);

	CScoreBoardNum* Num2 = new CScoreBoardNum();
	Num2->SetPlayer(pPlayer);
	Num2->SetScale(2);
	AddGameObject(Num2);

	CScoreBoardNum* Num3 = new CScoreBoardNum();
	Num3->SetPlayer(pPlayer);
	Num3->SetScale(3);
	AddGameObject(Num3);

	CScoreBoardNum* Num4 = new CScoreBoardNum();
	Num4->SetPlayer(pPlayer);
	Num4->SetScale(4);
	AddGameObject(Num4);

	CScoreBoardNum* Num5 = new CScoreBoardNum();
	Num5->SetPlayer(pPlayer);
	Num5->SetScale(5);
	AddGameObject(Num5);

	CScoreBoardNum* Num6 = new CScoreBoardNum();
	Num6->SetPlayer(pPlayer);
	Num6->SetScale(6);
	AddGameObject(Num6);

#pragma endregion

#pragma region 화로 생성

	CTorch* torch1 = new CTorch();
	torch1->SetPos(350, 335);
	torch1->SetItem(ItemCase::Heart);
	AddGameObject(torch1);

	CTorch* torch2 = new CTorch();
	torch2->SetPos(650, 365);
	torch2->SetPlayer(pPlayer);
	torch2->SetItem(ItemCase::Dagger);
	AddGameObject(torch2);

	CTorch* torch3 = new CTorch();
	torch3->SetPos(800, 190);
	torch3->SetCredit(100);
	torch3->SetPlayer(pPlayer);
	torch3->SetItem(ItemCase::Credit);
	AddGameObject(torch3);

	CTorch* torch4 = new CTorch();
	torch4->SetPos(900, 365);
	torch4->SetItem(ItemCase::Heart);
	AddGameObject(torch4);

	CTorch* torch5 = new CTorch();
	torch5->SetPos(1200, 365);
	torch5->SetItem(ItemCase::Heart);
	AddGameObject(torch5);

	CTorch* torch6 = new CTorch();
	torch6->SetPos(1450, 365);
	torch6->SetPlayer(pPlayer);
	torch6->SetItem(ItemCase::Axe);
	AddGameObject(torch6);

#pragma endregion

#pragma region 몬스터 생성

	CSkeltonApe* SA = new CSkeltonApe();
	SA->SetPos(620, 365);
	SA->SetPlayer(pPlayer);
	AddGameObject(SA);

	CSkeltonApe* SA2 = new CSkeltonApe();
	SA2->SetPos(900, 365);
	SA2->SetPlayer(pPlayer);
	AddGameObject(SA2);

	CSkeltonApe* SA3 = new CSkeltonApe();
	SA3->SetPos(1100, 365);
	SA3->SetPlayer(pPlayer);
	AddGameObject(SA3);

	CSkeltonApe* SA4 = new CSkeltonApe();
	SA4->SetPos(1400, 365);
	SA4->SetPlayer(pPlayer);
	AddGameObject(SA4);

	CSkeltonApe* SA5 = new CSkeltonApe();
	SA5->SetPos(1600, 365);
	SA5->SetPlayer(pPlayer);
	AddGameObject(SA5);

	CSkeltonApe* SA6 = new CSkeltonApe();
	SA6->SetPos(1800, 365);
	SA6->SetPlayer(pPlayer);
	AddGameObject(SA6);

	CSkeltonApe* SA7 = new CSkeltonApe();
	SA7->SetPos(2000, 365);
	SA7->SetPlayer(pPlayer);
	AddGameObject(SA7);

#pragma endregion

#pragma region 계단 생성

	CStair* stair = new CStair();
	stair->SetCount(11);
	stair->SetPos(520,423);
	AddGameObject(stair);

	CStair* stair1 = new CStair();
	stair1->SetCount(11);
	stair1->SetReverse(true);
	stair1->SetPos(1080, 423);
	AddGameObject(stair1);

#pragma endregion

	Map = new CStage01Map();
	AddGameObject(Map);

	
	CCameraController* pCamController = new CCameraController;
	AddGameObject(pCamController);

	CObstacle* ob = new CObstacle;
	ob->SetPos(160, 430);
	ob->SetScale(Vector(320, 32));
	AddGameObject(ob);

	CObstacle* ob2 = new CObstacle;
	ob2->SetPos(343, 400);
	ob2->SetScale(Vector(178, 32));
	AddGameObject(ob2);

#pragma region 맵 이펙트 및 애니메이션

	CStage01Effect* pEffect = new CStage01Effect();
	pEffect->SetPos(1050,350);
	AddGameObject(pEffect);

	CStage01Effect2* pEffect2 = new CStage01Effect2();
	pEffect2->SetPos(1200, 70);
	AddGameObject(pEffect2);

	CStage01Effect3* pEffect3 = new CStage01Effect3();
	pEffect3->SetPos(0, 0);
	AddGameObject(pEffect3);

#pragma endregion


}

void CSceneStage01::Enter()
{
	CAMERA->FadeIn(0.25f);
	LoadTile(GETPATH + L"Tile\\Stage01.tile");
	CBGM* bgm = new CBGM();
	AddGameObject(bgm);
}

void CSceneStage01::Update()
{
	if (BUTTONDOWN(VK_ESCAPE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Title, 0.25f);
	}

	if (pPlayer->GetPos().x >= WINSIZEX * 0.5f)
	{
		CAMERA->SetTargetObj(pPlayer);
	}

	if (pPlayer->GetPos().x < WINSIZEX * 0.5f)
	{
		CAMERA->SetTargetObj(nullptr);
		CAMERA->SetTargetPos(Vector(WINSIZEX * 0.5f, WINSIZEY * 0.5f), 0);
	}

	if (pPlayer->GetPos().x > (1024 * 2) - (WINSIZEX * 0.5f))
	{
		CAMERA->SetTargetObj(nullptr);
		CAMERA->SetTargetPos(Vector((1024*2) - (WINSIZEX * 0.5f), WINSIZEY * 0.5f), 0);
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
