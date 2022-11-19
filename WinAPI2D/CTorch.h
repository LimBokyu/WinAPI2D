#pragma once
#include "CGameObject.h"

class CAnimator;
class CImage;
class CPlayer;

enum struct ItemCase
{
	Null,
	Credit,
	Heart,
	BigHeart,
	Dagger,
	Axe,
	Cross,
	HollyWater,
	Bible,
	Clock,

	size
};

class CTorch : public CGameObject
{
public:
	CTorch();
	virtual ~CTorch();

private:
	CAnimator* m_pAnimator;
	CImage* m_pTorch;
	ItemCase m_Item;
	CPlayer* pPlayer;

	int m_credit;

public:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void SetItem(ItemCase item);
	void SetCredit(int credit);
	void CreateHeart();
	void CreateBigHeart();
	void CreateCredit();
	void CreateAxe();
	void CreateDagger();
	void SetPlayer(CPlayer* player);

	void OnCollisionEnter(CCollider* pOtherCollider);
};

