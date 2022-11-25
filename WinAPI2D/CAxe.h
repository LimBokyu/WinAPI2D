#pragma once
#include "CGameObject.h"

class CAnimator;
class CImage;
class CPlayer;

class CAxe : public CGameObject
{
public:
	CAxe();
	virtual ~CAxe();

private:
	CAnimator* m_pAnimator;
	CImage* m_pAxe;

	float m_fTimer;
	float m_fSpeed;
	float m_fThrow = 30;
	float m_fTriggerTimer = 0;

	bool m_bChanged;
	bool m_bDelete;
	bool m_bCollisionTrigger;
	bool m_bReverse;

public:

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void SetReverse(bool reverse);

	void Changed(bool trigger = true);
	void UpdateAnimation();

	void OnCollisionEnter(CCollider* pOtherCollider);
};

