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

	Vector curLookAt;
	Vector FirstLookAt;

public:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};