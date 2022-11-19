#pragma once
#include "CGameObject.h"

class CAnimator;
class CImage;
class CPlayer;

class CCredit : public CGameObject
{
public:
	CCredit();
	virtual ~CCredit();

private:
	CAnimator* m_pAnimator;
	CImage* m_pCredit;
	CPlayer* pPlayer;

	float m_fVelocity = 300;
	int m_Credit = 0;

public:

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void SetCredit(int credit);
	void UpdateAnimation();
	void SetPlayer(CPlayer* player);

	void OnCollisionEnter(CCollider* pOtherCollider) override;

};

