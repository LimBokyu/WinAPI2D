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
	CPlayer* pPlayer;

	float m_fSpeed = 300;
	float m_fTimer = 0;
	float m_fThrow = 30;

	bool m_bChanged;
	bool m_bDelete;
	bool m_bTouchAble;

public:

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void Changed(bool trigger = true);
	void UpdateAnimation();
	void SetPlayer(CPlayer* player);

	void OnCollisionEnter(CCollider* pOtherCollider) override;
};
