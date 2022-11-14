#pragma once
#include "CGameObject.h"

class CAnimator;
class CImage;

class CStage01Effect3 : public CGameObject
{
public:
	CStage01Effect3();
	virtual ~CStage01Effect3();

private:
	CAnimator* m_pAnimator;
	CImage* m_pImage;
	CImage* m_MiddleMap;

	Vector startLook;
	Vector curLook;

public:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

