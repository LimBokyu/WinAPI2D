#pragma once
#include "CGameObject.h"

class CWhip;
class CSound;

class CAttackCollider : public CGameObject
{
public:
	CAttackCollider();
	virtual ~CAttackCollider();

private:
	CWhip* m_pWhip;
	CSound* m_pSoundEffect;

public:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void SetWhip(CWhip* whip);
};

