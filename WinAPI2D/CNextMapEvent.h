#pragma once
#include "CGameObject.h"
class CNextMapEvent : public CGameObject
{
public:
	CNextMapEvent();
	virtual ~CNextMapEvent();

public:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider);

};

