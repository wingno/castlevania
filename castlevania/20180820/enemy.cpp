#include "stdafx.h"
#include "enemy.h"
#include "missileManager.h"
#include "player.h"
#include "room.h"
#include "animation.h"





HRESULT enemy::init( POINT position, EnemyKind eKind)
{

	//std::string strFile = std::string(szFileName);
	//m_pImg = IMAGEMANAGER->addImage(strFile, szFileName,
	//	530, 32, 10, 1, true, RGB(255, 0, 255));

	//m_rc = RectMakeCenter(position.x, position.y,
	//	m_pImg->getFrameWidth(), m_pImg->getFrameHeight());

	//m_pMissileMgr = new missileManager;
	//m_pMissileMgr->init("image/bullet.bmp", 200.0f, 10);
	m_pPlayer = g_mainGame.getPlayer();

	m_fX = position.x;
	m_fY = position.y;

	m_bIsAlive = true;
	m_pMissileMgr = NULL;


	switch (m_eKind)
	{
	case RIPPER:
		m_mStatus = { "¸®ÆÛ", 20,0,20,20,0,0,10,MonsterStatus::IDLE };
		m_pImgLMotion = IMAGEMANAGER->addImage("image/RipperL.bmp", "image/RipperL.bmp", 192, 16, 12, 1, true, RGB(96, 96, 128));
		m_pImgRMotion = IMAGEMANAGER->addImage("image/RipperR.bmp", "image/RipperR.bmp", 192, 16, 12, 1, true, RGB(96, 96, 128));
		m_rc = RectMake(position.x, position.y, m_pImgLMotion->getFrameWidth()*3, m_pImgLMotion->getFrameHeight()*3);

		m_fSpeed = 10.0f;

		m_fAngle = 0;

		m_fGravity = 6.0f;



		if (m_pPlayer->getFx() > m_fX)
		{
			m_bIsLeftSee = false;
		}
		else
		{
			m_bIsLeftSee = true;
		}

		if (!m_bIsLeftSee)
		{

			m_fAngle = 80.0f;
		}
		else
		{
			m_fAngle = 100.0f;
		}


		m_pLAni1 = new int[5];
		m_pLAni1[0] = 0;
		m_pLAni1[1] = 4;
		m_pLAni1[2] = 5;
		m_pLAni1[3] = 6;
		m_pLAni1[4] = 7;

		m_pMissileMgr = new missileManager;
		m_pMissileMgr->init();

		m_aniL1 = new animation;
		m_aniL1->init(192, 16, 16, 16);
		m_aniL1->setPlayFrame(m_pLAni1, 5);
		m_aniL1->setFPS(10);

		m_pLAni2 = new int[3];
		m_pLAni2[0] = 8;
		m_pLAni2[1] = 9;
		m_pLAni2[2] = 10;

		m_aniL2 = new animation;
		m_aniL2->init(192, 16, 16, 16);
		m_aniL2->setPlayFrame(m_pLAni2, 3);
		m_aniL2->setFPS(5);

		m_pRAni1 = new int[5];
		m_pRAni1[0] = 11;
		m_pRAni1[1] = 7;
		m_pRAni1[2] = 6;
		m_pRAni1[3] = 5;
		m_pRAni1[4] = 4;

		m_aniR1 = new animation;
		m_aniR1->init(192, 16, 16, 16);
		m_aniR1->setPlayFrame(m_pRAni1, 5);
		m_aniR1->setFPS(10);
		
		m_pRAni2 = new int[3];
		m_pRAni2[0] = 3;
		m_pRAni2[1] = 2;
		m_pRAni2[2] = 1;


		m_aniR2 = new animation;
		m_aniR2->init(192, 16, 16, 16);
		m_aniR2->setPlayFrame(m_pRAni2, 3);
		m_aniR2->setFPS(5);

		break;
	default:
		break;
	}



	return S_OK;
}


void enemy::release()
{
	if (m_pMissileMgr)
	{
		m_pMissileMgr->release();
		delete m_pMissileMgr;
	}

}

void enemy::update()
{
	if (!m_bIsAlive)
		return;
	m_fY += m_fGravity;



	float elapsedTime= TIMEMANAGER->getElapsedTime();

	m_aniL1->frameUpdate(elapsedTime);
	m_aniR1->frameUpdate(elapsedTime);
	m_aniL2->frameUpdate(elapsedTime);
	m_aniR2->frameUpdate(elapsedTime);



	switch (m_eKind)
	{
		case RIPPER:

			if (m_bIsGround)
			{
				if (m_pPlayer->getFx() > m_fMapX)
				{
					m_bIsLeftSee = false;
				}
				else
				{
					m_bIsLeftSee = true;
				}

			}


			switch (m_mStatus.state)
			{
				case MonsterStatus::IDLE:
					if (WINSIZEX > m_fMapX && m_fMapX > 0 && WINSIZEY > m_fMapY &&m_fMapY > 0)
					{
						m_mStatus.state = MonsterStatus::CHASER;
					}
					break;
				case MonsterStatus::CHASER:

					move();

					if (RANDOM->getInt(100)==1)
					{
						m_mStatus.state = MonsterStatus::ATTACK;

						if (m_bIsLeftSee)
						{
								m_aniL2->start();
						}
						else
						{
								m_aniR2->start();
						}
					}

					break;
				case MonsterStatus::ATTACK:
					move();
					fire();
					break;
			

			default:
				break;
			}


			m_pMissileMgr->update();


		mapchackCollision();
		m_fMapX = m_fX - ROOMMANAGER->getCurrRoom()->getPosMap().x;
		m_fMapY = m_fY - ROOMMANAGER->getCurrRoom()->getPosMap().y;
		m_rc = RectMake(m_fMapX, m_fMapY -10, m_pImgLMotion->getFrameWidth() * 3, m_pImgLMotion->getFrameHeight() * 3);

		break;
	default:
		break;
	}
}

void enemy::render(HDC hdc)
{
	if (!m_bIsAlive)
		return;

	Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	switch (m_eKind)
	{
	case RIPPER:
		switch (m_mStatus.state)
		{
			case MonsterStatus::IDLE:
				if (m_bIsLeftSee)
				{
					m_pImgLMotion->frameRender(hdc, m_fMapX, m_fMapY,0,0,3);
				}
				else
				{
					m_pImgRMotion->frameRender(hdc, m_fMapX, m_fMapY, 11, 0, 3);
				}
				break;
			case MonsterStatus::CHASER:
				if (m_bIsLeftSee)
				{
					m_pImgLMotion->aniRender(hdc, m_fMapX, m_fMapY, m_aniL1, 3);
				}
				else
				{
					m_pImgRMotion->aniRender(hdc, m_fMapX, m_fMapY, m_aniR1, 3);
				}
				break;
			case MonsterStatus::ATTACK:
				if (m_bIsLeftSee)
				{
					m_pImgLMotion->aniRender(hdc, m_fMapX, m_fMapY, m_aniL2, 3);
				}
				else
				{
					m_pImgRMotion->aniRender(hdc, m_fMapX, m_fMapY, m_aniR2, 3);
				}

				break;
		default:
			break;
		}

		m_pMissileMgr->render(hdc);

		break;
	default:
		break;
	}
}

void enemy::move()
{

	switch (m_eKind)
	{
	case RIPPER:



		if (!m_bIsLeftSee)
		{
			if (m_bIsGround)
			{
				m_fAngle =  80.0f;
				m_aniR1->start();

			}
			else
			{
				m_fY -= m_fGravity;

				m_fAngle -= 5;
				if (270 < m_fAngle)
				{
					m_fAngle = 270.0f;
				}
				if (m_fAngle < -90)
				{
					m_fAngle = -90.0f;
				}
			}
		}
		else
		{
			if (m_bIsGround)
			{
				m_fAngle =  100.0f;
				m_aniL1->start();
			}
			else
			{
				m_fY -= m_fGravity;

				m_fAngle += 5;
				if (270 < m_fAngle)
				{
					m_fAngle = 270.0f;
				}
				if (m_fAngle < -90)
				{
					m_fAngle = -90.0f;
				}
			}
		}

		



		m_fX += cosf(PI / 180 * m_fAngle) * m_fSpeed;
		m_fY += -sinf(PI / 180 * m_fAngle) * m_fSpeed;




		break;
	default:
		break;
	}
}

void enemy::fire()
{

	if (m_bIsLeftSee)
	{
		if (!m_aniL2->getIsPlaying())
		{
			m_mStatus.state = MonsterStatus::CHASER;
			m_pMissileMgr->fire(m_fX, m_fY, PI, 10.0f,0);

		}
			
	}
	else
	{
		if (!m_aniR2->getIsPlaying())
		{
			m_mStatus.state = MonsterStatus::CHASER;
			m_pMissileMgr->fire(m_fX, m_fY, 0, 10.0f,1);

		}
	}



}

void enemy::mapchackCollision()
{
	for (int y = m_rc.top; y <= m_rc.bottom; y++)
	{
		COLORREF color = GetPixel(ROOMMANAGER->getCurrRoom()->getMemDCInfo()->hMemDC,
			m_fMapX + ROOMMANAGER->getCurrRoom()->getPosMap().x,
			y + ROOMMANAGER->getCurrRoom()->getPosMap().y);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);


		if (!(r == 0 && g == 88 && b == 24))
		{
			if (y > m_fMapY)
			{
				m_fY--;
			}
			else if ((y < m_fMapY))
			{
				m_fY++;
			}
		}


		if (y == m_rc.bottom)
		{
			y++;

			color = GetPixel(ROOMMANAGER->getCurrRoom()->getMemDCInfo()->hMemDC,
				m_fMapX + ROOMMANAGER->getCurrRoom()->getPosMap().x,
				y + ROOMMANAGER->getCurrRoom()->getPosMap().y);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (!(r == 0 && g == 88 && b == 24))
			{

				m_fY -= m_fGravity;
				m_bIsGround = true;
			}
			else
			{
				m_bIsGround = false;
			}
		}
	}
}
enemy::enemy()
{
}


enemy::~enemy()
{
}
