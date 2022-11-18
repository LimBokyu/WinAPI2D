#pragma once
#include "CGameObject.h"

class CAnimator;
class CImage;

class CHeart : public CGameObject
{
public:
	CHeart();
	virtual ~CHeart();

private:


public:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

