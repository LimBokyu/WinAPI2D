#pragma once
#include "CGameObject.h"
#include "CPlayer.h"

class CImage;
class CAnimator;

class CSubWeapon : public CGameObject
{
public:
	CSubWeapon();
	virtual ~CSubWeapon();
	PlayerITEM pItem;

private:
	CImage* m_pDagger;
	CImage* m_pAxe;
	CAnimator* m_pAnimator;
	CPlayer* pPlayer;

public:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void SetItem();
	void SetPlayer();
};

