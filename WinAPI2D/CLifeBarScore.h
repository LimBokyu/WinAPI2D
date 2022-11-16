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
	CAnimator* m_pAnimator;
	CPlayer* pPlayer;

	Vector m_StartLookAt;
	Vector m_curLookAt;

	CImage* m_pScoreBoard;
	CImage* m_pRestBoard;
	CImage* m_pScoreNum;

	CImage* m_pScoreToRest;
	CImage* m_pRestToScore;

	float m_fTimer;

	bool m_bScoreBoard;
	bool m_bChangeOrder;

public:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void SetPlayer(CPlayer* player);
	void AnimationUpdate();
};