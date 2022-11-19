#pragma once
#include "CGameObject.h"

class CWhip;

class CLongAttackCollider : public CGameObject
{
public:
	CLongAttackCollider();
	virtual ~CLongAttackCollider();

private:
	CWhip* m_pWhip;

public:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void SetWhip(CWhip* whip);
};

