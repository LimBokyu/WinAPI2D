#pragma once
#include "CGameObject.h"

class CAnimator;
class CImage;

class CHeart : public CGameObject
{
public:
	CHeart();
	virtual ~CHeart();

private:
	CAnimator* m_pAnimator;
	CImage* m_pHeart;

	float m_fVelocity = 50;
	float m_fSpeed = 100;
	float m_fTimer = 0;
	bool m_bReverse;
	bool m_bOnGround;

public:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider) override;

};

