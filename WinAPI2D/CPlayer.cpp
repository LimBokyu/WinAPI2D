#include "framework.h"
#include "CPlayer.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CResourceManager.h"
#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"

#include "CMissile.h"

CPlayer::CPlayer()
{
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(46, 91);
	m_layer = Layer::Player;
	pItem = PlayerITEM::None;
	m_strName = L"플레이어";

#pragma region 이미지용 포인터 초기화

	m_pIdleImage = nullptr;
	m_pDuckImage = nullptr;
	m_pMoveImage = nullptr;
	m_pJumpImage = nullptr;

	m_pAttackImage = nullptr;
	m_pDuckAttackImage = nullptr;

	m_pIdleImageR = nullptr;
	m_pDuckImageR = nullptr;
	m_pMoveImageR = nullptr;
	m_pJumpImageR = nullptr;

	m_pAttackImageR = nullptr;
	m_pDuckAttackImageR = nullptr;

	m_pBackFlipImage = nullptr;
	m_pBackFlipImageR = nullptr;

	m_pLookUpImage = nullptr;
	m_pLookUpImageR = nullptr;

	m_pSubWeaponImage = nullptr;
	m_pSubWeaponImageR = nullptr;

	m_pStairDown = nullptr;
	m_pStairUp = nullptr;
	m_pStairDownR = nullptr;
	m_pStairUpR = nullptr;

	m_pStairDownAttack = nullptr;
	m_pStairDownAttackR = nullptr;

	m_pStairUpAttack = nullptr;
	m_pStairUpAttackR = nullptr;

#pragma endregion

	m_vecMoveDir = Vector(0, 0);

	m_bIsMove = false;
	m_bDuck = false;
	m_bReverse = false;
	m_bAttack = false;
	m_bJump = false;
	m_bBackFlip = false;
	m_bLookup = false;
	m_bAttackinBackFlip = false;
	m_bOnStair = false;

}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{

#pragma region 캐릭터 이미지 로드

	// 캐릭터가 오른쪽을 보고있는 이미지 파일 로드
	m_pIdleImage = RESOURCE->LoadImg(L"PlayerIdle", L"Image\\PlayerIdle.png");
	m_pDuckImage = RESOURCE->LoadImg(L"PlayerDuck", L"Image\\PlayerDuck.png");
	m_pMoveImage = RESOURCE->LoadImg(L"PlayerMove", L"Image\\PlayerMove.png");
	m_pJumpImage = RESOURCE->LoadImg(L"PlayerJump", L"Image\\PlayerJump.png");
	m_pLookUpImage = RESOURCE->LoadImg(L"PlayerUp", L"Image\\PlayerUp.png");

	m_pAttackImage = RESOURCE->LoadImg(L"PlayerAttack", L"Image\\PlayerAttack.png");
	m_pDuckAttackImage = RESOURCE->LoadImg(L"PlayerDuckAttack", L"Image\\PlayerDuckAttack.png");
	m_pSubWeaponImage = RESOURCE->LoadImg(L"PlayerSubWeapon", L"Image\\PlayerSubWeapon.png");

	m_pBackFlipImage = RESOURCE->LoadImg(L"PlayerBackFlip", L"Image\\PlayerBackFlip.png");

	// 캐릭터가 왼쪽을 보고있는 이미지 파일 로드
	m_pIdleImageR = RESOURCE->LoadImg(L"PlayerIdleR", L"Image\\PlayerIdleR.png");
	m_pDuckImageR = RESOURCE->LoadImg(L"PlayerDuckR", L"Image\\PlayerDuckR.png");
	m_pMoveImageR = RESOURCE->LoadImg(L"PlayerMoveR", L"Image\\PlayerMoveR.png");
	m_pJumpImageR = RESOURCE->LoadImg(L"PlayerJumpR", L"Image\\PlayerJumpR.png");
	m_pLookUpImageR = RESOURCE->LoadImg(L"PlayerUpR", L"Image\\PlayerUpR.png");

	m_pAttackImageR = RESOURCE->LoadImg(L"PlayerAttackR", L"Image\\PlayerAttackR.png");
	m_pDuckAttackImageR = RESOURCE->LoadImg(L"PlayerDuckAttackR", L"Image\\PlayerDuckAttackR.png");
	m_pSubWeaponImageR = RESOURCE->LoadImg(L"PlayerSubWeaponR", L"Image\\PlayerSubWeaponR.png");

	m_pBackFlipImageR = RESOURCE->LoadImg(L"PlayerBackFlipR", L"Image\\PlayerBackFlipR.png");

#pragma endregion
	
#pragma region 캐릭터 애니메이션 생성

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"PlayerIdle", m_pIdleImage, Vector(0.f, 0.f), Vector(200.f, 100.f), Vector(200.f, 0.f), 0.2f, 3);
	m_pAnimator->CreateAnimation(L"PlayerDuck", m_pDuckImage, Vector(0.f, 0.f), Vector(200.f, 100.f), Vector(200.f, 0.f), 0.05f, 3, false);
	m_pAnimator->CreateAnimation(L"PlayerMove", m_pMoveImage, Vector(0.f, 0.f), Vector(200.f, 100.f), Vector(200.f, 0.f), 0.09f, 8);
	m_pAnimator->CreateAnimation(L"PlayerJump", m_pJumpImage, Vector(0.f, 0.f), Vector(200.f, 100.f), Vector(200.f, 0.f), 0.09f, 6, false);
	m_pAnimator->CreateAnimation(L"PlayerBackFlip", m_pBackFlipImage, Vector(0.f, 0.f), Vector(200.f, 100.f), Vector(200.f, 0.f), 0.09f, 4, false);
	m_pAnimator->CreateAnimation(L"PlayerLookUp", m_pLookUpImage, Vector(0.f, 0.f), Vector(200.f, 100.f), Vector(200.f, 0.f), 0.03f, 1, false);

	m_pAnimator->CreateAnimation(L"PlayerJumpDown", m_pJumpImage, Vector(1000.f, 0.f), Vector(200.f, 100.f), Vector(200.f, 0.f), 0.09f, 1, false);
	m_pAnimator->CreateAnimation(L"PlayerDucking", m_pDuckImage, Vector(400.f, 0.f), Vector(200.f, 100.f), Vector(200.f, 0.f), 0.03f, 1, false);

	m_pAnimator->CreateAnimation(L"PlayerAttack", m_pAttackImage, Vector(0.f, 0.f), Vector(200.f, 100.f), Vector(200.f, 0.f), 0.03f, 6, false);
	m_pAnimator->CreateAnimation(L"PlayerDuckAttack",m_pDuckAttackImage,Vector(0.f, 0.f), Vector(200.f, 100.f), Vector(200.f, 0.f), 0.03f, 6, false);
	m_pAnimator->CreateAnimation(L"PlayerSubWeapon",m_pSubWeaponImage, Vector(0.f, 0.f), Vector(200.f, 100.f), Vector(200.f, 0.f), 0.03f, 6, false);

	// ============ 반대방향 애니메이션 ================
	m_pAnimator->CreateAnimation(L"PlayerIdleR", m_pIdleImageR, Vector(0.f, 0.f), Vector(200.f, 100.f), Vector(200.f, 0.f), 0.2f, 3);
	m_pAnimator->CreateAnimation(L"PlayerDuckR", m_pDuckImageR, Vector(0.f, 0.f), Vector(200.f, 100.f), Vector(200.f, 0.f), 0.05f, 3, false);
	m_pAnimator->CreateAnimation(L"PlayerMoveR", m_pMoveImageR, Vector(0.f, 0.f), Vector(200.f, 100.f), Vector(200.f, 0.f), 0.09f, 8);
	m_pAnimator->CreateAnimation(L"PlayerJumpR", m_pJumpImageR, Vector(0.f, 0.f), Vector(200.f, 100.f), Vector(200.f, 0.f), 0.09f, 6, false);
	m_pAnimator->CreateAnimation(L"PlayerBackFlipR", m_pBackFlipImageR, Vector(0.f, 0.f), Vector(200.f, 100.f), Vector(200.f, 0.f), 0.09f, 4, false);
	m_pAnimator->CreateAnimation(L"PlayerLookUpR", m_pLookUpImageR, Vector(0.f, 0.f), Vector(200.f, 100.f), Vector(200.f, 0.f), 0.03f, 1, false);

	m_pAnimator->CreateAnimation(L"PlayerDuckingR", m_pDuckImageR, Vector(400.f, 0.f), Vector(200.f, 100.f), Vector(200.f, 0.f), 0.03f, 1, false);
	m_pAnimator->CreateAnimation(L"PlayerJumpDownR", m_pJumpImageR, Vector(1000.f, 0.f), Vector(200.f, 100.f), Vector(200.f, 0.f), 0.09f, 1, false);

	m_pAnimator->CreateAnimation(L"PlayerAttackR", m_pAttackImageR, Vector(0.f, 0.f), Vector(200.f, 100.f), Vector(200.f, 0.f), 0.03f, 6, false);
	m_pAnimator->CreateAnimation(L"PlayerDuckAttackR", m_pDuckAttackImageR, Vector(0.f, 0.f), Vector(200.f, 100.f), Vector(200.f, 0.f), 0.03f, 6, false);
	m_pAnimator->CreateAnimation(L"PlayerSubWeaponR", m_pSubWeaponImageR, Vector(0.f, 0.f), Vector(200.f, 100.f), Vector(200.f, 0.f), 0.03f, 6, false);

#pragma endregion

	m_pAnimator->Play(L"PlayerIdle", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(46, 91), Vector(0, -5));
}

void CPlayer::Update()
{
	m_bIsMove = false;
	m_bDuck = false;
	m_bLookup = false;

	if (BUTTONDOWN('Z'))
	{
		m_bAttack = true;
	}

	if (BUTTONDOWN('X'))
	{
		m_bJump = true;
	}

	if (m_bIsMove)
	{
		if (m_bJump)
		{
			if (m_bReverse)
			{
				if (m_vecPos.x > 30)
				{
					m_vecPos.x -= m_fSpeed * DT;
				}
				m_vecMoveDir.x = -1;
				m_bReverse = true;
			}
			else
			{
				if (m_vecPos.x < (1024 * 2) - 30)
				{
					m_vecPos.x += m_fSpeed * DT;
				}
				m_vecMoveDir.x = +1;
				m_bReverse = false;
			}
		}
	}

	if (BUTTONSTAY(VK_UP))
	{
		m_bLookup = true;
	}
	else if (BUTTONSTAY(VK_DOWN))
	{
		if (!m_bJump)
		{
			m_fDuckTime += DT;
			m_bDuck = true;
			if (BUTTONSTAY(VK_LEFT))
			{
				m_bReverse = true;
			}
			else if (BUTTONSTAY(VK_RIGHT))
			{
				m_bReverse = false;
			}
		}
	}
	else
	{
		m_vecMoveDir.y = 0;
	}

	if ((!m_bDuck && !m_bAttack) || (m_bAttack && m_bJump))
	{
		if (BUTTONSTAY(VK_LEFT))
		{
			if (m_vecPos.x > 30)
			{
				m_vecPos.x -= m_fSpeed * DT;
			}
			m_bReverse = true;
			m_bIsMove = true;
			if (!m_bAttack)
			{
				m_vecMoveDir.x = -1;
			}
		}
		else if (BUTTONSTAY(VK_RIGHT))
		{

			if (m_vecPos.x < (1024 * 2) - 30)
			{
				m_vecPos.x += m_fSpeed * DT;
			}
			m_bIsMove = true;
			m_bReverse = false;
			if (!m_bAttack)
			{
				m_vecMoveDir.x = +1;
			}
		}
		else
		{
			m_vecMoveDir.x = 0;
		}
	}

	if (m_bJump)
	{
		m_fJumpTime += DT;

		if (BUTTONDOWN('X') && m_fJumpTime > 0.15)
		{
			m_bBackFlip = true;
		}

		if (m_fJumpTime <= 0.4)
		{
			m_vecPos.y -= m_fSpeed * DT*2;
		}
		else if(m_fJumpTime > 0.4 && m_fJumpTime <= 0.8)
		{
			m_vecPos.y += m_fSpeed * DT*2;
			if (m_bBackFlip)
			{
				if (m_bReverse)
				{
					m_vecPos.x += DT * 370;
				}
				else
				{
					m_vecPos.x -= DT * 370;
				}
			}
		}
		else
		{
			m_fJumpTime = 0;
			m_bJump = false;
			m_bBackFlip = false;
			m_bAttackinBackFlip = false;
		}
	}

	if (BUTTONUP(VK_DOWN))
	{
		m_fDuckTime = 0;
	}

	if (m_bAttack)
	{
		m_fAttackTime += DT;
		if (m_fAttackTime >= 0.3)
		{
			m_bAttack = false;
			m_fAttackTime = 0;
		}
	}

	AnimatorUpdate();
}

void CPlayer::Render()
{
}

void CPlayer::Release()
{
}

void CPlayer::AnimatorUpdate()
{
	wstring str = L"Player";

	if (m_bJump)
	{
		str = L"PlayerJump";

		if (m_fJumpTime >= 0.4f)
		{
			str += L"Down";
		}
	}
	else
	{
		if (m_bIsMove)
		{
			str += L"Move";
		}
		else if (m_bDuck)
		{
			if (m_fDuckTime >= 0.04f)
			{
				str += L"Ducking";
			}
			else
			{
				str += L"Duck";
			}
		}
		else
		{
			if (m_bLookup)
			{
				str += L"LookUp";
			}
			else
			{
				str += L"Idle";
			}
		}
	}

	if (m_bBackFlip)
	{
		if (m_bAttack)
		{
			m_bAttackinBackFlip = true;
			str = L"PlayerJumpDown";
		}
		else if(!m_bAttackinBackFlip)
		{
			str = L"PlayerBackFlip";
		}
		else
		{
			str = L"PlayerJumpDown";
		}
	}
	
	if (m_bAttack)
	{
		if (m_bDuck)
		{
			str = L"PlayerDuckAttack";
		}
		else if (m_bLookup)
		{
			str = L"PlayerSubWeapon";
		}
		else
		{
			str = L"PlayerAttack";
		}
	}

	if (m_bReverse)
	{
		str += L"R";
	}

	m_pAnimator->Play(str, false);
}

void CPlayer::CreateMissile()
{
	Logger::Debug(L"미사일 생성");

	/*Vector MissilePos(m_vecPos.x - 30, m_vecPos.y - 20);
	CMissile* pMissile = new CMissile();
	pMissile->SetPos(MissilePos);
	pMissile->SetDir(Vector(1, 0));
	ADDOBJECT(pMissile);*/
}

void CPlayer::OnCollisionEnter(CCollider* pOtherCollider)
{

}

void CPlayer::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"Tile")
	{
		
	}
}

void CPlayer::OnCollisionExit(CCollider* pOtherCollider)
{
}
