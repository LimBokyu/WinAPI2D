#include "framework.h"
#include "CTimeManager.h"

CTimeManager::CTimeManager()
{
	m_uiFPS = 1;
	m_fDT = 1;
	m_fUDT = 1;
	updateCount = 0;
	updateOneSecond = 0;

	m_bStop = false;

	prevTime = {};
	curTime = {};
}

CTimeManager::~CTimeManager()
{
}

void CTimeManager::Init()
{
	prevTime = chrono::high_resolution_clock::now();
}

void CTimeManager::Update()
{
	// 이전프레임에서 현재프레임까지 걸린 시간을 측정
	// 단위시간 = 현재프레임시간 - 이전프레임시간
	curTime = chrono::high_resolution_clock::now();
	chrono::duration<float> elapsed = curTime - prevTime;

	m_fDT = elapsed.count();
	m_fUDT = elapsed.count();

	if (m_fDT > 0.1f) m_fDT = 0.1f;
	if (m_fUDT > 0.1f) m_fUDT = 0.1f;
	prevTime = curTime;

	if (m_bStop)
	{
		m_fDT = 0;
	}

	// 1초가 걸릴때까지 반복한 횟수가 초당프레임수
	updateCount++;
	updateOneSecond += m_fDT;
	if (updateOneSecond >= 1.0)
	{
		m_uiFPS = updateCount;
		updateOneSecond = 0;
		updateCount = 0;
	}
}

void CTimeManager::Release()
{
}

UINT CTimeManager::GetFPS()
{
	return m_uiFPS;
}

float CTimeManager::GetDT()
{
	return m_fDT;
}

float CTimeManager::GetUDT()
{
	return m_fUDT;
}

void CTimeManager::StopTime()
{
	m_bStop = true;
}

void CTimeManager::GoTime()
{
	m_bStop = false;
}
