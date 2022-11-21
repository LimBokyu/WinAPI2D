#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;

enum struct PlayerITEM
{
	Default,

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

	// ======ĳ���� �̹���=========
	CImage* m_pIdleImage;
	CImage* m_pDuckImage;
	CImage* m_pMoveImage;
	CImage* m_pLookUpImage;
	CImage* m_pStairUp;
	CImage* m_pStairDown;
	// �� ĳ���� ������ �̹���
	CImage* m_pAttackImage;
	CImage* m_pAttackingImage;
	CImage* m_pDuckAttackImage;
	CImage* m_pDuckAttackingImage;
	CImage* m_pStairUpAttack;
	CImage* m_pStairDownAttack;
	CImage* m_pSubWeaponImage;
	// �� ĳ���� ���� �̹���
	CImage* m_pJumpImage;
	CImage* m_pBackFlipImage;
	// ��ĳ���� ���� �̹���

	// ----ĳ���� ���� �̹���-------
	CImage* m_pIdleImageR;
	CImage* m_pDuckImageR;
	CImage* m_pMoveImageR;
	CImage* m_pLookUpImageR;
	CImage* m_pStairUpR;
	CImage* m_pStairDownR;
	// �� ĳ���� ������ �̹���
	CImage* m_pAttackImageR;
	CImage* m_pAttackingImageR;
	CImage* m_pDuckAttackImageR;
	CImage* m_pDuckAttackingImageR;
	CImage* m_pStairUpAttackR;
	CImage* m_pStairDownAttackR;
	CImage* m_pSubWeaponImageR;
	// �� ĳ���� ���� �̹���
	CImage* m_pJumpImageR;
	CImage* m_pBackFlipImageR;
	// ��ĳ���� ���� �̹���
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
	bool m_bAttacking;
	bool m_bTriggerOnce;

	bool m_bStop;

	float m_fAttackTime = 0;
	float m_fJumpTime = 0;
	float m_fDuckTime = 0;

	float m_fSpeed = 150.0f;
	float m_fVelocity = 150.0f;

	int m_Score;
	int m_Life;

	unsigned int m_Heart;
	unsigned int m_Credit;
	unsigned int m_Rest = 13;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void AnimatorUpdate();
	void WhipAttack();
	void CreateItem();
	void ItemCrash();

	void OnCollisionEnter(CCollider* pOtherCollider) override;
	void OnCollisionStay(CCollider* pOtherCollider) override;
	void OnCollisionExit(CCollider* pOtherCollider) override;

public:
	PlayerITEM pItem;
	PlayerITEM prevItem;

	PlayerITEM GetItem();
	void SetItem(PlayerITEM item);

	int GetHeart();
	void SetHeart(int heart);

	int GetCredit();
	void SetCredit(int credit);

	int GetRest();

	int GetScore();
	void SetScore(int score);

	bool GetReverse();
	bool GetDuck();

	void SwitchItem();
	void DropItem();

	void SetStop(bool stop);
	void SwitchStop();
};