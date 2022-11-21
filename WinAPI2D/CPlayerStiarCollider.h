#pragma once
#include "CGameObject.h"

class CPlayer;

class CPlayerStiarCollider : public CGameObject
{
public:
	CPlayerStiarCollider();
	virtual ~CPlayerStiarCollider();

private:
	CPlayer* pPlayer;

public:

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;


};

