#pragma once
#include "CGameObject.h"
class CAnimationObject :  public CGameObject
{
public:
	CAnimationObject();
	virtual ~CAnimationObject();

public:

	void Init() override;
	void Update() override;
	void Release() override;
	void Render() override;
};

