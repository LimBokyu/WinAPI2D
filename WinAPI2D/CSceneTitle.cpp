#include "framework.h"
#include "CSceneTitle.h"

#include "WinAPI.h"
#include "CRenderManager.h"
#include "CInputManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"
#include "CTitle.h"

CSceneTitle::CSceneTitle()
{
	m_bTrigger = false;
	m_bSound = false;

	title = nullptr;
}

CSceneTitle::~CSceneTitle()
{
}

void CSceneTitle::Init()
{
	title = new CTitle();
	title->SetPos(WINSIZEX * 0.5f, WINSIZEY * 0.5f);
	AddGameObject(title);
}

void CSceneTitle::Enter()
{
	CAMERA->FadeIn(0.25f);
}

void CSceneTitle::Update()
{
	title->SetTrigger(m_bTrigger);

	if (BUTTONDOWN(VK_F1))
	{
		CHANGESCENE(GroupScene::TileTool);
	}
	if (BUTTONDOWN(VK_SPACE))
	{
		m_bTrigger = true;
	}

	if (m_bTrigger)
	{
		m_fTimer += DT;
		PlaySoundEffect();
		if (m_fTimer > 3)
		{
			CAMERA->FadeOut(0.25f);
			DELAYCHANGESCENE(GroupScene::Stage01, 0.25f);
		}
	}
}

void CSceneTitle::Render()
{
	/*RENDER->Text(L"press space to start",
		WINSIZEX * 0.5f - 100,
		WINSIZEY * 0.5f - 10,
		WINSIZEX * 0.5f + 100,
		WINSIZEY * 0.5f + 10,
		Color(0, 0, 0, 1.f),
		20.f);*/
}

void CSceneTitle::Exit()
{
}

void CSceneTitle::Release()
{
}

void CSceneTitle::PlaySoundEffect()
{
	if (!m_bSound)
	{
		CSound* BGM = RESOURCE->LoadSound(L"Start", L"Sound\\Start.mp3");
		SOUND->Play(BGM, 0.5f, false);
		m_bSound = true;
	}
}
