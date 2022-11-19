#pragma once
#include "CGameObject.h"

class CAnimator;
class CImage;
class CPlayer;

class CWhip : public CGameObject
{
public:
	CWhip();
	virtual ~CWhip();

private:

	CImage* m_pNormalAttack;
	CImage* m_pLongAttack;
	CImage* m_pNormalAttackR;
	CImage* m_pLongAttackR;

	CImage* m_pDuckNormalAttack;
	CImage* m_pDuckLongAttack;

	CImage* m_pDuckNormalAttackR;
	CImage* m_pDuckLongAttackR;

	CAnimator* m_pAnimator;

	CPlayer* pPlayer;

	Vector m_vecDir;
	Vector m_vecLong;
	Vector m_vecDotFix;

	float m_fVelocity;
	float m_AttackTime;

	bool m_bLongAttack;
	bool m_bReverse;
	bool m_bDuck;
	bool m_bHit;
	bool m_bTriggerOnce;

public:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void SetPlayer(CPlayer* player);
	void UpdateAnimation();
};

