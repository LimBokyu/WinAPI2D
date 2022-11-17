#pragma once
#include "CGameObject.h"

class CAnimator;
class CImage;
class CPlayer;

class CScoreBoardNum : public CGameObject
{
public:
	CScoreBoardNum();
	virtual ~CScoreBoardNum();
private:
	CAnimator* m_pAnimator;
	CPlayer* pPlayer;

	Vector m_StartLookAt;
	Vector m_curLookAt;

	CImage* m_pNumIdle;
	CImage* m_pNumOut;
	CImage* m_pNumIn;

	CImage* m_pNumNone;

	bool m_bScoreBoard;
	bool m_bChangeBoard;
	bool m_bChangeTrigger;

	int m_Credit;
	int m_Rest;
	int m_Score;

	int m_NumScale = 0;
	int m_TenScale;
	int m_OutputNum = 0;

	float m_fTimer = 0;

public:

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void SetPlayer(CPlayer* player);
	void SetScale(int scale);
	void ChangeBoard();
	void UpdateAnimation();
};

