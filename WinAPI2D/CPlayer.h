#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;

class CPlayer : public CGameObject
{
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
	// ㄴ 캐릭터 움직임 이미지
	CImage* m_pAttackImage;
	CImage* m_pDuckAttackImage;
	// ㄴ 캐릭터 공격 이미지
	CImage* m_pJumpImage;
	CImage* m_pBackFlipImage;
	// ㄴ캐릭터 점프 이미지

	// 캐릭터 반전 이미지
	CImage* m_pIdleImageR;
	CImage* m_pDuckImageR;
	CImage* m_pMoveImageR;
	CImage* m_pLookUpImageR;
	// ㄴ 캐릭터 움직임 이미지
	CImage* m_pAttackImageR;
	CImage* m_pDuckAttackImageR;
	// ㄴ 캐릭터 공격 이미지
	CImage* m_pJumpImageR;
	CImage* m_pBackFlipImageR;
	// ㄴ캐릭터 점프 이미지
	//============================

	Vector m_vecMoveDir;
	Vector m_vecLookDir;

	bool m_bIsMove;
	bool m_bDuck;
	bool m_bReverse;
	bool m_bAttack;
	bool m_bJump;
	bool m_bBackFlip;
	bool m_bLookup;

	float m_fAttackTime = 0;
	float m_fJumpTime = 0;
	float m_fDuckTime = 0;

	float m_fSpeed = 200.0f;

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
};