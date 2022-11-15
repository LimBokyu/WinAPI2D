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
	CImage* m_pHeart;


	Vector curLookAt;
	Vector FirstLookAt;

	CPlayer* pPlayer;
	CAnimator* m_pAnimator;

	int Heart = 0;
	
public:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void New();
	void Score();
	void UpdateAnimation();
	void ItemUpdate();
};