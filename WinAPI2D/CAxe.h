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
	CPlayer* pPlayer;

	float m_fTimer;
	float m_fSpeed;
	float m_fThrow = 30;

	bool m_bChanged;
	bool m_bDelete;

public:

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void Changed(bool trigger = true);
	void UpdateAnimation();
	void SetPlayer(CPlayer* player);

	void OnCollisionEnter(CCollider* pOtherCollider);
};

