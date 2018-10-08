#include "stdafx.h"
#include "player.h"
#include "room.h"
#include "zombie.h"
#include "bulletSoul.h"
#include "guardianSoul.h"
#include "enchantSoul.h"


HRESULT player::init()
{
	// 플레이어의 오른쪽 보고 있을떄의 이미지 0부터 프레임 시작
	m_pImg = IMAGEMANAGER->addImage("player", "image/playerMotion.bmp", 855, 741, 19, 13, true, RGB(0, 64, 128));

	// 플레이어의 왼쪽 보고 있을떄의 이미지 18부터 프레임 시작
	m_pImg2 = IMAGEMANAGER->addImage("player2", "image/playerMotion2.bmp", 855, 741, 19, 13, true, RGB(0, 64, 128));

	// 칼
	m_pImg3 = IMAGEMANAGER->addImage("발뭉", "image/발뭉.bmp", 720, 24, 9, 1, true, RGB(255, 0, 255));

	m_Zombie = new zombie;

	// 플레이어의 동작 프레임 값
	m_nCount = 0;
	m_nRCurrFrameX = 0;
	m_nRCurrFrameY = 0;

	m_nLCurrFrameX = 18;
	m_nLCurrFrameY = 0;

	m_nNCurrFrameX = 0;
	m_nNCurrFrameY = 0;

	// 플레이어의 속성 초기화
	m_Speed = 6.0f; //테스팅용으로 
	m_JumP = 20.0f;
	m_Gravity = 10.0f;
	m_SildeP = 10.0f;
	m_BackP = 8.0f;
	m_SildeC = 0;
	m_BackC = 0;
	m_JumC = 0;
	m_JumMC = 0;
	m_motionC = 0;
	// 플레이어의 초기 위치 값
	m_fX = 200;
	m_fY = 400;

	// 플레이어가 오른쪽 보고 있는 상태로 초기화
	m_PlayerSee = 1;

	// 플레이어의 공격 모션 초기화
	m_PlayerAttack = 0;

	// 플레이어의 점프 모션 초기화 점프는 int형식으로 주어서 2단 점프를 구현
	m_PlayerJump = 0;
	m_PlayerJumpDown = 0;
	m_PlayerJumpM = 0;
	m_PlayerJumpAttack = 0;

	// 플레이어의 앉기 모션 초기화
	m_PlayerDown = 0;
	m_PlayerDownAt = 0;

	// 플레이어의 백대쉬 모션 초기화
	m_PlayerBackDash = 0;

	// 플레이어의 슬라이딩 모션 초기화
	m_PlayerSilde = 0;

	// 플레이어의 착지 모션 초기화
	m_PlayerStand = 0;

	m_status = { 10,10,12,12,11,11,9,9, 10,10,11,11,320,320,80,80,0,84 };

	m_nGold = 0;

	m_rc = RectMakeCenter(m_fX, m_fY, (m_pImg->getFrameWidth()-20)*3, (m_pImg->getFrameHeight() - 20)*3);
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

	guardianSoul* baseGSoul = new guardianSoul;
	baseGSoul->init(0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, "------", "---");

	guardianSoul* testGSoul = new guardianSoul;
	testGSoul->init(0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, "메두사 헤드", "공중에서 정지가 가능하다.");

	m_soulInven.vecGuardianSoul.push_back(baseGSoul);
	m_soulInven.vecGuardianSoul.push_back(testGSoul);

	enchantSoul* baseESoul = new enchantSoul;
	baseESoul->init(0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, "------", "---");

	enchantSoul* testESoul = new enchantSoul;
	testESoul->init(0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, "좀비", "CON +1");

	m_soulInven.vecEnchantSoul.push_back(baseESoul);
	m_soulInven.vecEnchantSoul.push_back(testESoul);


	m_soulSet.bS = baseBSoul;
	m_soulSet.gS = baseGSoul;
	m_soulSet.eS = baseESoul;


	

	m_Item = 0;

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	// 중력 적용

	m_fY += m_Gravity;
	
	
	
	// 키입력시 플레이어의 행동

	// 플레이어 좌우 이동
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && m_PlayerDown == 0 && m_PlayerBackDash == 0 && m_PlayerAttack == 0)
	{
		m_PlayerAttack = 0;
		m_PlayerSee = 1;
		if (m_PlayerJump == 0)
		{
			m_nRCurrFrameY = 3;
		}
		m_fX += m_Speed;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) && m_PlayerDown == 0 && m_PlayerBackDash == 0 && m_PlayerAttack == 0)
	{
		m_nRCurrFrameX = 0;
		m_nRCurrFrameY = 0;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && m_PlayerDown == 0 && m_PlayerBackDash == 0 && m_PlayerAttack == 0)
	{
		m_PlayerAttack = 0;
		m_PlayerSee = 0;
		m_nLCurrFrameY = 3;
		m_fX -= m_Speed;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) && m_PlayerDown == 0 && m_PlayerBackDash == 0 && m_PlayerAttack == 0)
	{
		m_nLCurrFrameX = 18;
		m_nLCurrFrameY = 0;
	}

	if (KEYMANAGER->isOnceKeyDownNotuch('Z'))
	{
		m_bIsJump = true;
	}

	// 플레이어 점프
	if (KEYMANAGER->isStayKeyDown('Z') && m_PlayerAttack == 0)
	{
		if (m_bIsJump)
		{
			if (m_PlayerDown == 0 && m_PlayerJump <= 2)
			{
				m_JumMC++;
				if (m_JumMC < 2)
				{
					m_nRCurrFrameX = 2;
				}
				m_PlayerJumpM = 1;
				m_nRCurrFrameY = 6;
				if (m_PlayerJump == 0)
				{
					m_PlayerJump = 1;
				}
				m_JumC++;
				m_fY -= m_JumP;

				if (m_JumC < 30 && m_JumC > 10)
				{
					m_JumP = 10;
				}
				else if (m_JumC > 30)
				{
					m_JumP--;
					if (m_JumP <= 0)
					{
						m_JumP = 0;
					}
				}
			}


			// 플레이어 슬라이딩
			else if (m_PlayerDown == 1 && m_PlayerJump == 0)
			{
				m_PlayerJump = 3;
				m_PlayerSilde = 1;
				if (m_PlayerSee == 1)
				{
					m_nRCurrFrameX = 7;
				}
				else if (m_PlayerSee == 0)
				{
					m_nLCurrFrameX = 12;
				}
			}
		}
	}

	if (KEYMANAGER->isOnceKeyUp('Z') && m_PlayerJump <= 3)
	{
		m_PlayerJump++;
		m_PlayerJumpDown = 1;
		m_PlayerJumpM = 0;
		m_nRCurrFrameY = 6;
		m_nRCurrFrameX = 0;
		m_JumC = 0;
		m_JumP = 20.0f;
		m_JumMC = 0;
	}

	// 플레이어 공격
	if (KEYMANAGER->isOnceKeyDown('X') && m_PlayerAttack == 0 && m_PlayerSilde == 0 && m_PlayerJumpM == 0)
	{
		if (m_PlayerDown == 0 && m_PlayerStand == 1)
		{
			m_PlayerAttack = 1;
			m_PlayerBackDash = 0;
			if (m_PlayerSee == 1)
			{
				m_nRCurrFrameX = 0;
				m_nRCurrFrameY = 1;
			}
			else if (m_PlayerSee == 0)
			{
				m_nLCurrFrameX = 18;
				m_nLCurrFrameY = 1;
			}
		}
		else if (m_PlayerDown == 1 && m_PlayerAttack == 0 && m_PlayerDownAt == 0)
		{
			m_PlayerDownAt = 1;
			m_nRCurrFrameX = 10;
			m_nRCurrFrameY = 11;
		}
		else if (m_PlayerStand == 0)
		{
			m_PlayerJumpAttack = 1;
			m_nRCurrFrameY = 6;
			m_nRCurrFrameX = 4;
		}
	}

	// 플레이어 앉기
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && m_PlayerAttack == 0)
	{
		m_PlayerDown = 1;
		if (m_PlayerSee == 1)
		{
			m_nRCurrFrameY = 11;
		}
		else if (m_PlayerSee == 0)
		{
			m_nLCurrFrameY = 11;
		}
	}

	if(KEYMANAGER->isOnceKeyUp(VK_DOWN) && m_PlayerSilde == 0 && m_PlayerDownAt == 0)
	{
		m_PlayerDown = 2;
	}

	//// 플레이어 슬라이딩
	//if (KEYMANAGER->isOnceKeyDown('Z') && m_PlayerDown == 1 && m_PlayerSilde == 0 && m_PlayerAttack == 0 && m_PlayerJump == 0)
	//{
	//	m_PlayerSilde = 1;
	//	if (m_PlayerSee == 1)
	//	{
	//		m_nRCurrFrameX = 7;
	//	}
	//	else if (m_PlayerSee == 0)
	//	{
	//		m_nLCurrFrameX = 12;
	//	}
	//}

	// 플레이어 백대쉬
	if (KEYMANAGER->isOnceKeyDown('A') && m_PlayerBackDash == 0 && m_PlayerDown == 0 && m_PlayerJump == 0)
	{
		m_PlayerBackDash = 1;
		m_PlayerAttack = 0;
		if (m_PlayerSee == 1)
		{
			m_nRCurrFrameX = 2;
			m_nRCurrFrameY = 4;
		}
		else if (m_PlayerSee == 0)
		{
			m_nLCurrFrameX = 17;
			m_nLCurrFrameY = 4;
		}

	}


	// 플레이어가 우측 방향을 보고 있을 떄 프레임 모션 지정
	if (m_PlayerSee == 1)
	{
		m_nCount++;
		// 플레이어 기본자세
		if (m_nRCurrFrameY == 0 && m_PlayerStand == 1)
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
		else if (m_nRCurrFrameY == 3 && m_PlayerStand == 1)
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
		else if (m_nRCurrFrameY == 1 && m_PlayerAttack == 1)
		{
			if (m_nCount % 4 == 0)
			{
				m_nRCurrFrameX++;
				if (m_nRCurrFrameX > 2)
				{
					m_Item = 1;
					m_nNCurrFrameX++;


					if (m_nNCurrFrameX > 0 && m_nNCurrFrameX < 5)
					{
						m_Irc = RectMakeCenter(m_fX + 120, m_fY - 40, m_pImg3->getFrameWidth() * 2, m_pImg3->getFrameHeight() * 2);
					}
				}
				m_pImg->setFrameX(m_nRCurrFrameX);
				m_pImg3->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > m_pImg->getMaxFrameX() - 7)
				{
					m_nRCurrFrameX = 0;
					m_PlayerAttack = 0;
					m_nRCurrFrameY = 0;
					m_nNCurrFrameX = 0;
					m_Item = 0;
					m_nCount = 0;
					m_Irc = RectMakeCenter(-10, -10, 1, 1);
				}
			}
		}

		// 플레이어 점프 자세
		else if (m_nRCurrFrameY == 6 && m_PlayerJumpM == 1 && m_PlayerStand == 0 && m_JumC < 30)
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

		else if (m_nRCurrFrameY == 6 && m_PlayerJumpAttack == 1)
		{
			if (m_nCount % 5 == 0)
			{
				m_nRCurrFrameX++;
				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > 9)
				{
					m_nRCurrFrameX;
				}
			}

		}

		// 플레이어 떨어지는 자세
		else if (m_PlayerStand == 0 && m_PlayerJumpM == 0 || m_JumC >= 30)
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
		else if (m_nRCurrFrameY == 11 && m_PlayerDown == 1 && m_PlayerSilde == 0 && m_PlayerDownAt == 0)
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
		else if (m_nRCurrFrameY == 11 && m_PlayerDown == 2)
		{
			if (m_nCount % 5 == 0)
			{
				m_nRCurrFrameX++;
				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > 5)
				{
					m_PlayerDown = 0;
					m_nCount = 0;
					m_nRCurrFrameX = 0;
					m_nRCurrFrameY = 0;
				}
			}
		}

		// 플레이어 앉아 공격 자세
		else if (m_PlayerDownAt == 1 && m_nRCurrFrameY == 11)
		{
			if (m_nCount % 5 == 0)
			{
				m_motionC++;
				if (m_motionC < 3 || m_motionC > 5)
				{
					m_nRCurrFrameX++;
				}

				if (m_nRCurrFrameX < 14)
				{
					m_Item = 1;
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
					m_PlayerDownAt = 0;
					m_PlayerDown = 2;
					m_motionC = 0;
					m_Item = 0;
				}
			}
		}

		// 플레이어 슬라이딩 자세
		else if (m_nRCurrFrameY == 11 && m_PlayerSilde == 1 && m_PlayerDown == 1)
		{
			if (m_SildeC > 5)
			{
				m_nRCurrFrameX++;
				m_SildeC = 0;
			}
			else
			{
				m_SildeC++;
			}

			if (m_nRCurrFrameX <= 9)
			{
				m_fX += m_SildeP;
			}

			if (m_nCount % 10 == 0)
			{
				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > 9)
				{
					m_PlayerDown = 2;
					m_PlayerSilde = 0;
					m_nRCurrFrameX = 9;
					m_nRCurrFrameY = 11;
					m_SildeP = 10.0f;
					m_SildeC = 0;
				}
			}
		}

		// 플레이어 백대쉬 자세
		else if (m_nRCurrFrameY == 4 && m_PlayerBackDash == 1)
		{
			m_fX -= m_BackP;
			if (m_nCount % 5 == 0)
			{
				m_nRCurrFrameX++;
				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > 4)
				{
					m_PlayerBackDash = 0;
					m_nRCurrFrameX = 0;
					m_nRCurrFrameY = 0;
				}
			}
		}
	}


	// 플레이어가 좌측 방향을 보고 있을 떄 프레임 모션 지정
	else if (m_PlayerSee == 0)
	{
		m_nCount++;

		// 플레이어 왼쪽 기본자세
		if (m_nLCurrFrameY == 0)
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
		else if (m_nLCurrFrameY == 3)
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
		else if (m_nLCurrFrameY == 1 && m_PlayerAttack == 1)
		{
			if (m_nCount % 5 == 0)
			{
				m_nLCurrFrameX--;
				m_pImg2->setFrameX(m_nLCurrFrameX);
				if (m_nLCurrFrameX < 7)
				{
					m_nLCurrFrameX = 18;
					m_PlayerAttack = 0;
					m_nLCurrFrameY = 0;
				}
			}
		}

		// 플레이어 점프 자세
		/*else if (m_nRCurrFrameY == 7)
		{
		if (m_nCount % 5 == 0)
		{
		m_nRCurrFrameX++;
		m_pImg->setFrameX(m_nRCurrFrameX);
		if (m_nRCurrFrameX > m_pImg->getMaxFrameX() - 7)
		{
		m_nRCurrFrameX = 0;
		m_PlayerAttack = 0;
		m_nRCurrFrameY = 0;
		m_nCount = 0;
		}
		}
		}*/

		// 플레이어 왼쪽 앉기 자세
		else if (m_nLCurrFrameY == 11 && m_PlayerDown == 1 && m_PlayerSilde == 0)
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

		else if (m_nLCurrFrameY == 11 && m_PlayerDown == 2)
		{
			if (m_nCount % 5 == 0)
			{
				m_nLCurrFrameX--;
				m_pImg2->setFrameX(m_nLCurrFrameX);
				if (m_nLCurrFrameX < 13)
				{
					m_nLCurrFrameX = 18;
					m_nLCurrFrameY = 0;
					m_PlayerDown = 0;
					m_nCount = 0;
				}
			}
		}

		// 플레이어 슬라이딩 자세
		else if (m_nLCurrFrameY == 11 && m_PlayerSilde == 1 && m_PlayerDown == 1)
		{
			if (m_SildeC > 5)
			{
				m_nLCurrFrameX--;
				m_SildeC = 0;
			}
			else
			{
				m_SildeC++;
			}
			if (m_nLCurrFrameX > 9)
			{
				m_fX -= m_SildeP;
			}
			if (m_nCount % 10 == 0)
			{
				m_pImg2->setFrameX(m_nLCurrFrameX);
				if (m_nLCurrFrameX < 9)
				{
					m_nLCurrFrameX = 9;
					m_nLCurrFrameY = 11;
					m_PlayerDown = 2;
					m_PlayerSilde = 0;
					m_SildeP = 10.0f;
					m_SildeC = 0;
				}
			}
		}

		// 플레이어 백대쉬 자세
		else if (m_nLCurrFrameY == 4 && m_PlayerBackDash == 1)
		{
			m_fX += m_BackP;
			if (m_nCount % 5 == 0)
			{
				m_nLCurrFrameX--;
				m_pImg2->setFrameX(m_nLCurrFrameX);
				if (m_nLCurrFrameX < 14)
				{
					m_PlayerBackDash = 0;
					m_nLCurrFrameX = 18;
					m_nLCurrFrameY = 0;
				}
			}
		}
	}

	mapchackCollision();
	mapMove();


	m_rc = RectMakeCenter(m_fX, m_fY, (m_pImg->getFrameWidth() * 3) / 2, (m_pImg->getFrameHeight() * 3) / 2);

	
}

void player::render(HDC hdc)
{
	if (m_pImg)
	{
		//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
		// 플레이어가 오른쪽을 보고 있을때 이미지 랜더
		if (m_PlayerSee == 1)
		{
			m_pImg->frameRender(hdc, m_fX - (m_pImg->getFrameWidth()*3) / 2, m_fY - (m_pImg->getFrameHeight()*3) / 2-10, m_nRCurrFrameX, m_nRCurrFrameY,3);
			if (m_Item)
			{
				if (m_PlayerAttack)
				{
					m_pImg3->frameRender(hdc, m_fX - 30, m_fY - 70, m_nNCurrFrameX, m_nNCurrFrameY, 3);
				}
				else if (m_PlayerDownAt)
				{
					m_pImg3->frameRender(hdc, m_fX - 30, m_fY - 35, m_nNCurrFrameX, m_nNCurrFrameY, 3);
				}

				Rectangle(hdc, m_Irc.left, m_Irc.top, m_Irc.right, m_Irc.bottom);
			}
		}

		// 플레이어가 왼쪽을 보고 있을때 이미지 랜더
		else if (m_PlayerSee == 0)
		{
			m_pImg2->frameRender(hdc, m_fX - (m_pImg->getFrameWidth() * 3) / 2 , m_fY - (m_pImg->getFrameHeight() * 3)/2-10, m_nLCurrFrameX, m_nLCurrFrameY,3);
		}
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

	if (m_fY > (WINSIZEY / 2)+ 75 - 10&& m_fY < (WINSIZEY / 2)+ 75 + 10)
	{
		m_yCameraOn = true;
		m_fY = WINSIZEY / 2 + 75;
	}


	if (m_xCameraOn)
	{
		if (m_fX < WINSIZEX / 2)
		{
			ROOMMANAGER->mapMove( m_fX- WINSIZEX / 2, 0);
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
		if (m_fY < WINSIZEY / 2+ 75)
		{
			ROOMMANAGER->mapMove(0, m_fY- 75 -WINSIZEY / 2);
			m_fY = WINSIZEY / 2+ 75;
		}
		else if (m_fY > WINSIZEY / 2 + 75)
		{
			ROOMMANAGER->mapMove(0, m_fY- 75 - WINSIZEY /2);
			m_fY = WINSIZEY / 2+ 75;
		}
	}
}

void player::mapchackCollision()
{
	for (int y= m_rc.top;y<=m_rc.bottom; y++)
	{
		COLORREF color = GetPixel(ROOMMANAGER->getCurrRoom()->getMemDCInfo()->hMemDC,
			m_fX+ ROOMMANAGER->getCurrRoom()->getPosMap().x,
			y + ROOMMANAGER->getCurrRoom()->getPosMap().y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);


			if (!(r == 0 && g == 88 && b == 24))
			{
				if (y>m_fY)
				{
					m_fY--;
				}
				else if((y < m_fY))
				{
					m_fY++;
				}
			}
			else
			{
				m_PlayerStand = 0;
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

						m_fY-=m_Gravity;
					
				}

				color = GetPixel(ROOMMANAGER->getCurrRoom()->getMemDCInfo()->hMemDC,
					m_fX + ROOMMANAGER->getCurrRoom()->getPosMap().x,
					m_rc.bottom + 30 + ROOMMANAGER->getCurrRoom()->getPosMap().y);

				r = GetRValue(color);
				g = GetGValue(color);
				b = GetBValue(color);

				if (!(r == 0 && g == 88 && b == 24))
				{
					m_PlayerStand = 1;
					m_PlayerJump = 0;
					if (m_nRCurrFrameY == 6)
					{
						m_nRCurrFrameY = 0;
						m_nRCurrFrameX = 0;
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


player::player()
{
}


player::~player()
{
}
