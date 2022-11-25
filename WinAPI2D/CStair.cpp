#include "framework.h"
#include "CStair.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CResourceManager.h"
#include "CCollider.h"

#define SIZE 16

CStair::CStair()
{
	m_layer = Layer::Stair;
	m_bReverse = false;
	m_bTriggerOnce = true;
}

CStair::~CStair()
{
}

void CStair::Init()
{
	AddCollider(ColliderType::Rect, Vector(SIZE, SIZE), Vector(0, 0));

	if (!m_bReverse)
	{
		m_strName = L"RightStair";
	}
	else
	{
		m_strName = L"LeftStair";
	}
}

void CStair::Update()
{
	Repeat(m_Count);
}

void CStair::Render()
{
}

void CStair::Release()
{
}

void CStair::SetReverse(bool reverse)
{
	m_bReverse = reverse;
}

void CStair::SetCount(int count)
{
	m_Count = count;
}

void CStair::Repeat(int count)
{
	if (m_bTriggerOnce)
	{
		SetCount(count);
		CreateStair();
		m_bTriggerOnce = false;
	}
	else
		return;
	
}

void CStair::CreateStair()
{
	if (m_Count > 0)
	{
		m_Count--;
		if (!m_bReverse)
		{
			CStair* stair = new CStair();
			stair->SetPos(m_vecPos.x + SIZE, m_vecPos.y - SIZE);
			stair->SetCount(m_Count);
			ADDOBJECT(stair);
		}
		else
		{
			CStair* stair = new CStair();
			stair->SetPos(m_vecPos.x - SIZE, m_vecPos.y - SIZE);
			stair->SetReverse(m_bReverse);
			stair->SetCount(m_Count);
			ADDOBJECT(stair);
		}
	}
}
