#pragma once
#include "CGameObject.h"
class CTitle : public CGameObject
{
public:

	CTitle();
	virtual ~CTitle();

private:
	CImage* m_pTitle;
	CAnimator* m_pAnimator;

	bool m_bTrigger;

public:

	void Init() override;
	void Render() override;
	void Release() override;
	void Update() override;

	void SetTrigger(bool trigger);

	void UpdateAnimation();
};

