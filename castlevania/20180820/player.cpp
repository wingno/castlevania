#include "stdafx.h"
#include "player.h"
#include "room.h"


HRESULT player::init()
{
	// �÷��̾��� ������ ���� �������� �̹��� 0���� ������ ����
	m_pImg = IMAGEMANAGER->addImage("player", "image/playerMotion.bmp", 855, 741, 19, 13, true, RGB(0, 64, 128));

	//aaaaa
	// �÷��̾��� ���� ���� �������� �̹��� 18���� ������ ����
	m_pImg2 = IMAGEMANAGER->addImage("player2", "image/playerMotion2.bmp", 855, 741, 19, 13, true, RGB(0, 64, 128));

	// �÷��̾��� ���� ������ ��
	m_nCount = 0;
	m_nRCurrFrameX = 0;
	m_nRCurrFrameY = 0;

	m_nLCurrFrameX = 18;
	m_nLCurrFrameY = 0;

	// �÷��̾��� �Ӽ� �ʱ�ȭ
	m_Speed = 6.0f;
	m_JumP = 20.0f;
	m_Gravity = 10.0f;
	m_SildeP = 10.0f;
	m_BackP = 8.0f;
	m_SildeC = 0;
	m_BackC = 0;
	m_JumC = 0;

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

	// �÷��̾��� �ɱ� ��� �ʱ�ȭ
	m_PlayerDown = 0;

	// �÷��̾��� ��뽬 ��� �ʱ�ȭ
	m_PlayerBackDash = 0;

	// �÷��̾��� �����̵� ��� �ʱ�ȭ
	m_PlayerSilde = 0;

	// �÷��̾��� ���� ��� �ʱ�ȭ
	m_PlayerStand = 0;

	m_status = { 10,10,12,12,11,11,9,9, 10,10,11,11,320,320,80,80,0,84 };

	m_nGold = 0;

	m_rc = RectMakeCenter(m_fX, m_fY, (m_pImg->getFrameWidth()-20)*3, (m_pImg->getFrameHeight() - 20)*3);

	m_xCameraOn = false;
	m_yCameraOn = false;

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

	// �÷��̾� ����
	if (KEYMANAGER->isStayKeyDown('Z') && m_PlayerJump <= 2 && m_PlayerDown == 0 && m_PlayerAttack == 0)
	{
		m_JumC++;
		m_fY -= m_JumP;
		m_nRCurrFrameY = 6;
		m_PlayerJump = 1;
		if (m_JumC < 20 && m_JumC > 10)
		{
			m_JumP = 10;
		}
		else if (m_JumC > 20)
		{
			m_JumP--;
			if (m_JumP <= 0)
			{
				m_JumP = 0;
			}
		}
	}

	if (KEYMANAGER->isOnceKeyUp('Z') && m_PlayerJump <= 2)
	{
		m_PlayerJump++;
		m_PlayerJumpDown = 1;
		m_JumC = 0;
		m_JumP = 20.0f;
	}

	// �÷��̾� ����
	if (KEYMANAGER->isOnceKeyDown('X') && m_PlayerAttack == 0 && m_PlayerSilde == 0)
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

	if(KEYMANAGER->isOnceKeyUp(VK_DOWN) && m_PlayerSilde == 0)
	{
		m_PlayerDown = 2;
	}

	// �÷��̾� �����̵�
	if (KEYMANAGER->isOnceKeyDown('Z') && m_PlayerDown == 1 && m_PlayerSilde == 0 && m_PlayerAttack == 0)
	{
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
		if (m_nRCurrFrameY == 0)
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
		else if (m_nRCurrFrameY == 3)
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
				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > m_pImg->getMaxFrameX() - 7)
				{
					m_nRCurrFrameX = 0;
					m_PlayerAttack = 0;
					m_nRCurrFrameY = 0;
					m_nCount = 0;
				}
			}
		}

		// �÷��̾� ���� �ڼ�
		else if (m_nRCurrFrameY == 6 && m_PlayerJump <= 2)
		{
			if (m_nCount % 5 == 0)
			{
				m_nRCurrFrameX++;
				if (m_JumC < 20)
				{
					if (m_nRCurrFrameX == 2)
					{
						m_nRCurrFrameX = 0;
					}
				}
				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > m_pImg->getMaxFrameX() - 7)
				{
					m_nRCurrFrameX = 0;
					m_PlayerAttack = 0;
					m_nRCurrFrameY = 0;
					m_nCount = 0;
				}
			}
		}

		// �÷��̾� �������� �ڼ�
		/*else if (m_PlayerStand == 0)
		{
			m_nRCurrFrameY = 6;
			m_nRCurrFrameX = 7;
			m_nRCurrFrameX++;
			if (m_nRCurrFrameX == 8)
			{
				m_nRCurrFrameX = 7;
			}
		}*/

		// �÷��̾� �ɱ� �ڼ�
		else if (m_nRCurrFrameY == 11 && m_PlayerDown == 1 && m_PlayerSilde == 0)
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
		Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
		// �÷��̾ �������� ���� ������ �̹��� ����
		if (m_PlayerSee == 1)
		{
			m_pImg->frameRender(hdc, m_fX - (m_pImg->getFrameWidth()*3) / 2, m_fY - (m_pImg->getFrameHeight()*3) / 2-10, m_nRCurrFrameX, m_nRCurrFrameY,3);
		}

		// �÷��̾ ������ ���� ������ �̹��� ����
		else if (m_PlayerSee == 0)
		{
			m_pImg2->frameRender(hdc, m_fX - (m_pImg->getFrameWidth() * 3) / 2 , m_fY - (m_pImg->getFrameHeight() * 3)/2-10, m_nLCurrFrameX, m_nLCurrFrameY,3);
		}
	}
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


		m_PlayerStand = 0;
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
					m_PlayerStand = 1;
					m_PlayerJump = 0;

				}
				else if((y < m_fY))
				{
					m_fY++;
				}
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
					if (y > m_fY)
					{
						m_fY-=m_Gravity;
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
