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

	// ======ĳ���� �̹���=========
	CImage* m_pIdleImage;
	CImage* m_pDuckImage;
	CImage* m_pMoveImage;
	CImage* m_pLookUpImage;
	// �� ĳ���� ������ �̹���
	CImage* m_pAttackImage;
	CImage* m_pDuckAttackImage;
	// �� ĳ���� ���� �̹���
	CImage* m_pJumpImage;
	CImage* m_pBackFlipImage;
	// ��ĳ���� ���� �̹���

	// ĳ���� ���� �̹���
	CImage* m_pIdleImageR;
	CImage* m_pDuckImageR;
	CImage* m_pMoveImageR;
	CImage* m_pLookUpImageR;
	// �� ĳ���� ������ �̹���
	CImage* m_pAttackImageR;
	CImage* m_pDuckAttackImageR;
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


	float m_fAttackTime = 0;
	float m_fJumpTime = 0;
	float m_fDuckTime = 0;

	float m_fSpeed = 150.0f;

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