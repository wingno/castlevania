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

	
	m_Speed = 6.0f;

	m_fX = 100;
	m_fY = 400;

	m_PlayerSee = 1;

	m_PlayerAttack = 0;

	m_rc = RectMakeCenter(m_fX, m_fY, (m_pImg->getFrameWidth()-20)*3, (m_pImg->getFrameHeight() - 20)*3);

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	// 플레이어 렉트 업데이트
	m_rc = RectMakeCenter(m_fX, m_fY, (m_pImg->getFrameWidth()*3)/2 , (m_pImg->getFrameHeight() * 3)/2);
	
	// 키입력시 플레이어의 행동

	// 플레이어 좌우 이동
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		m_PlayerAttack = 0;
		m_PlayerSee = 1;
		m_nRCurrFrameY = 3;
		m_fX += m_Speed;

		mapMove(m_Speed, 0);

		

	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		m_nRCurrFrameX = 0;
		m_nRCurrFrameY = 0;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		m_PlayerAttack = 0;
		m_PlayerSee = 0;
		m_nLCurrFrameY = 3;
		m_fX -= m_Speed;
		mapMove(-m_Speed, 0);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		m_nLCurrFrameX = 18;
		m_nLCurrFrameY = 0;
	}

	// 플레이어 점프
	if (KEYMANAGER->isStayKeyDown('Z'))
	{

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
	}

	// 플레이어가 우측 방향을 보고 있을 떄 프레임 모션 지정
	if (m_PlayerSee == 1)
	{
		m_nCount++;
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
		else if (m_nRCurrFrameY == 3)
		{
			if (m_nCount % 5 == 0)
			{
				m_nRCurrFrameX++;
				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > m_pImg->getMaxFrameX())
				{
					m_nRCurrFrameX = 3;
				}
			}
		}
		else if (m_nRCurrFrameY == 1 && m_PlayerAttack == 1)
		{
			
			if (m_nCount % 5 == 0)
			{
				m_nRCurrFrameX++;
				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > m_pImg->getMaxFrameX()-7)
				{
					m_nRCurrFrameX = 0;
					m_PlayerAttack = 0;
					m_nRCurrFrameY = 0;
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
				m_pImg->setFrameX(m_nLCurrFrameX);
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
				m_pImg->setFrameX(m_nLCurrFrameX);
				if (m_nLCurrFrameX < 0)
				{
					m_nLCurrFrameX = 14;
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
			m_pImg->frameRender(hdc, m_fX - (m_pImg->getFrameWidth()*3) / 2, m_fY - (m_pImg->getFrameHeight()*3) / 2, m_nRCurrFrameX, m_nRCurrFrameY,3);
		}
		else if (m_PlayerSee == 0)
		{
			m_pImg2->frameRender(hdc, m_fX - (m_pImg->getFrameWidth() * 3) / 2, m_fY - (m_pImg->getFrameHeight() * 3)/2, m_nLCurrFrameX, m_nLCurrFrameY,3);
		}


	}
}

void player::mapMove(float fx,float fy)
{

	
	if (m_fX > (WINSIZEX / 2) - 15 && m_fX < (WINSIZEX / 2) + 15)
	{
		ROOMMANAGER->mapMove(fx, fy);
		if (fx > 0&& m_fX>WINSIZEX/2)
		{
			m_fX -= fx;
		}
		else if (fx < 0 && m_fX < WINSIZEX / 2)
		{
			m_fX -= fx;
		}
	}


}



player::player()
{
}


player::~player()
{
}
