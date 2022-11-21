#pragma once
#include "CGameObject.h"

class CStair : public CGameObject
{
public:
	CStair();
	virtual ~CStair();

private:
	unsigned int m_Count = 0;
	bool m_bReverse;
	bool m_bTriggerOnce;

public:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void SetReverse(bool reverse = false);
	void SetCount(int count);
	void Repeat(int count);
	void CreateStair();
};

