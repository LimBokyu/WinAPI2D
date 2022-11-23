#pragma once
#include "CGameObject.h"

class CAnimator;
class CImage;
class CPlayer;

class CDagger : public CGameObject
{
public:
	CDagger();
	virtual ~CDagger();
private:
	CImage* m_pDagger;
	CAnimator* m_pAnimator;

	float m_fSpeed = 300;
	float m_fTimer = 0;
	float m_fThrow = 100;
	float m_fTriggerTimer = 0;

	bool m_bChanged;
	bool m_bDelete;
	bool m_bTouchAble;
	bool m_bCollisionTrigger;
	bool m_bReverse;

public:

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void Changed(bool trigger = true);
	void UpdateAnimation();
	void SetReverse(bool reverse);

	void OnCollisionEnter(CCollider* pOtherCollider) override;
};
