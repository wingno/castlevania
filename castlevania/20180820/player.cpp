#include "stdafx.h"
#include "player.h"
#include "room.h"
#include "zombie.h"
#include "bulletSoul.h"
#include "guardianSoul.h"
#include "enchantSoul.h"


HRESULT player::init()
{
	// �÷��̾��� ������ ���� �������� �̹��� 0���� ������ ����
	m_pImg = IMAGEMANAGER->addImage("player", "image/playerMotion.bmp", 855, 741, 19, 13, true, RGB(0, 64, 128));

	// �÷��̾��� ���� ���� �������� �̹��� 18���� ������ ����
	m_pImg2 = IMAGEMANAGER->addImage("player2", "image/playerMotion2.bmp", 855, 741, 19, 13, true, RGB(0, 64, 128));

	// Į
	m_pImg3 = IMAGEMANAGER->addImage("�߹�", "image/�߹�.bmp", 720, 24, 9, 1, true, RGB(255, 0, 255));

	m_Zombie = new zombie;

	// �÷��̾��� ���� ������ ��
	m_nCount = 0;
	m_nRCurrFrameX = 0;
	m_nRCurrFrameY = 0;

	m_nLCurrFrameX = 18;
	m_nLCurrFrameY = 0;

	m_nNCurrFrameX = 0;
	m_nNCurrFrameY = 0;

	// �÷��̾��� �Ӽ� �ʱ�ȭ
	m_Speed = 6.0f; //�׽��ÿ����� 
	m_JumP = 20.0f;
	m_Gravity = 10.0f;
	m_SildeP = 10.0f;
	m_BackP = 8.0f;
	m_SildeC = 0;
	m_BackC = 0;
	m_JumC = 0;
	m_JumMC = 0;
	m_motionC = 0;
	// �÷��̾��� �ʱ� ��ġ ��
	m_fX = 200;
	m_fY = 400;

	// �÷��̾ ������ ���� �ִ� ���·� �ʱ�ȭ
	m_PlayerSee = 1;

	// �÷��̾��� ���� ��� �ʱ�ȭ
	m_PlayerAttack = 0;

	// �÷��̾��� ���� ��� �ʱ�ȭ ������ int�������� �־ 2�� ������ ����
	m_PlayerJump = 0;
	m_PlayerJumpDown = 0;
	m_PlayerJumpM = 0;
	m_PlayerJumpAttack = 0;

	// �÷��̾��� �ɱ� ��� �ʱ�ȭ
	m_PlayerDown = 0;
	m_PlayerDownAt = 0;

	// �÷��̾��� ��뽬 ��� �ʱ�ȭ
	m_PlayerBackDash = 0;

	// �÷��̾��� �����̵� ��� �ʱ�ȭ
	m_PlayerSilde = 0;

	// �÷��̾��� ���� ��� �ʱ�ȭ
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
	testBSoul->init(0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, "�ذ���", "������ Ȱ�� ���");

	m_soulInven.vecBulletSoul.push_back(baseBSoul);
	m_soulInven.vecBulletSoul.push_back(testBSoul);

	guardianSoul* baseGSoul = new guardianSoul;
	baseGSoul->init(0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, "------", "---");

	guardianSoul* testGSoul = new guardianSoul;
	testGSoul->init(0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, "�޵λ� ���", "���߿��� ������ �����ϴ�.");

	m_soulInven.vecGuardianSoul.push_back(baseGSoul);
	m_soulInven.vecGuardianSoul.push_back(testGSoul);

	enchantSoul* baseESoul = new enchantSoul;
	baseESoul->init(0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, "------", "---");

	enchantSoul* testESoul = new enchantSoul;
	testESoul->init(0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, "����", "CON +1");

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
	// �߷� ����

	m_fY += m_Gravity;
	
	
	
	// Ű�Է½� �÷��̾��� �ൿ

	// �÷��̾� �¿� �̵�
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

	// �÷��̾� ����
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


			// �÷��̾� �����̵�
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

	// �÷��̾� ����
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

	// �÷��̾� �ɱ�
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

	//// �÷��̾� �����̵�
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

	// �÷��̾� ��뽬
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


	// �÷��̾ ���� ������ ���� ���� �� ������ ��� ����
	if (m_PlayerSee == 1)
	{
		m_nCount++;
		// �÷��̾� �⺻�ڼ�
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
		
		// �÷��̾� �̵��ڼ�
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
		
		// �÷��̾� �����ڼ�
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

		// �÷��̾� ���� �ڼ�
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

		// �÷��̾� �������� �ڼ�
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

		// �÷��̾� �ɱ� �ڼ�
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

		// �÷��̾� �ɾ� ���� �ڼ�
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

		// �÷��̾� �����̵� �ڼ�
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

		// �÷��̾� ��뽬 �ڼ�
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


	// �÷��̾ ���� ������ ���� ���� �� ������ ��� ����
	else if (m_PlayerSee == 0)
	{
		m_nCount++;

		// �÷��̾� ���� �⺻�ڼ�
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

		// �÷��̾� ���� �̵��ڼ�
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

		// �÷��̾� ���� �����ڼ�
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

		// �÷��̾� ���� �ڼ�
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

		// �÷��̾� ���� �ɱ� �ڼ�
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

		// �÷��̾� �����̵� �ڼ�
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

		// �÷��̾� ��뽬 �ڼ�
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
		// �÷��̾ �������� ���� ������ �̹��� ����
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

		// �÷��̾ ������ ���� ������ �̹��� ����
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
