#include "stdafx.h"
#include "player.h"


HRESULT player::init()
{
	// 플레이어의 오른쪽 보고 있을떄의 이미지 0부터 프레임 시작
	m_pImg = IMAGEMANAGER->addImage("player", "image/playerMotion.bmp", 855, 741, 19, 13, true, RGB(0, 64, 128));


	// 플레이어의 왼쪽 보고 있을떄의 이미지 18부터 프레임 시작
	m_pImg2 = IMAGEMANAGER->addImage("player2", "image/playerMotion2.bmp", 855, 741, 19, 13, true, RGB(0, 64, 128));

	// 플레이어의 동작 프레임 값
	m_nCount = 0;
	m_nRCurrFrameX = 0;
	m_nRCurrFrameY = 0;

	m_nLCurrFrameX = 18;
	m_nLCurrFrameY = 0;

	// 플레이어의 속성 초기화
	m_Speed = 6.0f;
	m_JumP = 7.0f;
	m_Gravity = 3;
	m_SildeP = 1.0f;
	m_BackP = 10.0f;
	m_SildeC = 0;
	m_BackC = 0;

	// 플레이어의 초기 위치 값
	m_fX = 100;
	m_fY = 400;

	// 플레이어가 오른쪽 보고 있는 상태로 초기화
	m_PlayerSee = 1;

	// 플레이어의 공격 모션 초기화
	m_PlayerAttack = 0;

	// 플레이어의 점프 모션 초기화 점프는 int형식으로 주어서 2단 점프를 구현
	m_PlayerJump = 0;

	// 플레이어의 앉기 모션 초기화
	m_PlayerDown = 0;

	// 플레이어의 백대쉬 모션 초기화
	m_PlayerBackDash = 0;

	// 플레이어의 슬라이딩 모션 초기화
	m_PlayerSilde = 0;

	m_rc = RectMakeCenter(m_fX, m_fY, (m_pImg->getFrameWidth()-20)*3, (m_pImg->getFrameHeight() - 20)*3);

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	// 플레이어 렉트 업데이트
	if(m_fY <= 400)
	{
		m_fY += m_Gravity;
	}
	m_rc = RectMakeCenter(m_fX, m_fY, (m_pImg->getFrameWidth()*3)/2 , (m_pImg->getFrameHeight() * 3)/2);
	
	// 키입력시 플레이어의 행동

	// 플레이어 좌우 이동
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && m_PlayerDown == 0)
	{
		m_PlayerAttack = 0;
		m_PlayerSee = 1;
		m_nRCurrFrameY = 3;
		m_fX += m_Speed;

		mapMove(m_Speed, 0);

		

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
		mapMove(-m_Speed, 0);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) && m_PlayerDown == 0)
	{
		m_nLCurrFrameX = 18;
		m_nLCurrFrameY = 0;
	}

	// 플레이어 점프
	if (KEYMANAGER->isStayKeyDown('Z') && m_PlayerJump < 2 && m_PlayerDown == 0)
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
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && m_PlayerJump == 0)
	{
		m_PlayerDown = 1;
		m_nRCurrFrameY = 11;
	}

	if(KEYMANAGER->isOnceKeyUp(VK_DOWN) && m_PlayerSilde == 0)
	{
		m_PlayerDown = 2;
	}

	// 플레이어 슬라이딩
	if (KEYMANAGER->isOnceKeyDown('Z') && m_PlayerDown == 1 && m_PlayerSilde == 0)
	{
		m_nRCurrFrameX = 7;
		m_PlayerSilde = 1;
	}

	// 플레이어 백대쉬
	if (KEYMANAGER->isOnceKeyDown('A') && m_PlayerBackDash == 0 && m_PlayerDown == 0 && m_PlayerJump == 0)
	{
		m_nRCurrFrameX = 2;
		m_nRCurrFrameY = 4;
		m_PlayerBackDash = 1;

	}

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
					m_nCount = 0;
				}
			}
		}
		
		// 플레이어 이동자세
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
					m_nCount = 0;
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

		// 플레이어 앉기 자세
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
					m_nRCurrFrameX = 0;
					m_nRCurrFrameY = 0;
					m_PlayerDown = 0;
					m_nCount = 0;
				}
			}
		}

		// 플레이어 슬라이딩 자세
		else if (m_nRCurrFrameY == 11 && m_PlayerSilde == 1 && m_PlayerDown == 1)
		{
			if (m_nCount % 1 == 0)
			{
				if (m_SildeC>5)
				{
					m_nRCurrFrameX++;
					m_SildeC = 0;
				}
				else
				{
					m_SildeC++;
				}

				if (m_nRCurrFrameX < 9)
				{
					m_fX += 10;
				}
			}


			if (m_nCount % 15 == 0)
			{

				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > 9)
				{
					m_nRCurrFrameX = 10;
					m_nRCurrFrameY = 11;
					m_PlayerDown = 2;
					m_PlayerSilde = 0;
					m_SildeP = 1.0f;
					m_SildeC = 0;
				}
			}
		}

		// 플레이어 백대쉬 자세
		else if (m_nRCurrFrameY == 4 && m_PlayerBackDash == 1)
		{
			m_fX -= m_BackP;
			m_BackP++;
			if (m_nCount % 5 == 0)
			{
				m_nRCurrFrameX++;
				m_pImg->setFrameX(m_nRCurrFrameX);
				if (m_nRCurrFrameX > 4)
				{
					m_nRCurrFrameX = 0;
					m_nRCurrFrameY = 0;
					m_PlayerBackDash = 0;
					m_BackP = 10.0f;
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
