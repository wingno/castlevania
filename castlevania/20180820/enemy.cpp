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

	m_eKind = eKind;


	switch (m_eKind)
	{
	case RIPPER:

		ripperInit(position, eKind);


		break;
	case AXE_ARMOR:
		axeArmorInit(position, eKind);
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









	switch (m_eKind)
	{
		case RIPPER:
			ripperUpdate();


		break;
		case AXE_ARMOR:
			axeArmorUpdate();
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
		ripperRender(hdc);
		break;
	case AXE_ARMOR:
		axeArmorRender(hdc);
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
		ripperMove();

		break;
	case AXE_ARMOR:
		if (m_bIsLeftSee)
		{
			m_fX--;
			if (!m_aniL1->getIsPlaying())
				m_aniL1->start();

		}
		else
		{
			m_fX++;
			if (!m_aniL1->getIsPlaying())
				m_aniL1->start();
		}
		break;
	default:
		break;
	}
}

void enemy::fire()
{


	switch (m_eKind)
	{
		case RIPPER:
			if (m_bIsLeftSee)
			{
				if (!m_aniL2->getIsPlaying())
				{
					m_mStatus.state = MonsterStatus::CHASER;
					m_pMissileMgr->fire(m_fX, m_fY, PI, 10.0f, 0);
				}

			}
			else
			{
				if (!m_aniR2->getIsPlaying())
				{
					m_mStatus.state = MonsterStatus::CHASER;
					m_pMissileMgr->fire(m_fX, m_fY, 0, 10.0f, 1);

				}
			}



			break;
		case AXE_ARMOR:
			if (m_bIsLeftSee)
			{
				if (!m_aniL2->getIsPlaying())
				{
					
					m_pMissileMgr->fire(m_fX, m_fY, PI, 10.0f, 3);
				}

			}
			else
			{
				if (!m_aniR2->getIsPlaying())
				{

					m_pMissileMgr->fire(m_fX, m_fY, 0, 10.0f, 3);

				}
			}

			break;
		default:
			break;
	}




}

void enemy::ripperMapchackCollision()
{

	for (int x = m_rc.left; x < m_rc.right; x++)
	{
		COLORREF color = GetPixel(ROOMMANAGER->getCurrRoom()->getMemDCInfo()->hMemDC,
			x + ROOMMANAGER->getCurrRoom()->getPosMap().x,
			m_fMapY-60 + ROOMMANAGER->getCurrRoom()->getPosMap().y);

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

	m_fMapX = m_fX - ROOMMANAGER->getCurrRoom()->getPosMap().x;
	m_fMapY = m_fY - ROOMMANAGER->getCurrRoom()->getPosMap().y;

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
				//if(m_fY>WINSIZEX/2)
				m_fY--;
			}
			else if ((y < m_fMapY))
			{
				//if (m_fY < WINSIZEX / 2)
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
void enemy::axeAromorMapchackCollision()
{
	for (int x = m_rc.left; x < m_rc.right; x++)
	{
		COLORREF color = GetPixel(ROOMMANAGER->getCurrRoom()->getMemDCInfo()->hMemDC,
			x + ROOMMANAGER->getCurrRoom()->getPosMap().x,
			m_fMapY - 60 + ROOMMANAGER->getCurrRoom()->getPosMap().y);

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

	m_fMapX = m_fX - ROOMMANAGER->getCurrRoom()->getPosMap().x;
	m_fMapY = m_fY - ROOMMANAGER->getCurrRoom()->getPosMap().y;

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
			//if (y > m_fMapY+60)
			//{
			//	//if(m_fY>WINSIZEX/2)
			//	m_fY= y- ((m_pImgLMotion->getFrameHeight() * 3) - 60)/2;

			//	//m_rc = RectMakeCenter(m_fMapX, m_fMapY, m_pImgLMotion->getFrameWidth(), (m_pImgLMotion->getFrameHeight() * 3) - 60);
			//}
			//else if ((y < m_fMapY+60))
			//{
			//	//if (m_fY < WINSIZEX / 2)
			//	m_fY++;
			//}
			m_fY = y - ((m_pImgLMotion->getFrameHeight() * 3) - 140);
			break;

		}




		//if (y == m_rc.bottom)
		//{
		//	y++;

		//	color = GetPixel(ROOMMANAGER->getCurrRoom()->getMemDCInfo()->hMemDC,
		//		m_fMapX + ROOMMANAGER->getCurrRoom()->getPosMap().x,
		//		y + ROOMMANAGER->getCurrRoom()->getPosMap().y);

		//	r = GetRValue(color);
		//	g = GetGValue(color);
		//	b = GetBValue(color);

		//	if (!(r == 0 && g == 88 && b == 24))
		//	{
		//		m_fY -= m_fGravity;
		//		m_bIsGround = true;
		//	}
		//	else
		//	{
		//		m_bIsGround = false;
		//	}
		//}
	}

}
void enemy::ripperInit(POINT position, EnemyKind eKind)
{
	m_mStatus = { "����", 20,0,20,20,0,0,10,MonsterStatus::IDLE };
	m_pImgLMotion = IMAGEMANAGER->addImage("image/RipperL.bmp", "image/RipperL.bmp", 192, 16, 12, 1, true, RGB(96, 96, 128));
	m_pImgRMotion = IMAGEMANAGER->addImage("image/RipperR.bmp", "image/RipperR.bmp", 192, 16, 12, 1, true, RGB(96, 96, 128));
	m_rc = RectMake(position.x, position.y, m_pImgLMotion->getFrameWidth() * 3, m_pImgLMotion->getFrameHeight() * 3);

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

}
void enemy::ripperUpdate()
{
	float elapsedTime = TIMEMANAGER->getElapsedTime();

	m_aniL1->frameUpdate(elapsedTime);
	m_aniR1->frameUpdate(elapsedTime);
	m_aniL2->frameUpdate(elapsedTime);
	m_aniR2->frameUpdate(elapsedTime);


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

			if (RANDOM->getInt(100) == 1)
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


	m_fMapX = m_fX - ROOMMANAGER->getCurrRoom()->getPosMap().x;
	m_fMapY = m_fY - ROOMMANAGER->getCurrRoom()->getPosMap().y;
	ripperMapchackCollision();
	m_rc = RectMake(m_fMapX, m_fMapY - 10, m_pImgLMotion->getFrameWidth() * 3, m_pImgLMotion->getFrameHeight() * 3);
}

void enemy::ripperMove()
{


	if (!m_bIsLeftSee)
	{
		if (m_bIsGround)
		{
			m_fAngle = 80.0f;
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
			m_fAngle = 100.0f;
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
}

void enemy::ripperRender(HDC hdc)
{
	switch (m_mStatus.state)
	{
	case MonsterStatus::IDLE:
		if (m_bIsLeftSee)
		{
			m_pImgLMotion->frameRender(hdc, m_fMapX, m_fMapY, 0, 0, 3);
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
			if (m_aniL2->getNowPlayFrame() == 9)
			{
				m_pImgLMotion->render(hdc, m_fMapX - 8 * 3, m_fMapY - 4 * 3, 176, 0, 16, 8, 3);
			}
			else if ((m_aniL2->getNowPlayFrame() == 10))
			{
				m_pImgLMotion->render(hdc, m_fMapX - 8 * 3, m_fMapY - 4 * 3, 176, 8, 16, 8, 3);
			}

		}
		else
		{
			m_pImgRMotion->aniRender(hdc, m_fMapX, m_fMapY, m_aniR2, 3);
			if (m_aniR2->getNowPlayFrame() == 2)
			{
				m_pImgRMotion->render(hdc, m_fMapX - 8 * 3, m_fMapY - 4 * 3, 0, 0, 16, 8, 3);
			}
			else if ((m_aniR2->getNowPlayFrame() == 1))
			{
				m_pImgRMotion->render(hdc, m_fMapX - 8 * 3, m_fMapY - 4 * 3, 0, 8, 16, 8, 3);
			}
		}

		break;
	default:
		break;
	}

	m_pMissileMgr->render(hdc);
}

void enemy::axeArmorInit(POINT position, EnemyKind eKind)
{

	m_mStatus = { "�����Ƹ�", 50,10,50,50,0,0,30,MonsterStatus::IDLE };
	m_pImgLMotion = IMAGEMANAGER->addImage("image/axeArmorL.bmp", "image/axeArmorL.bmp", 80, 1610, 1, 23, true, RGB(84, 109, 142));
	m_pImgRMotion = IMAGEMANAGER->addImage("image/axeArmorR.bmp", "image/axeArmorR.bmp", 80, 1610, 1, 23, true, RGB(84, 109, 142));
	m_rc = RectMake(position.x, position.y, m_pImgLMotion->getFrameWidth() * 3, m_pImgLMotion->getFrameHeight() * 3);
	m_chaserRc = RectMakeCenter(m_fMapX, m_fMapY, AXE_ARMOR_RANGE, (m_pImgLMotion->getFrameHeight() * 3) - 60);
	m_fSpeed = 3.0f;



	m_fGravity = 6.0f;

	m_fElapsedTime = 0;


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

	m_pMissileMgr = new missileManager;
	m_pMissileMgr->init();

	//m_pLAni1 = new int[5];
	//m_pLAni1[0] = 0;
	//m_pLAni1[1] = 4;
	//m_pLAni1[2] = 5;
	//m_pLAni1[3] = 6;
	//m_pLAni1[4] = 7;


	m_aniL1 = new animation;
	m_aniL1->init(80, 1610, 80, 70);
	m_aniL1->setPlayFrame(0,6,false,true);
	m_aniL1->setFPS(10);

	//m_pLAni2 = new int[3];
	//m_pLAni2[0] = 8;
	//m_pLAni2[1] = 9;
	//m_pLAni2[2] = 10;

	//m_aniL2 = new animation;
	//m_aniL2->init(192, 16, 16, 16);
	//m_aniL2->setPlayFrame(m_pLAni2, 3);
	//m_aniL2->setFPS(5);

	
}
void enemy::axeArmorUpdate()
{

	if (m_pPlayer->getFx() > m_fMapX)
	{
		m_bIsLeftSee = false;
	}
	else
	{
		m_bIsLeftSee = true;
	}


	

	RECT rc;
	switch (m_mStatus.state)
	{
	case MonsterStatus::IDLE:
		if (WINSIZEX > m_fMapX && m_fMapX > 0 && WINSIZEY > m_fMapY &&m_fMapY > 0)
		{

			if (IntersectRect(&rc, &m_pPlayer->getRc(), &m_chaserRc))
			{
				m_mStatus.state = MonsterStatus::CHASER;
				m_aniL1->start();


			}
			

		}
		break;
	case MonsterStatus::CHASER:

		m_aniL1->frameUpdate(TIMEMANAGER->getElapsedTime());

		if (IntersectRect(&rc, &m_pPlayer->getRc(), &m_chaserRc))
		{
			m_aniL1->stop();
			if (m_fElapsedTime > 2)
			{
				m_mStatus.state = MonsterStatus::ATTACK;
				m_fElapsedTime = 0;
				

			}
			
		}
		else
		{

			if (m_fMapX<0 || m_fMapX>WINSIZEX)
			{
				m_mStatus.state = MonsterStatus::IDLE;
				m_fElapsedTime = 0;
				m_aniL1->stop();
			}
			else
			{
				move();

			}
			


		}
		m_fElapsedTime += TIMEMANAGER->getElapsedTime();



		break;
	case MonsterStatus::ATTACK:

		fire();
		break;


	default:
		break;
	}


	m_pMissileMgr->update();


	m_fMapX = m_fX - ROOMMANAGER->getCurrRoom()->getPosMap().x;
	m_fMapY = m_fY - ROOMMANAGER->getCurrRoom()->getPosMap().y;
	axeAromorMapchackCollision();
	m_rc = RectMakeCenter(m_fMapX, m_fMapY, m_pImgLMotion->getFrameWidth(), (m_pImgLMotion->getFrameHeight() * 3)-60);

	m_chaserRc= RectMakeCenter(m_fMapX, m_fMapY, AXE_ARMOR_RANGE, (m_pImgLMotion->getFrameHeight() * 3) - 60);
}
void enemy::axeArmorRender(HDC hdc)
{
	//Rectangle(hdc, m_chaserRc.left, m_chaserRc.top, m_chaserRc.right, m_chaserRc.bottom);
	switch (m_mStatus.state)
	{
	case MonsterStatus::IDLE:
		if (m_bIsLeftSee)
		{
			m_pImgLMotion->frameRender(hdc, m_fMapX- m_pImgLMotion->getFrameWidth()*1.5, m_fMapY- (m_pImgLMotion->getFrameHeight() * 3)+65, 0, 0, 3);
		}
		else
		{
			m_pImgRMotion->frameRender(hdc, m_fMapX - m_pImgLMotion->getFrameWidth()*1.5, m_fMapY - (m_pImgLMotion->getFrameHeight() * 3)+65 , 0, 0, 3);
		}
		
		break;
	case MonsterStatus::CHASER:
		if (m_bIsLeftSee)
		{
			m_pImgLMotion->aniRender(hdc, m_fMapX - m_pImgLMotion->getFrameWidth()*1.5, m_fMapY - (m_pImgLMotion->getFrameHeight() * 3) + 65, m_aniL1, 3);
		}
		else
		{
			m_pImgRMotion->aniRender(hdc, m_fMapX - m_pImgLMotion->getFrameWidth()*1.5, m_fMapY - (m_pImgLMotion->getFrameHeight() * 3) + 65, m_aniL1, 3);
		}
		break;
	//case MonsterStatus::ATTACK:
	//	if (m_bIsLeftSee)
	//	{
	//		m_pImgLMotion->aniRender(hdc, m_fMapX, m_fMapY, m_aniL2, 3);
	//		if (m_aniL2->getNowPlayFrame() == 9)
	//		{
	//			m_pImgLMotion->render(hdc, m_fMapX - 8 * 3, m_fMapY - 4 * 3, 176, 0, 16, 8, 3);
	//		}
	//		else if ((m_aniL2->getNowPlayFrame() == 10))
	//		{
	//			m_pImgLMotion->render(hdc, m_fMapX - 8 * 3, m_fMapY - 4 * 3, 176, 8, 16, 8, 3);
	//		}

	//	}
	//	else
	//	{
	//		m_pImgRMotion->aniRender(hdc, m_fMapX, m_fMapY, m_aniR2, 3);
	//		if (m_aniR2->getNowPlayFrame() == 2)
	//		{
	//			m_pImgRMotion->render(hdc, m_fMapX - 8 * 3, m_fMapY - 4 * 3, 0, 0, 16, 8, 3);
	//		}
	//		else if ((m_aniR2->getNowPlayFrame() == 1))
	//		{
	//			m_pImgRMotion->render(hdc, m_fMapX - 8 * 3, m_fMapY - 4 * 3, 0, 8, 16, 8, 3);
	//		}
	//	}

		break;
	default:
		break;
	}
}
enemy::enemy()
{
}


enemy::~enemy()
{
}
