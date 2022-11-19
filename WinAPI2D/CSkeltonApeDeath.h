#pragma once
#include "CGameObject.h"

class CAnimator;
class CImage;

class CSkeltonApeDeath : public CGameObject
{
public:
	CSkeltonApeDeath();
	virtual ~CSkeltonApeDeath();

private:
	CImage* m_pDeathImage;
	CAnimator* m_pAnimator;

	float m_fTimer = 0;

public:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

