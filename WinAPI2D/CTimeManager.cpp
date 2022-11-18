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
	// ���������ӿ��� ���������ӱ��� �ɸ� �ð��� ����
	// �����ð� = ���������ӽð� - ���������ӽð�
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

	// 1�ʰ� �ɸ������� �ݺ��� Ƚ���� �ʴ������Ӽ�
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
