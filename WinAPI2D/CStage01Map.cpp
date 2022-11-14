#include "framework.h"
#include "CSceneStage01.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"
#include "CPathManager.h"
#include "CStage01Map.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CCameraController.h"
#include "CButton.h"
#include "CPanel.h"

CStage01Map::CStage01Map()
{
	m_layer = Layer::NearMap;
	m_Map = nullptr;
	m_strName = L"Stage_01 Map";
}

CStage01Map::~CStage01Map()
{
}

void CStage01Map::Init()
{
	m_Map = RESOURCE->LoadImg(L"stage01_map1", L"Image\\Stage_01.png");
}

void CStage01Map::Render()
{
	RENDER->Image(m_Map, 0, 480, 1024 * 2, 480 - (168 * 2));
}

void CStage01Map::Update()
{
}

void CStage01Map::Release()
{
}
