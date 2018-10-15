#include "stdafx.h"
#include "player.h"
#include "room.h"
#include "bulletSoul.h"
#include "guardianSoul.h"
#include "enchantSoul.h"
#include "zombie.h"


HRESULT player::init()
{
	// 플레이어의 오른쪽 보고 있을떄의 이미지 0부터 프레임 시작
	m_pImg = IMAGEMANAGER->addImage("player", "image/playerMotion.bmp", 855, 741, 19, 13, true, RGB(0, 64, 128));

	// 플레이어의 왼쪽 보고 있을떄의 이미지 18부터 프레임 시작
	m_pImg2 = IMAGEMANAGER->addImage("player2", "image/playerMotion2.bmp", 855, 741, 19, 13, true, RGB(0, 64, 128));

	// 칼
	m_pImg3 = IMAGEMANAGER->addImage("발뭉", "image/발뭉.bmp", 720, 48, 9, 2, true, RGB(255, 0, 255));

	// 숫자 이미지
	m_pCImg = IMAGEMANAGER->addImage("숫자", "image/숫자.bmp", 96, 40, 12, 4, true, RGB(255, 0, 255));

	// 플레이어의 동작 프레임 값
	m_nCount = 0;
	m_nRCurrFrameX = 0;
	m_nRCurrFrameY = 0;

	m_nLCurrFrameX = 18;
	m_nLCurrFrameY = 0;

	m_nNCurrFrameX = 0;
	m_nNCurrFrameY = 0;

	// 플레이어의 속성 초기화
	m_fSpeed = 6.0f; //테스팅용으로 
	m_fJumP = 20.0f;
	m_fGravity = 10.0f;
	m_fSildeP = 10.0f;
	m_fBackP = 8.0f;
	m_nSildeC = 0;
	m_nBackC = 0;
	m_nJumC = 0;
	m_nJumMC = 0;
	m_nMotionC = 0;
	m_nSkReadyC = 0;
	m_nHitC = 0;
	m_nHitDivineC = 100;
	m_nNumC = 0;
	// 플레이어의 초기 위치 값
	m_fX = 200;
	m_fY = 400;

	m_fDamageY = m_fY - 80;

	// 플레이어가 오른쪽 보고 있는 상태로 초기화
	m_bPlayerSee = 1;

	// 플레이어의 공격 모션 초기화
	m_bPlayerAttack = 0;

	// 플레이어의 점프 모션 초기화 점프는 int형식으로 주어서 2단 점프를 구현
	m_nPlayerJump = 0;
	m_bPlayerJumpDown = 0;
	m_bPlayerJumpM = 0;
	m_bPlayerJumpAttack = 0;

	// 플레이어의 앉기 모션 초기화
	m_nPlayerDown = 0;
	m_bPlayerDownAt = 0;

	// 플레이어의 백대쉬 모션 초기화
	m_bPlayerBackDash = 0;

	// 플레이어의 슬라이딩 모션 초기화
	m_bPlayerSilde = 0;

	// 플레이어의 착지 모션 초기화
	m_bPlayerStand = 0;

	// 플레이어의 스킬대기 모션 초기화
	m_bPlayerSkReady = 0;

	// 플레이어의 피격 모션 초기화
	m_bPlayerHited = 0;
	m_bDivin = 0;
	m_bDamageShow = 0;

	m_status = { 10,10,12,12,11,11,9,9, 10,10,6,6,320,320,80,80,0,84 };

	m_nGold = 0;

	m_rc = RectMakeCenter(m_fX, m_fY, (m_pImg->getFrameWidth() - 20) * 3, (m_pImg->getFrameHeight() - 20) * 3);
	m_Irc = RectMakeCenter(0, 0, 0, 0);

	m_xCameraOn = false;
	m_yCameraOn = false;

	m_bIsJump = false;

	bulletSoul* baseBSoul = new bulletSoul;
	baseBSoul->init(0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, "------", "---");

	bulletSoul* testBSoul = new bulletSoul;
	testBSoul->init(0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, "해골사수", "마법의 활을 쏜다");


	m_soulInven.vecBulletSoul.push_back(baseBSoul);
	m_soulInven.vecBulletSoul.push_back(testBSoul);
	m_soulInven.vecBulletSoul.push_back(testBSoul);


	guardianSoul* baseGSoul = new guardianSoul;
	baseGSoul->init(0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, "------", "---");

	guardianSoul* testGSoul = new guardianSoul;
	testGSoul->init(0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, "메두사 헤드", "공중에서 정지가 가능하다.");

	m_soulInven.vecGuardianSoul.push_back(baseGSoul);
	m_soulInven.vecGuardianSoul.push_back(testGSoul);
	m_soulInven.vecGuardianSoul.push_back(testGSoul);
	m_soulInven.vecGuardianSoul.push_back(baseGSoul);

	enchantSoul* baseESoul = new enchantSoul;
	baseESoul->init(0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, "------", "---");

	enchantSoul* testESoul = new enchantSoul;
	testESoul->init(0, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, "좀비", "CON +2");

	m_soulInven.vecEnchantSoul.push_back(baseESoul);
	m_soulInven.vecEnchantSoul.push_back(testESoul);


	m_soulSet.bS = baseBSoul;
	m_soulSet.gS = baseGSoul;
	m_soulSet.eS = baseESoul;






	m_bItem = 0;

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	// 중력 적용
	mapRectCollision();


	m_fY += m_fGravity;
	if (m_bPlayerHited == 1)
	{
		m_nNumC--;
	}

	// 키입력시 플레이어의 행동

	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		hitCollision(3);
	}

	// 플레이어 스킬 준비 모션
	if (KEYMANAGER->isStayKeyDown(VK_UP) && m_bPlayerAttack == 0 && m_bPlayerHited == 0)
	{
		m_bPlayerSkReady = 1;
		m_nSkReadyC++;
		if (m_bPlayerSee == 1)
		{
			m_nRCurrFrameY = 1;
			if (m_nSkReadyC < 1)
			{
				m_nRCurrFrameX = 1;
			}
		}
		else if (m_bPlayerSee == 0)
		{
			m_nLCurrFrameY = 1;
			if (m_nSkReadyC < 1)
			{
				m_nLCurrFrameX = 17;
			}
		}
	}

	// 플레이어 좌우 이동
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && m_nPlayerDown == 0 && m_bPlayerBackDash == 0 && m_bPlayerAttack == 0 && m_bPlayerHited == 0)
	{
		m_bPlayerAttack = 0;
		m_bPlayerSee = 1;
		m_bPlayerSkReady = 0;
		if (m_nPlayerJump == 0)
		{
			m_nRCurrFrameY = 3;
		}
		m_fX += m_fSpeed;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) && m_nPlayerDown == 0 && m_bPlayerBackDash == 0 && m_bPlayerAttack == 0 && m_bPlayerHited == 0)
	{
		m_nRCurrFrameX = 0;
		m_nRCurrFrameY = 0;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && m_nPlayerDown == 0 && m_bPlayerBackDash == 0 && m_bPlayerAttack == 0 && m_bPlayerHited == 0)
	{
		m_bPlayerAttack = 0;
		m_bPlayerSee = 0;
		m_bPlayerSkReady = 0;
		m_nLCurrFrameY = 3;
		m_fX -= m_fSpeed;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) && m_nPlayerDown == 0 && m_bPlayerBackDash == 0 && m_bPlayerAttack == 0 && m_bPlayerHited == 0)
	{
		m_nLCurrFrameX = 18;
		m_nLCurrFrameY = 0;
	}

	if (KEYMANAGER->isOnceKeyDownNotuch('Z'))
	{
		m_bIsJump = true;
	}



	if (KEYMANAGER->isOnceKeyUp(VK_UP) && m_bPlayerHited == 0)
	{
		m_bPlayerSkReady = 0;
		if (m_bPlayerSee == 1)
		{
			m_nRCurrFrameY = 0;
			m_nRCurrFrameX = 0;
		}
		else if (m_bPlayerSee == 0)
		{
			m_nLCurrFrameY = 0;
			m_nLCurrFrameX = 18;
		}

	}

	// 플레이어 점프
	if (KEYMANAGER->isStayKeyDown('Z') && m_bPlayerAttack == 0 && m_bPlayerHited == 0 && m_nPlayerDown == 0)
	{
		if (m_bIsJump)
		{
			if (m_bPlayerSee == 1)
			{
				if (m_nPlayerJump <= 2)
				{
					m_nJumMC++;
					if (m_nJumMC < 2)
					{
						m_nRCurrFrameX = 2;
					}
					m_bPlayerJumpM = 1;
					if (m_bPlayerJumpAttack == 0)

					{
						m_nRCurrFrameY = 6;

					}
					if (m_nPlayerJump == 0)
					{
						m_nPlayerJump = 1;
					}
					m_nJumC++;
					m_fY -= m_fJumP;

					if (m_nJumC < 30 && m_nJumC > 10)
					{
						m_fJumP = 10;
					}
					else if (m_nJumC > 30)
					{
						m_fJumP--;
						if (m_fJumP <= 0)
						{
							m_fJumP = 0;
						}
					}
				}
			}

			else if (m_bPlayerSee == 0)
			{
				if (m_nPlayerDown == 0 && m_nPlayerJump <= 2)
				{
					m_nJumMC++;
					if (m_nJumMC < 2)
					{
						m_nLCurrFrameX = 16;
					}
					m_bPlayerJumpM = 1;
					m_nLCurrFrameY = 6;
					if (m_nPlayerJump == 0)
					{
						m_nPlayerJump = 1;
					}
					m_nJumC++;
					m_fY -= m_fJumP;

					if (m_nJumC < 30 && m_nJumC > 10)
					{
						m_fJumP = 10;
					}
					else if (m_nJumC > 30)
					{
						m_fJumP--;
						if (m_fJumP <= 0)
						{
							m_fJumP = 0;
						}
					}
				}
			}
		}
	}


	//플레이어 슬라이딩
	if (KEYMANAGER->isOnceKeyDown('Z') && m_nPlayerDown == 1 && m_nPlayerJump == 0 && m_bPlayerSilde == 0)
	{
		if (m_bIsJump)
		{
			m_bPlayerSilde = 1;
			if (m_bPlayerSee == 1)
			{
				m_nRCurrFrameX = 7;
			}
			else if (m_bPlayerSee == 0)
			{
				m_nLCurrFrameX = 12;
			}
		}
	}

	// 점프 동작 초기화
	if (KEYMANAGER->isOnceKeyUp('Z') && m_nPlayerJump <= 3 && m_bPlayerHited == 0 && m_nPlayerDown == 0)
	{
		if (m_bIsJump)
		{
			if (m_bPlayerSee == 1)
			{
				m_nRCurrFrameY = 6;
				m_nRCurrFrameX = 0;
			}
			else if (m_bPlayerSee == 0)
			{
				m_nLCurrFrameY = 6;
				m_nLCurrFrameY = 18;
			}
			m_nPlayerJump++;
			m_bPlayerJumpDown = 1;
			m_bPlayerJumpM = 0;
			m_nJumC = 0;
			m_fJumP = 20.0f;
			m_nJumMC = 0;
		}
	}

	// 플레이어 공격
	if (KEYMANAGER->isOnceKeyDown('X') && m_bPlayerAttack == 0 && m_bPlayerSilde == 0 && m_bPlayerHited == 0)
	{
		if (m_nPlayerDown == 0 && m_bPlayerStand == 1 && m_bPlayerJumpM == 0)
		{
			m_bPlayerAttack = 1;
			m_bPlayerBackDash = 0;
			if (m_bPlayerSee == 1)
			{
				m_nRCurrFrameX = 0;
				m_nRCurrFrameY = 1;
				m_nNCurrFrameY = 0;
			}
			else if (m_bPlayerSee == 0)
			{
				m_nLCurrFrameX = 18;
				m_nLCurrFrameY = 1;
				m_nNCurrFrameY = 1;
			}
		}
		else if (m_nPlayerDown == 1 && m_bPlayerAttack == 0 && m_bPlayerDownAt == 0 && m_bPlayerStand == 1)
		{
			m_bPlayerDownAt = 1;
			if (m_bPlayerSee == 1)
			{
				m_nRCurrFrameX = 10;
				m_nRCurrFrameY = 11;
				m_nNCurrFrameY = 0;
			}
			else if (m_bPlayerSee == 0)
			{
				m_nLCurrFrameX = 7;
				m_nLCurrFrameY = 11;
				m_nNCurrFrameY = 1;
			}
		}
		else if (m_nPlayerJump != 0 && m_bPlayerStand == 0 && m_bPlayerJumpAttack == 0)
		{
			m_bPlayerJumpAttack = 1;
			m_nRCurrFrameY = 7;
			m_nRCurrFrameX = 4;
		}
	}

	// 플레이어 앉기
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && m_bPlayerAttack == 0)
	{
		m_nPlayerDown = 1;
		if (m_bPlayerSee == 1)
		{
			m_nRCurrFrameY = 11;
		}
		else if (m_bPlayerSee == 0)
		{
			m_nLCurrFrameY = 11;
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_DOWN) && m_bPlayerSilde == 0 && m_bPlayerDownAt == 0)
	{
		m_nPlayerDown = 2;
	}

	// 플레이어 백대쉬
	if (KEYMANAGER->isOnceKeyDown('A') && m_bPlayerBackDash == 0 && m_nPlayerDown == 0 && m_nPlayerJump == 0)
	{
		m_bPlayerBackDash = 1;
		m_bPlayerAttack = 0;
		m_nNCurrFrameX = 0;
		m_Irc = RectMakeCenter(-10, -10, 1, 1);
		if (m_bPlayerSee == 1)
		{
			m_nRCurrFrameX = 2;
			m_nRCurrFrameY = 4;
		}
		else if (m_bPlayerSee == 0)
		{
			m_nLCurrFrameX = 17;
			m_nLCurrFrameY = 4;
		}
	}


	// 플레이어가 우측 방향을 보고 있을 떄 프레임 모션 지정
	if (m_bPlayerSee == 1)
	{
		m_nCount++;
		// 플레이어 기본자세
		if (m_nRCurrFrameY == 0 && m_bPlayerStand == 1 && m_bPlayerHited == 0 && m_bPlayerJumpAttack == 0)
		{
			if (m_nCount % 20 == 0)
			{
				m_nRCurrFrameX++;
				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > 3)
				{
					m_nRCurrFrameX = 0;
					m_nCount = 0;
				}
			}
		}

		// 플레이어 이동자세
		if (m_nRCurrFrameY == 3 && m_bPlayerStand == 1)
		{
			if (m_nCount % 5 == 0)
			{
				m_nRCurrFrameX++;
				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > m_pImg->getMaxFrameX())
				{
					m_nRCurrFrameX = 3;
					m_nCount = 0;
				}
			}
		}

		// 플레이어 공격자세
		else if (m_nRCurrFrameY == 1 && m_bPlayerAttack == 1 && m_bPlayerStand == 1)
		{
			if (m_nCount % 4 == 0)
			{
				m_nRCurrFrameX++;
				if (m_nRCurrFrameX > 2)
				{
					m_bItem = 1;
					m_nNCurrFrameX++;


					if (m_nNCurrFrameX > 0 && m_nNCurrFrameX < 5)
					{
						m_Irc = RectMakeCenter(m_fX + 120, m_fY - 40, m_pImg3->getFrameWidth() * 2, m_pImg3->getFrameHeight() * 2);
					}
				}
				m_pImg->setFrameX(m_nRCurrFrameX);
				m_pImg3->setFrameX(m_nNCurrFrameX);
				if (m_nRCurrFrameX > m_pImg->getMaxFrameX() - 7)
				{
					m_nRCurrFrameX = 0;
					m_bPlayerAttack = 0;
					m_nRCurrFrameY = 0;
					m_nNCurrFrameX = 0;
					m_bItem = 0;
					m_nCount = 0;
					m_Irc = RectMakeCenter(-10, -10, 1, 1);
				}
			}
		}

		// 플레이어 점프 자세
		else if (m_nRCurrFrameY == 6 && m_bPlayerJumpM == 1 && m_bPlayerStand == 0 && m_nJumC < 30 && m_bPlayerHited == 0 && m_bPlayerJumpAttack == 0)
		{
			if (m_nCount % 5 == 0)
			{
				m_nRCurrFrameX++;
				if (m_nRCurrFrameX == 2)
				{
					m_nRCurrFrameX = 0;
				}
				m_pImg->setFrameX(m_nRCurrFrameX);
			}
		}

		else if (m_nRCurrFrameY == 7 && m_bPlayerHited == 0 && m_bPlayerJumpAttack == 1 && m_bPlayerStand == 0)
		{
			if (m_nCount % 6 == 0)
			{
				m_nRCurrFrameX++;
				if (m_nRCurrFrameX > 6)
				{
					m_bItem = 1;
					m_nNCurrFrameX++;
					if (m_nNCurrFrameX > 0 && m_nNCurrFrameX < 5)
					{
						m_Irc = RectMakeCenter(m_fX + 120, m_fY - 40, m_pImg3->getFrameWidth() * 2, m_pImg3->getFrameHeight() * 2);
					}
				}
				m_pImg->setFrameX(m_nRCurrFrameX);
				m_pImg3->setFrameX(m_nNCurrFrameX);
				if (m_nRCurrFrameX > 8)
				{
					m_bPlayerJumpAttack = 0;
					m_nRCurrFrameX = 0;
					m_nNCurrFrameX = 0;
					m_Irc = RectMakeCenter(-10, -10, 1, 1);
					m_nCount = 0;
					m_bItem = 0;
					//m_nRCurrFrameY = 6;
				}
			}
		}

		// 플레이어 떨어지는 자세
		else if (m_bPlayerStand == 0 && m_bPlayerJumpM == 0 || m_nJumC >= 30 && m_bPlayerHited == 0 && m_bPlayerJumpAttack == 0)
		{
			m_nRCurrFrameY = 6;
			m_nRCurrFrameX = 7;
			if (m_nCount % 5 == 0)
			{
				m_nRCurrFrameX++;
				if (m_nRCurrFrameX == 8)
				{
					m_nRCurrFrameX = 7;
				}
			}
		}

		// 플레이어 앉기 자세
		else if (m_nRCurrFrameY == 11 && m_nPlayerDown == 1 && m_bPlayerSilde == 0 && m_bPlayerDownAt == 0)
		{
			if (m_nCount % 10 == 0)
			{
				m_nRCurrFrameX++;
				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > 3)
				{
					m_nRCurrFrameX = 3;
					m_nRCurrFrameY = 11;
					m_nCount = 0;
				}
			}
		}
		else if (m_nRCurrFrameY == 11 && m_nPlayerDown == 2)
		{
			if (m_nCount % 5 == 0)
			{
				m_nRCurrFrameX++;
				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > 5)
				{
					m_nPlayerDown = 0;
					m_nCount = 0;
					m_nRCurrFrameX = 0;
					m_nRCurrFrameY = 0;
				}
			}
		}

		// 플레이어 앉아 공격 자세
		else if (m_bPlayerDownAt == 1 && m_nRCurrFrameY == 11)
		{
			if (m_nCount % 5 == 0)
			{
				m_nMotionC++;
				if (m_nMotionC < 3 || m_nMotionC > 5)
				{
					m_nRCurrFrameX++;
				}

				if (m_nRCurrFrameX < 14)
				{
					m_bItem = 1;
					m_nNCurrFrameX++;
					if (m_nNCurrFrameX > 3 && m_nNCurrFrameX < 5)
					{
						m_Irc = RectMakeCenter(m_fX + 120, m_fY - 10, m_pImg3->getFrameWidth() * 2, m_pImg3->getFrameHeight() * 2);
					}
				}

				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > 14)
				{
					m_nCount = 0;
					m_nRCurrFrameX = 10;
					m_nNCurrFrameX = 0;
					m_bPlayerDownAt = 0;
					m_nPlayerDown = 2;
					m_nMotionC = 0;
					m_bItem = 0;
					m_Irc = RectMakeCenter(-10, -10, 1, 1);
				}
			}
		}

		// 플레이어 슬라이딩 자세
		else if (m_nRCurrFrameY == 11 && m_bPlayerSilde == 1 && m_nPlayerDown == 1)
		{
			if (m_nSildeC > 5)
			{
				m_nRCurrFrameX++;
				m_nSildeC = 0;
			}
			else
			{
				m_nSildeC++;
			}

			if (m_nRCurrFrameX <= 9)
			{
				m_fX += m_fSildeP;
			}

			if (m_nCount % 10 == 0)
			{
				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > 9)
				{
					m_nPlayerDown = 2;
					//m_nPlayerJump = 1;
					m_bPlayerSilde = 0;
					m_nRCurrFrameX = 9;
					m_nRCurrFrameY = 11;
					m_fSildeP = 10.0f;
					m_nSildeC = 0;
				}
			}
		}

		// 플레이어 백대쉬 자세
		else if (m_nRCurrFrameY == 4 && m_bPlayerBackDash == 1)
		{
			m_fX -= m_fBackP;
			if (m_nCount % 5 == 0)
			{
				m_nRCurrFrameX++;
				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > 4)
				{
					m_bPlayerBackDash = 0;
					m_nRCurrFrameX = 0;
					m_nRCurrFrameY = 0;
				}
			}
		}
		// 플레이어 스킬모션 대기 자세
		else if (m_bPlayerSkReady == 1 && m_nRCurrFrameY != 3)
		{
			if (m_nCount % 5 == 0)
			{
				if (m_nRCurrFrameX < 3)
				{
					m_nRCurrFrameX++;
					m_pImg->setFrameX(m_nRCurrFrameX);
				}
			}
		}
	}


	// 플레이어가 좌측 방향을 보고 있을 떄 프레임 모션 지정
	else if (m_bPlayerSee == 0)
	{
		m_nCount++;

		// 플레이어 왼쪽 기본자세
		if (m_nLCurrFrameY == 0 && m_bPlayerStand == 1 && m_bPlayerHited == 0)
		{
			if (m_nCount % 20 == 0)
			{
				m_nLCurrFrameX--;
				m_pImg2->setFrameX(m_nLCurrFrameX);
				if (m_nLCurrFrameX < 15)
				{
					m_nLCurrFrameX = 18;
				}
			}
		}

		// 플레이어 왼쪽 이동자세
		else if (m_nLCurrFrameY == 3 && m_bPlayerStand == 1)
		{
			if (m_nCount % 5 == 0)
			{
				m_nLCurrFrameX--;
				m_pImg2->setFrameX(m_nLCurrFrameX);
				if (m_nLCurrFrameX < 0)
				{
					m_nLCurrFrameX = 14;
				}
			}
		}

		// 플레이어 왼쪽 공격자세
		else if (m_nLCurrFrameY == 1 && m_bPlayerAttack == 1 && m_bPlayerStand == 1)
		{
			if (m_nCount % 4 == 0)
			{
				if (m_nLCurrFrameX < 17)
				{
					m_bItem = 1;
					m_nNCurrFrameX++;
					if (m_nNCurrFrameX > 0 && m_nNCurrFrameX < 5)
					{
						m_Irc = RectMakeCenter(m_fX - 110, m_fY - 40, m_pImg3->getFrameWidth() * 2, m_pImg3->getFrameHeight() * 2);
					}
				}
				m_nLCurrFrameX--;
				m_pImg3->setFrameX(m_nRCurrFrameX);
				m_pImg2->setFrameX(m_nLCurrFrameX);
				if (m_nLCurrFrameX < 7)
				{
					m_nLCurrFrameX = 18;
					m_bPlayerAttack = 0;
					m_nLCurrFrameY = 0;
					m_nNCurrFrameX = 0;
					m_Irc = RectMakeCenter(-10, -10, 1, 1);
				}
			}
		}

		// 플레이어 점프자세

		else if (m_nLCurrFrameY == 6 && m_bPlayerJumpM == 1 && m_bPlayerStand == 0 && m_nJumC < 30)
		{
			if (m_nCount % 5 == 0)
			{
				m_nLCurrFrameX--;
				if (m_nRCurrFrameX == 16)
				{
					m_nLCurrFrameX = 17;
				}
				m_pImg2->setFrameX(m_nLCurrFrameX);
			}
		}

		else if (m_nLCurrFrameY == 6 && m_bPlayerJumpAttack == 1)
		{
			if (m_nCount % 5 == 0)
			{
				m_nLCurrFrameX--;
				m_pImg2->setFrameX(m_nLCurrFrameX);
				if (m_nLCurrFrameX < 9)
				{
					m_bPlayerJumpAttack = 0;
					m_nLCurrFrameX = 18;
				}
			}

		}

		// 플레이어 떨어지는 자세
		else if (m_bPlayerStand == 0 && m_bPlayerJumpM == 0 || m_nJumC >= 30)
		{
			m_nLCurrFrameY = 6;
			m_nLCurrFrameX = 11;
			if (m_nCount % 5 == 0)
			{
				m_nLCurrFrameX--;
				if (m_nLCurrFrameX == 10)
				{
					m_nLCurrFrameX = 11;
				}
			}
		}

		// 플레이어 왼쪽 앉기 자세
		else if (m_nLCurrFrameY == 11 && m_nPlayerDown == 1 && m_bPlayerSilde == 0 && m_bPlayerDownAt == 0)
		{
			if (m_nCount % 10 == 0)
			{
				m_nLCurrFrameX--;
				m_pImg2->setFrameX(m_nLCurrFrameX);
				if (m_nLCurrFrameX < 15)
				{
					m_nLCurrFrameX = 15;
					m_nLCurrFrameY = 11;
					m_nCount = 0;
				}
			}
		}

		else if (m_nLCurrFrameY == 11 && m_nPlayerDown == 2)
		{
			if (m_nCount % 5 == 0)
			{
				m_nLCurrFrameX--;
				m_pImg2->setFrameX(m_nLCurrFrameX);
				if (m_nLCurrFrameX < 13)
				{
					m_nLCurrFrameX = 18;
					m_nLCurrFrameY = 0;
					m_nPlayerDown = 0;
					m_nCount = 0;
				}
			}
		}


		// 플레이어 앉아 공격 자세
		else if (m_bPlayerDownAt == 1 && m_nLCurrFrameY == 11)
		{
			if (m_nCount % 5 == 0)
			{
				m_nMotionC++;
				if (m_nMotionC < 3 || m_nMotionC > 5)
				{
					m_nLCurrFrameX--;
				}

				if (m_nLCurrFrameX > 4)
				{
					m_bItem = 1;
					m_nNCurrFrameX++;
					if (m_nNCurrFrameX > 3 && m_nNCurrFrameX < 5)
					{
						m_Irc = RectMakeCenter(m_fX - 110, m_fY - 10, m_pImg3->getFrameWidth() * 2, m_pImg3->getFrameHeight() * 2);
					}
				}
				m_pImg2->setFrameX(m_nLCurrFrameX);
				if (m_nLCurrFrameX < 4)
				{
					m_nCount = 0;
					m_nLCurrFrameX = 8;
					m_nNCurrFrameX = 0;
					m_bPlayerDownAt = 0;
					m_nPlayerDown = 2;
					m_nMotionC = 0;
					m_bItem = 0;
					m_Irc = RectMakeCenter(-10, -10, 1, 1);
				}
			}
		}

		// 플레이어 슬라이딩 자세
		else if (m_nLCurrFrameY == 11 && m_bPlayerSilde == 1 && m_nPlayerDown == 1)
		{
			if (m_nSildeC > 5)
			{
				m_nLCurrFrameX--;
				m_nSildeC = 0;
			}
			else
			{
				m_nSildeC++;
			}
			if (m_nLCurrFrameX > 9)
			{
				m_fX -= m_fSildeP;
			}
			if (m_nCount % 10 == 0)
			{
				m_pImg2->setFrameX(m_nLCurrFrameX);
				if (m_nLCurrFrameX < 9)
				{
					m_nLCurrFrameX = 9;
					m_nLCurrFrameY = 11;
					m_nPlayerDown = 2;
					m_bPlayerSilde = 0;
					m_fSildeP = 10.0f;
					m_nSildeC = 0;
				}
			}
		}

		// 플레이어 백대쉬 자세
		else if (m_nLCurrFrameY == 4 && m_bPlayerBackDash == 1)
		{
			m_fX += m_fBackP;
			if (m_nCount % 5 == 0)
			{
				m_nLCurrFrameX--;
				m_pImg2->setFrameX(m_nLCurrFrameX);
				if (m_nLCurrFrameX < 14)
				{
					m_bPlayerBackDash = 0;
					m_nLCurrFrameX = 18;
					m_nLCurrFrameY = 0;
				}
			}
		}
		// 플레이어 스킬 대기 자세
		else if (m_bPlayerSkReady == 1 && m_nLCurrFrameY != 3)
		{
			if (m_nCount % 5 == 0)
			{
				if (m_nLCurrFrameX > 15)
				{
					m_nLCurrFrameX--;
					m_pImg2->setFrameX(m_nLCurrFrameX);
				}
			}
		}
	}

	mapchackCollision();
	mapMove();
	hitMosion();
	ShowDamage();
	FallDown();


	m_rc = RectMakeCenter(m_fX, m_fY, (m_pImg->getFrameWidth() * 3) / 2, (m_pImg->getFrameHeight() * 3) / 2);


}

void player::render(HDC hdc)
{
	if (m_pImg)
	{
		//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
		// 플레이어가 오른쪽을 보고 있을때 이미지 랜더
		if (m_bPlayerSee == 1)
		{
			m_pImg->frameRender(hdc, m_fX - (m_pImg->getFrameWidth() * 3) / 2, m_fY - (m_pImg->getFrameHeight() * 3) / 2 - 10, m_nRCurrFrameX, m_nRCurrFrameY, 3);
			if (m_bItem)
			{
				if (m_bPlayerAttack)
				{
					m_pImg3->frameRender(hdc, m_fX - 30, m_fY - 70, m_nNCurrFrameX, m_nNCurrFrameY, 3);
				}
				else if (m_bPlayerDownAt)
				{
					m_pImg3->frameRender(hdc, m_fX - 30, m_fY - 35, m_nNCurrFrameX, m_nNCurrFrameY, 3);
				}
				else if (m_bPlayerJumpAttack)
				{
					m_pImg3->frameRender(hdc, m_fX - 30, m_fY - 35, m_nNCurrFrameX, m_nNCurrFrameY, 3);
				}
			}
		}

		// 플레이어가 왼쪽을 보고 있을때 이미지 랜더
		else if (m_bPlayerSee == 0)
		{
			m_pImg2->frameRender(hdc, m_fX - (m_pImg->getFrameWidth() * 3) / 2, m_fY - (m_pImg->getFrameHeight() * 3) / 2 - 10, m_nLCurrFrameX, m_nLCurrFrameY, 3);

			if (m_bItem)
			{
				if (m_bPlayerAttack)
				{
					m_pImg3->frameRender(hdc, m_fX - 200, m_fY - 70, m_nNCurrFrameX, m_nNCurrFrameY, 3);
				}
				else if (m_bPlayerDownAt)
				{
					m_pImg3->frameRender(hdc, m_fX - 200, m_fY - 35, m_nNCurrFrameX, m_nNCurrFrameY, 3);
				}
			}
		}
	}

	if (m_bDamageShow == 1)
	{
		DamageImg(hdc, 0);
	}


	Rectangle(hdc, m_Irc.left, m_Irc.top, m_Irc.right, m_Irc.bottom);
}


void player::mapMove()
{

	if (m_fX > (WINSIZEX / 2) - 6 && m_fX < (WINSIZEX / 2) + 6)
	{
		m_xCameraOn = true;
		m_fX = WINSIZEX / 2;
	}

	if (m_fY > (WINSIZEY / 2) + 75 - 10 && m_fY < (WINSIZEY / 2) + 75 + 10)
	{
		m_yCameraOn = true;
		m_fY = WINSIZEY / 2 + 75;
	}


	if (m_xCameraOn)
	{
		if (m_fX < WINSIZEX / 2)
		{
			ROOMMANAGER->mapMove(m_fX - WINSIZEX / 2, 0);
			m_fX = WINSIZEX / 2;
		}
		else if (m_fX > WINSIZEX / 2)
		{
			ROOMMANAGER->mapMove(m_fX - WINSIZEX / 2, 0);
			m_fX = WINSIZEX / 2;
		}
	}
	if (m_yCameraOn)
	{
		if (m_fY < WINSIZEY / 2 + 75)
		{
			ROOMMANAGER->mapMove(0, m_fY - 75 - WINSIZEY / 2);
			m_fY = WINSIZEY / 2 + 75;
		}
		else if (m_fY > WINSIZEY / 2 + 75)
		{
			ROOMMANAGER->mapMove(0, m_fY - 75 - WINSIZEY / 2);
			m_fY = WINSIZEY / 2 + 75;
		}
	}
}

void player::mapchackCollision()
{
	for (int y = m_rc.top; y <= m_rc.bottom; y++)
	{
		COLORREF color = GetPixel(ROOMMANAGER->getCurrRoom()->getMemDCInfo()->hMemDC,
			m_fX + ROOMMANAGER->getCurrRoom()->getPosMap().x,
			y + ROOMMANAGER->getCurrRoom()->getPosMap().y);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);


		if (!(r == 0 && g == 88 && b == 24))
		{
			if (y > m_fY)
			{
				m_fY--;
			}
			else if ((y < m_fY))
			{
				m_fY++;
			}
		}
		else
		{
			m_bPlayerStand = 0;
		}

		if (y == m_rc.bottom)
		{
			y++;

			color = GetPixel(ROOMMANAGER->getCurrRoom()->getMemDCInfo()->hMemDC,
				m_fX + ROOMMANAGER->getCurrRoom()->getPosMap().x,
				y + ROOMMANAGER->getCurrRoom()->getPosMap().y);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (!(r == 0 && g == 88 && b == 24))
			{

				m_fY -= m_fGravity;

			}

			color = GetPixel(ROOMMANAGER->getCurrRoom()->getMemDCInfo()->hMemDC,
				m_fX + ROOMMANAGER->getCurrRoom()->getPosMap().x,
				m_rc.bottom + 30 + ROOMMANAGER->getCurrRoom()->getPosMap().y);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (!(r == 0 && g == 88 && b == 24))
			{
				m_bPlayerStand = 1;
				m_nPlayerJump = 0;
				m_bPlayerJumpAttack = 0;
				if (m_nRCurrFrameY == 6)
				{
					m_nRCurrFrameY = 0;
					m_nRCurrFrameX = 0;
				}
				else if (m_nLCurrFrameY == 6)
				{
					m_nLCurrFrameY = 0;
					m_nLCurrFrameX = 18;
				}
			}
		}
	}

	for (int x = m_rc.left; x < m_rc.right; x++)
	{
		COLORREF color = GetPixel(ROOMMANAGER->getCurrRoom()->getMemDCInfo()->hMemDC,
			x + ROOMMANAGER->getCurrRoom()->getPosMap().x,
			m_fY + ROOMMANAGER->getCurrRoom()->getPosMap().y);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);


		if (!(r == 0 && g == 88 && b == 24))
		{
			if (x > m_fX)
			{
				m_fX--;
			}
			else if ((x < m_fX))
			{
				m_fX++;
			}
		}
	}
}

void player::mapRectCollision()
{
	for (int i = 0; i < ROOMMANAGER->getCurrRoom()->getRectNum(); i++)
	{

		RECT rc;

		if (IntersectRect(&rc, &m_rc, &(ROOMMANAGER->getCurrRoom()->getRectObj()[i])))
		{
			m_bPlayerStand = 1;
			m_nPlayerJump = 0;
			if (m_nRCurrFrameY == 6)
			{
				m_nRCurrFrameY = 0;
				m_nRCurrFrameX = 0;
			}
			else if (m_nLCurrFrameY == 6)
			{
				m_nLCurrFrameY = 0;
				m_nLCurrFrameX = 18;
			}
		}


		for (int i = 0; i < ROOMMANAGER->getCurrRoom()->getRectNum(); i++)
		{
			if (ROOMMANAGER->getCurrRoom()->getRectObj()[i].top + 13 > m_rc.bottom &&
				ROOMMANAGER->getCurrRoom()->getRectObj()[i].top - 7 < m_rc.bottom
				&& (m_rc.right > ROOMMANAGER->getCurrRoom()->getRectObj()[i].left &&
					m_rc.left < ROOMMANAGER->getCurrRoom()->getRectObj()[i].right))
			{

				m_fY = (ROOMMANAGER->getCurrRoom()->getRectObj()[i].top - 50);


			}

		}
	}
}

void player::hitCollision(int damage)
{
	if (m_bDivin == 0)
	{
		if (m_bPlayerStand == 0)
		{
			m_bPlayerHited = 1;
			m_bDivin = 1;
			if (m_nHitDivineC == 100)
			{
				m_status.curHP -= damage;
			}
		}
		else if (m_bPlayerStand == 1)
		{
			m_bPlayerHited = 1;
			m_bDivin = 1;
			if (m_nHitDivineC == 100)
			{
				m_status.curHP -= damage;
			}
		}
	}
}

void player::DamageImg(HDC hdc, int damage)
{
	int Num = 0;
	if (damage >= 10000)
	{
		m_pCImg->frameRender(hdc, m_fX, m_fDamageY, 9, 2, 3);
		m_pCImg->frameRender(hdc, m_fX + 15, m_fDamageY, 9, 2, 3);
		m_pCImg->frameRender(hdc, m_fX + 30, m_fDamageY, 9, 2, 3);
		m_pCImg->frameRender(hdc, m_fX + 45, m_fDamageY, 9, 2, 3);
		m_pCImg->frameRender(hdc, m_fX + 60, m_fDamageY, 9, 2, 3);
	}
	else if (damage < 10000 && damage >= 1000)
	{

		Num = (damage / 1000);
		m_pCImg->frameRender(hdc, m_fX, m_fDamageY, Num, 2, 3);
		Num = (damage / 100) - ((damage / 1000) * 10);
		m_pCImg->frameRender(hdc, m_fX + 15, m_fDamageY, Num, 2, 3);
		Num = (damage / 10) - ((damage / 100) * 10);
		m_pCImg->frameRender(hdc, m_fX + 30, m_fDamageY, Num, 2, 3);
		Num = (damage % 10);
		m_pCImg->frameRender(hdc, m_fX + 45, m_fDamageY, Num, 2, 3);
	}
	else if (damage < 1000 && damage >= 100)
	{
		Num = (damage / 100);
		m_pCImg->frameRender(hdc, m_fX, m_fDamageY, Num, 2, 3);
		Num = (damage / 10) - ((damage / 100) * 10);
		m_pCImg->frameRender(hdc, m_fX + 15, m_fDamageY, Num, 2, 3);
		Num = (damage % 10);
		m_pCImg->frameRender(hdc, m_fX + 30, m_fDamageY, Num, 2, 3);
	}
	else if (damage < 100 && damage >= 10)
	{
		Num = (damage / 10) - ((damage / 100) * 10);
		m_pCImg->frameRender(hdc, m_fX, m_fDamageY, Num, 2, 3);
		Num = (damage % 10);
		m_pCImg->frameRender(hdc, m_fX + 15, m_fDamageY, Num, 2, 3);
	}
	else
	{
		Num = (damage % 10);
		m_pCImg->frameRender(hdc, m_fX, m_fDamageY, Num, 2, 3);
	}

}

void player::ShowDamage()
{
	if (m_bPlayerHited == 1)
	{
		m_bDamageShow = 1;
	}

	if (m_bDamageShow == 1)
	{
		m_nNumC++;
		m_fDamageY--;
		if (m_nNumC >= 20)
		{
			m_nNumC = 0;
			m_bDamageShow = 0;
			m_fDamageY = m_fY - 80;
		}
	}
}

void player::FallDown()
{
	/*	if (m_bPlayerStand == 0)
		{
			m_fY -= m_fGravity;
		} */
}

void player::hitMosion()
{
	if (m_bDivin == 1)
	{
		m_nHitDivineC--;
		if (m_nHitDivineC <= 0)
		{
			m_bDivin = 0;
			m_nHitDivineC = 100;
		}
	}
	if (m_bPlayerHited == 1)
	{
		m_nHitC++;
		if (m_bPlayerStand == 0)
		{
			if (m_bPlayerSee == 1)
			{
				m_nRCurrFrameY = 5;
			}
			else if (m_bPlayerSee == 0)
			{
				m_nLCurrFrameY = 5;
			}
		}
		else if (m_bPlayerStand == 1)
		{
			if (m_bPlayerSee == 1)
			{
				m_nRCurrFrameY = 5;
				m_nRCurrFrameX = 0;
			}
			else if (m_bPlayerSee == 0)
			{
				m_nLCurrFrameY = 5;
				m_nLCurrFrameX = 18;
			}
		}
		if (m_nHitC < 10)
		{
			if (m_bPlayerSee == 1)
			{
				m_fX -= 7.0f;
			}
			else if (m_bPlayerSee == 0)
			{
				m_fX += 7.0f;
			}
		}
		else if (m_nHitC >= 10)
		{
			m_nHitC = 0;
			m_bPlayerHited = 0;
			if (m_bPlayerSee == 1)
			{
				m_nRCurrFrameY = 0;
				m_nRCurrFrameX = 0;
			}
			else if (m_bPlayerSee == 0)
			{
				m_nLCurrFrameY = 0;
				m_nLCurrFrameX = 18;
			}
		}
	}
}




player::player()
{
}


player::~player()
{
}
