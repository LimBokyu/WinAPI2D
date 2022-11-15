#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;
class CPlayer;

class CLifeBarScore : public CGameObject
{
public:
	CLifeBarScore();
	virtual ~CLifeBarScore();

private:

public:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};