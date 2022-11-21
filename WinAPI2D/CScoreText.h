#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;
class CCredit;

class CScoreText : public CGameObject
{
public:
	CScoreText();
	virtual ~CScoreText();

private:
	CAnimator* m_pAnimator;
	CImage*    m_pScore;
	CCredit*   m_pCredit;

	int m_Credit;
	float m_fTimer = 0;
	float m_fSpeed = 100;

public:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void UpdateAnimation();

	void SetCredit(int credit);
};

