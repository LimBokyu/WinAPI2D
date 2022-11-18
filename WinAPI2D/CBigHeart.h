#pragma once
#include "CGameObject.h"

class CAnimator;
class CImage;

class CBigHeart : public CGameObject
{
public:
	CBigHeart();
	virtual ~CBigHeart();

private:
	CAnimator* m_pAnimator;
	CImage* m_pHeart;

	float m_fVelocity = 300;

public:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider) override;
};

