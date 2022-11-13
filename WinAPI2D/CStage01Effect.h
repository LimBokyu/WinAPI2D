#pragma once
#include "CGameObject.h"

class CAnimator;
class CImage;

class CStage01Effect :  public CGameObject
{
public:
	CStage01Effect();
	virtual ~CStage01Effect();

private:
	CImage* m_Fire01;
	CAnimator* m_pAnimator;

public:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

