#pragma once
#include "CGameObject.h"

class CAnimator;
class CImage;
class CPlayer;

enum struct Type
{
	One,
	Ten
};

class CLifeBarHeart : public CGameObject
{
public:
	CLifeBarHeart();
	virtual ~CLifeBarHeart();

private:
	CImage* m_pHeart;
	CAnimator* m_pAnimator;

	CPlayer* pPlayer;
	Type type;

	Vector m_StartLookAt;
	Vector m_curLookAt;

	int Heart;

public:

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void GetPlayer(CPlayer* player);

	void UpdateAnimation();
	void OneOrTen(bool one = true);
};

