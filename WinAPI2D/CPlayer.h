#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;

enum struct PlayerITEM
{
	None,
	Dagger,
	Axe,
	HolyWater,
	Cross,
	Clock,
	Bible,


	Size
};

class CPlayer : public CGameObject
{
	friend class CLifeBar;
public:
	CPlayer();
	virtual ~CPlayer();

private:
	CAnimator* m_pAnimator;

	// ======캐릭터 이미지=========
	CImage* m_pIdleImage;
	CImage* m_pDuckImage;
	CImage* m_pMoveImage;
	CImage* m_pLookUpImage;
	CImage* m_pStairUp;
	CImage* m_pStairDown;
	// ㄴ 캐릭터 움직임 이미지
	CImage* m_pAttackImage;
	CImage* m_pDuckAttackImage;
	CImage* m_pStairUpAttack;
	CImage* m_pStairDownAttack;
	CImage* m_pSubWeaponImage;
	// ㄴ 캐릭터 공격 이미지
	CImage* m_pJumpImage;
	CImage* m_pBackFlipImage;
	// ㄴ캐릭터 점프 이미지

	// ----캐릭터 반전 이미지-------
	CImage* m_pIdleImageR;
	CImage* m_pDuckImageR;
	CImage* m_pMoveImageR;
	CImage* m_pLookUpImageR;
	CImage* m_pStairUpR;
	CImage* m_pStairDownR;
	// ㄴ 캐릭터 움직임 이미지
	CImage* m_pAttackImageR;
	CImage* m_pDuckAttackImageR;
	CImage* m_pStairUpAttackR;
	CImage* m_pStairDownAttackR;
	CImage* m_pSubWeaponImageR;
	// ㄴ 캐릭터 공격 이미지
	CImage* m_pJumpImageR;
	CImage* m_pBackFlipImageR;
	// ㄴ캐릭터 점프 이미지
	//============================

	Vector m_vecMoveDir;

	bool m_bIsMove;
	bool m_bDuck;
	bool m_bReverse;
	bool m_bAttack;
	bool m_bJump;
	bool m_bBackFlip;
	bool m_bLookup;
	bool m_bAttackinBackFlip;
	bool m_bOnStair;
	bool m_bCommandBlock;

	float m_fAttackTime = 0;
	float m_fJumpTime = 0;
	float m_fDuckTime = 0;

	float m_fSpeed = 150.0f;

	float m_fScore;
	float m_fLife;

	unsigned int m_Heart;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void AnimatorUpdate();
	void CreateMissile();

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;

public:
	PlayerITEM pItem;

	PlayerITEM GetItem();
	void SetItem(PlayerITEM item);

	int GetHeart();
	void SetHeart(int heart);
};