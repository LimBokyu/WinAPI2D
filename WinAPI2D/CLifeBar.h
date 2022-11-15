#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;
class CPlayer;

class CLifeBar : public CGameObject
{
public:
	CLifeBar();
	virtual ~CLifeBar();

private:

	CImage* m_pLifeBar;
	CImage* m_pLifeBarGauge;
	CImage* m_pItemDagger;
	CImage* m_pItemAxe;
	CImage* m_pItemHollyWater;
	CImage* m_pItemCross;
	CImage* m_pItemClock;
	CImage* m_pItemBible;

	Vector curLookAt;
	Vector FirstLookAt;

	CPlayer* pPlayer;
	
public:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void SetPlayer(CPlayer* player);
	void UpdateAnimation();
	void ItemUpdate();
};