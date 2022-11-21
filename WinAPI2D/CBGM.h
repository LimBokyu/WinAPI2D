#pragma once
#include "CGameObject.h"

class CBGM : public CGameObject
{
public:
	CBGM();
	virtual ~CBGM();

private:

public:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

