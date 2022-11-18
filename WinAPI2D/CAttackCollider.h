#pragma once
#include "CGameObject.h"

class CWhip;

class CAttackCollider : public CGameObject
{
public:
	CAttackCollider();
	virtual ~CAttackCollider();

	CWhip* m_pWhip;

	float m_fTimer;

private:

public:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void SetWhip(CWhip* whip);
};

