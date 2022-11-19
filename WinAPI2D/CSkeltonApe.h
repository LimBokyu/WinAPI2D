#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;

class CSkeltonApe : public CGameObject
{
public:
	CSkeltonApe();
	virtual ~CSkeltonApe();

private:

	CAnimator* m_pAnimator;
	CImage* m_pMonsterMove;
	CImage* m_pMonsterIdle;
	CImage* m_pMonsterFall;
	CImage* m_pMonsterAttack;
	CImage* m_pMonsterAttaking;

	float m_fSpeed;
	float m_fTimer = 0;

	bool m_bMove;

public:

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void UpdateAnimation();

	void OnCollisionEnter(CCollider* pOtherCollider);
};

