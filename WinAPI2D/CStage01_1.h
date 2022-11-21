#pragma once
#include "CScene.h"

class CPlayer;

class CStage01_1 : public CScene
{
public:
	CStage01_1();
	virtual ~CStage01_1();

private:
	CPlayer* pPlayer;


public:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void SetPlayer(CPlayer* player);

};

