#pragma once

#include "CGameObject.h"
class CStage01EndObject : public CGameObject
{
public:
	CStage01EndObject();
	virtual ~CStage01EndObject();

private:


public:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

