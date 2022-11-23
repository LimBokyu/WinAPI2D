#include "framework.h"
#include "CSceneStage01.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"
#include "CPathManager.h"
#include "CStage01EndObject.h"

CStage01EndObject::CStage01EndObject()
{
}

CStage01EndObject::~CStage01EndObject()
{
}

void CStage01EndObject::Init()
{
	AddCollider(ColliderType::Rect, Vector(50, WINSIZEY), Vector(0, 0));
}

void CStage01EndObject::Update()
{
}

void CStage01EndObject::Render()
{
}

void CStage01EndObject::Release()
{
}
