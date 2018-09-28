#include "stdafx.h"
#include "player.h"


HRESULT player::init()
{
	m_pImg = IMAGEMANAGER->addImage("player", "image/playerMotion.bmp", 855, 741, 19, 13, true, RGB(0, 64, 128));

	m_pImg2 = IMAGEMANAGER->addImage("player2", "image/playerMotion2.bmp", 855, 741, 19, 13, true, RGB(0, 64, 128));

	m_nCount = 0;
	m_nRCurrFrameX = 0;
	m_nRCurrFrameY = 0;

	m_nLCurrFrameX = 18;
	m_nLCurrFrameY = 0;


	m_Speed = 2.0f;
	m_JumP = 7.0f;
	m_Gravity = 3;

	m_fX = 100;
	m_fY = 400;

	m_PlayerSee = 1;

	m_PlayerAttack = 0;

	m_PlayerJump = 0;

	m_PlayerDown = 0;


	m_rc = RectMakeCenter(m_fX, m_fY, m_pImg->getFrameWidth() - 20, m_pImg->getFrameHeight() - 20);

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	// 플레이어 렉트 업데이트
	m_rc = RectMakeCenter(m_fX, m_fY, m_pImg->getFrameWidth() - 20, m_pImg->getFrameHeight() - 20);
	if(m_fY <= 400)
	{
		m_fY += m_Gravity;
	}
	// 키입력시 플레이어의 행동

	// 플레이어 좌우 이동
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && m_PlayerDown == 0)
	{
		m_PlayerAttack = 0;
		m_PlayerSee = 1;
		m_nRCurrFrameY = 3;
		m_fX += m_Speed;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) && m_PlayerDown == 0)
	{
		m_nRCurrFrameX = 0;
		m_nRCurrFrameY = 0;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && m_PlayerDown == 0)
	{
		m_PlayerAttack = 0;
		m_PlayerSee = 0;
		m_nLCurrFrameY = 3;
		m_fX -= m_Speed;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) && m_PlayerDown == 0)
	{
		m_nLCurrFrameX = 18;
		m_nLCurrFrameY = 0;
	}

	// 플레이어 점프
	if (KEYMANAGER->isStayKeyDown('Z') && m_PlayerJump < 2)
	{
		m_fY -= m_JumP;
	//	m_nRCurrFrameY = 7;
	}

	// 플레이어 공격
	if (KEYMANAGER->isOnceKeyDown('X') && m_PlayerAttack == 0)
	{
		m_PlayerAttack = 1;
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

	// 플레이어 앉기
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		m_PlayerDown = 1;
		m_nRCurrFrameY = 11;
	}

	if(KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		m_PlayerDown = 2;
	}

	// 플레이어 슬라이딩
	//if(KEYMANAGER->isStayKeyDown(VK_DOWN) && )

	// 플레이어가 우측 방향을 보고 있을 떄 프레임 모션 지정
	if (m_PlayerSee == 1)
	{
		m_nCount++;
		// 플레이어 기본자세
		if (m_nRCurrFrameY == 0)
		{
			if (m_nCount % 20 == 0)
			{
				m_nRCurrFrameX++;
				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > 3)
				{
					m_nRCurrFrameX = 0;
				}
			}
		}
		
		// 플레이어 이동자세
		else if (m_nRCurrFrameY == 3)
		{
			if (m_nCount % 10 == 0)
			{
				m_nRCurrFrameX++;
				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > m_pImg->getMaxFrameX())
				{
					m_nRCurrFrameX = 3;
				}
			}
		}
		
		// 플레이어 공격자세
		else if (m_nRCurrFrameY == 1 && m_PlayerAttack == 1)
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
				}
			}
		}*/

		// 플레이어 앉기 자세
		else if (m_nRCurrFrameY == 11 && m_PlayerDown == 1)
		{
			if (m_nCount % 10 == 0)
			{
				m_nRCurrFrameX++;
				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > 3)
				{
					m_nRCurrFrameX = 3;
					m_nRCurrFrameY = 11;
				}
			}
		}

		else if (m_nRCurrFrameY == 11 && m_PlayerDown == 2)
		{
			if (m_nCount % 5 == 0)
			{
				m_nLCurrFrameX = 3;
				m_nRCurrFrameX++;
				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > 5)
				{
					m_nRCurrFrameX = 0;
					m_nRCurrFrameY = 0;
					m_PlayerDown = 0;
				}
			}
		}
	}


	// 플레이어가 좌측 방향을 보고 있을 떄 프레임 모션 지정
	else if (m_PlayerSee == 0)
	{
		m_nCount++;
		if (m_nLCurrFrameY == 0)
		{

			if (m_nCount % 20 == 0)
			{
				//m_nCurrFrameX = 18;
				m_nLCurrFrameX--;
				m_pImg2->setFrameX(m_nLCurrFrameX);
				if (m_nLCurrFrameX < 15)
				{
					m_nLCurrFrameX = 18;
				}
			}
		}
		else if (m_nLCurrFrameY == 3)
		{
			if (m_nCount % 10 == 0)
			{
				//m_nCurrFrameX = 18;
				m_nLCurrFrameX--;
				m_pImg2->setFrameX(m_nLCurrFrameX);
				if (m_nLCurrFrameX < 0)
				{
					m_nLCurrFrameX = 14;
				}
			}
		}
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
	}
}

void player::render(HDC hdc)
{
	if (m_pImg)
	{
		Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
		if (m_PlayerSee == 1)
		{
			m_pImg->frameRender(hdc, m_fX - m_pImg->getFrameWidth() / 2, m_fY - m_pImg->getFrameHeight() / 2, m_nRCurrFrameX, m_nRCurrFrameY);
		}
		else if (m_PlayerSee == 0)
		{
			m_pImg2->frameRender(hdc, m_fX - m_pImg->getFrameWidth() / 2, m_fY - m_pImg->getFrameHeight() / 2, m_nLCurrFrameX, m_nLCurrFrameY);
		}


	}
}

player::player()
{
}


player::~player()
{
}
