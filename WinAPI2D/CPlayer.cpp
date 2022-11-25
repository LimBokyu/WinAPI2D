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

#include "CWhip.h"
#include "CHeart.h"
#include "CBigHeart.h"
#include "CDagger.h"
#include "CAxe.h"

#define MAXREST 99

CPlayer::CPlayer()
{
	m_vecPos = Vector(0, 0);
	m_vecScale = Vector(46, 91);
	m_layer = Layer::Player;
	pItem = PlayerITEM::None;
	m_strName = L"Player";

	m_Life = 94;
	// ㄴ 체력 : 최초 94 이렇게 애매한 점수인 이유는
	//          체력바 이미지의 길이가 94여서....

	m_Score = 0;
	// ㄴ 점수 : 적을 공격해서 죽였을 경우 해당
	//          해당 적을 죽이기 까지 필요한 공격 x100 점 흭득

	m_Heart = 10;
	// ㄴ 하트 : 아이템 사용에 필요한 코스트
	//			초기 시작시 10개를 들고 시작한다 

	m_Credit = 500;
	// ㄴ 크레딧 : 주운 돈 만큼 늘어남

#pragma region 이미지용 포인터 초기화

	m_pIdleImage = nullptr;
	m_pDuckImage = nullptr;
	m_pMoveImage = nullptr;
	m_pJumpImage = nullptr;

	m_pAttackImage = nullptr;
	m_pDuckAttackImage = nullptr;
	m_pDuckAttackingImage = nullptr;

	m_pIdleImageR = nullptr;
	m_pDuckImageR = nullptr;
	m_pMoveImageR = nullptr;
	m_pJumpImageR = nullptr;

	m_pAttackImageR = nullptr;
	m_pDuckAttackImageR = nullptr;
	m_pDuckAttackingImageR = nullptr;

	m_pBackFlipImage = nullptr;
	m_pBackFlipImageR = nullptr;

	m_pLookUpImage = nullptr;
	m_pLookUpImageR = nullptr;

	m_pSubWeaponImage = nullptr;
	m_pSubWeaponImageR = nullptr;

	m_pStairUpMove = nullptr;
	m_pStairUpIdle = nullptr;
	m_pStairDownMove = nullptr;
	m_pStairDownIdle = nullptr;
	m_pStairUpMoving = nullptr;
	m_pStairDownMoving = nullptr;

	m_pStairUpMoveR = nullptr;
	m_pStairUpIdleR = nullptr;
	m_pStairDownMoveR = nullptr;
	m_pStairDownIdleR = nullptr;
	m_pStairUpMovingR = nullptr;
	m_pStairDownMovingR = nullptr;

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
	m_bCommandBlock = false;
	m_bAttacking = false;
	m_bTriggerOnce = false;
	m_bFalling = false;
	m_bStairCollider = false;

	m_bStop = false;
	m_bChangedItem = false;
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{

#pragma region 캐릭터 이미지 로드

	// 캐릭터가 오른쪽을 보고있는 이미지 파일 로드
	m_pIdleImage	= RESOURCE->LoadImg(L"PlayerIdle",	 L"Image\\Player\\PlayerIdle.png");
	m_pDuckImage	= RESOURCE->LoadImg(L"PlayerDuck",	 L"Image\\Player\\PlayerDuck.png");
	m_pMoveImage	= RESOURCE->LoadImg(L"PlayerMove",	 L"Image\\Player\\PlayerMove.png");
	m_pJumpImage	= RESOURCE->LoadImg(L"PlayerJump",	 L"Image\\Player\\PlayerJump.png");
	m_pLookUpImage	= RESOURCE->LoadImg(L"PlayerUp",	 L"Image\\Player\\PlayerUp.png");

	m_pStairUpIdle = RESOURCE->LoadImg(L"PlayerUpStairIdle", L"Image\\Player\\PlayerUpStairIdle.png");
	m_pStairUpMove = RESOURCE->LoadImg(L"PlayerUpStairMove", L"Image\\Player\\PlayerUpStairMove.png");
	m_pStairUpMoving = RESOURCE->LoadImg(L"PlayerUpStairMoveing", L"Image\\Player\\PlayerUpStairMoveing.png");

	m_pAttackImage		 = RESOURCE->LoadImg(L"PlayerAttack",		 L"Image\\Player\\PlayerAttack.png");
	m_pDuckAttackImage	 = RESOURCE->LoadImg(L"PlayerDuckAttack",	 L"Image\\Player\\PlayerDuckAttack.png");
	m_pSubWeaponImage	 = RESOURCE->LoadImg(L"PlayerSubWeapon",	 L"Image\\Player\\PlayerSubWeapon.png");
	m_pAttackingImage    = RESOURCE->LoadImg(L"PlayerAttacking",     L"Image\\Player\\PlayerAttacking.png");
	m_pDuckAttackingImage = RESOURCE->LoadImg(L"DuckAttacking",      L"Image\\Player\\PlayerDuckAttacking.png");

	m_pBackFlipImage	 = RESOURCE->LoadImg(L"PlayerBackFlip",		 L"Image\\Player\\PlayerBackFlip.png");

	// 캐릭터가 왼쪽을 보고있는 이미지 파일 로드
	m_pIdleImageR	= RESOURCE->LoadImg(L"PlayerIdleR", L"Image\\Player\\PlayerIdleR.png");
	m_pDuckImageR	= RESOURCE->LoadImg(L"PlayerDuckR", L"Image\\Player\\PlayerDuckR.png");
	m_pMoveImageR	= RESOURCE->LoadImg(L"PlayerMoveR", L"Image\\Player\\PlayerMoveR.png");
	m_pJumpImageR	= RESOURCE->LoadImg(L"PlayerJumpR", L"Image\\Player\\PlayerJumpR.png");
	m_pLookUpImageR = RESOURCE->LoadImg(L"PlayerUpR",	L"Image\\Player\\PlayerUpR.png");

	m_pStairUpIdleR = RESOURCE->LoadImg(L"PlayerUpStairIdleR", L"Image\\Player\\PlayerUpStairIdleR.png");
	m_pStairUpMoveR = RESOURCE->LoadImg(L"PlayerUpStairMoveR", L"Image\\Player\\PlayerUpStairMoveR.png");
	m_pStairUpMovingR = RESOURCE->LoadImg(L"PlayerUpStairMoveingR", L"Image\\Player\\PlayerUpStairMoveingR.png");

	m_pAttackImageR		= RESOURCE->LoadImg(L"PlayerAttackR",	  L"Image\\Player\\PlayerAttackR.png");
	m_pDuckAttackImageR = RESOURCE->LoadImg(L"PlayerDuckAttackR", L"Image\\Player\\PlayerDuckAttackR.png");
	m_pSubWeaponImageR  = RESOURCE->LoadImg(L"PlayerSubWeaponR",  L"Image\\Player\\PlayerSubWeaponR.png");
	m_pAttackingImageR  = RESOURCE->LoadImg(L"PlayerAttackingR",  L"Image\\Player\\PlayerAttackingR.png");
	m_pDuckAttackingImageR = RESOURCE->LoadImg(L"DuckAttackingR", L"Image\\Player\\PlayerDuckAttackingR.png");


	m_pBackFlipImageR   = RESOURCE->LoadImg(L"PlayerBackFlipR",	  L"Image\\Player\\PlayerBackFlipR.png");


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
	m_pAnimator->CreateAnimation(L"PlayerSubWeapon",m_pSubWeaponImage, Vector(0.f, 0.f), Vector(200.f, 100.f), Vector(200.f, 0.f), 0.04f, 6, false);
	m_pAnimator->CreateAnimation(L"PlayerAttacking", m_pAttackingImage, Vector(0,0), Vector(200.f, 100.f), Vector(200.f, 0.f), 1, 1, false);
	m_pAnimator->CreateAnimation(L"PlayerDuckAttacking",m_pDuckAttackingImage, Vector(0.f, 0.f), Vector(200.f, 100.f), Vector(200.f, 0.f),1, 1, false);

	m_pAnimator->CreateAnimation(L"PlayerUpStairIdle", m_pStairUpIdle, Vector(0, 0), Vector(200, 100), Vector(200, 0), 1, 1, false);
	m_pAnimator->CreateAnimation(L"PlayerUpStairMove", m_pStairUpMove, Vector(0, 0), Vector(200, 100), Vector(200, 0), 0.1f, 3, false);
	m_pAnimator->CreateAnimation(L"PlayerUpStairMoveing", m_pStairUpMoving, Vector(0, 0), Vector(200, 100), Vector(200, 0), 0.1f, 6, false);

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
	m_pAnimator->CreateAnimation(L"PlayerSubWeaponR", m_pSubWeaponImageR, Vector(0.f, 0.f), Vector(200.f, 100.f), Vector(200.f, 0.f), 0.04f, 6, false);
	m_pAnimator->CreateAnimation(L"PlayerAttackingR", m_pAttackingImageR, Vector(0, 0), Vector(200.f, 100.f), Vector(200.f, 0.f), 1, 1, false);
	m_pAnimator->CreateAnimation(L"PlayerDuckAttackingR", m_pDuckAttackingImageR, Vector(0.f, 0.f), Vector(200.f, 100.f), Vector(200.f, 0.f), 1, 1, false);

	m_pAnimator->CreateAnimation(L"PlayerUpStairIdleR", m_pStairUpIdleR, Vector(0, 0), Vector(200, 100), Vector(200, 0), 1, 1, false);
	m_pAnimator->CreateAnimation(L"PlayerUpStairMoveR", m_pStairUpMoveR, Vector(0, 0), Vector(200, 100), Vector(200, 0), 0.1f, 3, false);
	m_pAnimator->CreateAnimation(L"PlayerUpStairMoveingR", m_pStairUpMovingR, Vector(0, 0), Vector(200, 100), Vector(200, 0), 0.1f, 6, false);


#pragma endregion

	m_pAnimator->Play(L"PlayerIdle", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(46, 91), Vector(0, -5));
}


void CPlayer::Update()
{
	if (!m_bStop)
	{
		m_vecPos.y += (m_fVelocity - m_fJumpVel) * DT;
		m_bIsMove = false;
		m_bLookup = false;

		if (m_bChangedItem)
		{
			m_fItemTimer += DT;
			if (m_fItemTimer > 1)
			{
				m_bChangedItem = false;
				m_fItemTimer = 0;
			}
		}

		if (m_bJump)
		{
			m_fVelTimer += DT;
			if (m_fVelTimer >= 0.03f && m_fJumpVel > 0)
			{
				m_fJumpVel -= 30;
				m_fVelTimer = 0;
			}
		}

		if (!m_bAttacking)
		{
			m_bDuck = false;
		}

		if (m_Heart == 0)
		{
			Logger::Debug(L"하트를 다씀");
		}

		if (BUTTONDOWN('W'))
		{
			m_Credit += 100;
		}

		if (BUTTONDOWN('P'))
		{
			CreateItem();
		}

		if (BUTTONDOWN('O'))
		{
			CBigHeart* bHeart = new CBigHeart();
			bHeart->SetPos(m_vecPos.x + 200, m_vecPos.y - 100);
			ADDOBJECT(bHeart);
		}

		if (!m_bCommandBlock)
		{

			if (BUTTONDOWN('Q'))
			{
				pItem = PlayerITEM::Dagger;
			}

			if (BUTTONDOWN('Z'))		// 공격
			{
				if (!m_bAttack)
				{
					m_bTriggerOnce = true;
					m_bAttack = true;
					m_Score += 10;
				}
			}

			if (BUTTONDOWN('X'))		// 점프
			{
				m_bJump = true;
				m_fJumpVel = 800;
			}

			if (BUTTONSTAY(VK_UP))
			{
				m_bLookup = true;
				if (BUTTONDOWN('Z'))
				{
					SetHeart(GetHeart() - 1);
				}
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

			if (BUTTONUP(VK_DOWN))
			{
				m_fDuckTime = 0;
			}
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

		if (m_bJump)
		{
			m_fJumpTime += DT;

			if (BUTTONDOWN('X') && m_fJumpTime > 0.15 && m_fJumpTime <0.4)
			{
				m_bBackFlip = true;
			}
			else if (m_fJumpTime > 0.4 && m_fJumpTime <= 0.8)
			{
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
		}


		if (m_bLookup && m_bAttack)
		{
			m_fAttackTime += DT;
			if (m_fAttackTime > 0.2f)
			{
				m_bAttack = false;
				m_bCommandBlock = false;
				m_fAttackTime = 0;
			}
		}
		else if (m_bAttack)
		{
			m_fAttackTime += DT;
			if (m_fAttackTime > 0.15f && m_fAttackTime < 0.3)
			{
				WhipAttack();
				m_bAttacking = true;
				m_bCommandBlock = true;
			}
			if (m_fAttackTime >= 0.3)
			{
				m_bAttacking = false;
				m_bAttack = false;
				m_bCommandBlock = false;
				m_fAttackTime = 0;
			}
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
			m_bFalling = true;
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

	if(m_bAttacking && !m_bLookup)
	{
		str += L"ing";
	}

	if (m_bOnStair)
	{
		str = L"PlayerUpStairIdle";
	}

	if (m_bReverse)
	{
		str += L"R";
	}

	m_pAnimator->Play(str, false);
}

void CPlayer::WhipAttack()
{
	if (m_bTriggerOnce)
	{
		Logger::Debug(L"플레이어의 공격");
		CWhip* attack = new CWhip();
		attack->SetPlayer(this);
		ADDOBJECT(attack);
		m_bTriggerOnce = false;
	}
}

void CPlayer::CreateItem()
{
	CHeart* heart = new CHeart();
	heart->SetPos(m_vecPos.x + 100, m_vecPos.y);
	ADDOBJECT(heart);
}

void CPlayer::ItemCrash()
{
	
}

void CPlayer::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"Heart")
	{
		if (m_Heart == 99)
		{

		}
		else
		{
			m_Heart++;
		}
	}
	else if (pOtherCollider->GetObjName() == L"BigHeart")
	{
		if ((m_Heart + 5) > 99)
		{
			m_Heart = 99;
		}
		else
		{
			m_Heart += 5;
		}
	}
	else if (pOtherCollider->GetObjName() == L"Obstacle")
	{
		if (m_fJumpVel <= 0)
		{
			PlayerOnGround();
		}
	}
	
	if (!m_bChangedItem)
	{
		if (pOtherCollider->GetObjName() == L"Dagger")
		{
			if (pItem == PlayerITEM::None)
			{
				pItem = PlayerITEM::Dagger;
			}
			else
			{
				SwitchItem();
				m_bChangedItem = true;
				pItem = PlayerITEM::Dagger;
			}
		}
		else if (pOtherCollider->GetObjName() == L"Axe")
		{
			if (pItem == PlayerITEM::None)
			{
				pItem = PlayerITEM::Axe;
			}
			else
			{
				SwitchItem();
				m_bChangedItem = true;
				pItem = PlayerITEM::Axe;
			}
		}
	}


}

void CPlayer::OnCollisionStay(CCollider* pOtherCollider)
{
	
}

void CPlayer::OnCollisionExit(CCollider* pOtherCollider)
{
}

PlayerITEM CPlayer::GetItem()
{
	return pItem;
}

void CPlayer::SetItem(PlayerITEM item)
{
	pItem = item;
}

int CPlayer::GetHeart()
{
	return m_Heart;
}

void CPlayer::SetHeart(int heart)
{
	m_Heart = heart;
}

int CPlayer::GetCredit()
{
	return m_Credit;
}

void CPlayer::SetCredit(int credit)
{
	m_Credit = credit;
}

int CPlayer::GetRest()
{
	return m_Rest;
}

int CPlayer::GetLife()
{
	return m_Life;
}

void CPlayer::SetLife(int life)
{
	m_Life = life;
}

int CPlayer::GetScore()
{
	return m_Score;
}

void CPlayer::SetScore(int score)
{
	m_Score = score;
}

bool CPlayer::GetReverse()
{
	return m_bReverse;
}

bool CPlayer::GetDuck()
{
	return m_bDuck;
}

void CPlayer::SwitchItem()
{
	if (pItem == PlayerITEM::Dagger)
	{
		CDagger* dagger = new CDagger();
		dagger->Changed();
		dagger->SetPos(m_vecPos);
		ADDOBJECT(dagger);
	}
	else if (pItem == PlayerITEM::Axe)
	{
		CAxe* axe = new CAxe();
		axe->Changed();
		axe->SetPos(m_vecPos);
		axe->SetReverse(m_bReverse);
		ADDOBJECT(axe);
	}
}

void CPlayer::DropItem()
{
}

void CPlayer::SetStop(bool stop)
{
	m_bStop = stop;
}

void CPlayer::SwitchStop()
{
	if (m_bStop)
	{
		m_bStop = false;
	}
	else
	{
		m_bStop = true;
	}
}

void CPlayer::PlayerOnGround()
{
	m_bJump = false;
	m_bBackFlip = false;
	m_bAttackinBackFlip = false;
	m_fJumpTime = 0;
}

void CPlayer::SetStairCollider(bool index)
{
	m_bStairCollider = index;
}

