#include "stdafx.h"
#include "enemy.h"
#include "missileManager.h"

HRESULT enemy::init()
{
	m_nCount = 0;
	m_nCurrFrameX = 0;
	m_nCurrFrameY = 0;
	m_pImg = NULL;

	ZeroMemory(&m_rc, sizeof(m_rc));

	m_pMissileMgr = new missileManager;
	m_pMissileMgr->init("image/bullet.bmp", 200.0f, 10);
	m_nFireCount = 0;
	m_nRandFireCount = 10;
	m_fX = 0;
	m_fY = 0;

	return S_OK;
}

HRESULT enemy::init(const char * szFileName, POINT position)
{
	m_nCount = 0;
	m_nCurrFrameX = 0;
	m_nCurrFrameY = 0;
	std::string strFile = std::string(szFileName);
	m_pImg = IMAGEMANAGER->addImage(strFile, szFileName,
		530, 32, 10, 1, true, RGB(255, 0, 255));

	m_rc = RectMakeCenter(position.x, position.y,
		m_pImg->getFrameWidth(), m_pImg->getFrameHeight());

	m_pMissileMgr = new missileManager;
	m_pMissileMgr->init("image/bullet.bmp", 200.0f, 10);
	m_nFireCount = 0;
	m_nRandFireCount = 10;
	m_fX = position.x;
	m_fY = position.y;

	return S_OK;
}

HRESULT enemy::init(const char * szFileName, POINT position, POINT destinationPos,ENEMYKIND enemyKind)
{
	m_enemyKind = enemyKind;


	m_nCount = 0;
	m_nCurrFrameX = 0;
	m_nCurrFrameY = 0;
	std::string strFile = std::string(szFileName);
	m_pImg = IMAGEMANAGER->addImage(strFile, szFileName,
		530, 32, 10, 1, true, RGB(255, 0, 255));

	m_rc = RectMakeCenter(position.x, position.y,
		m_pImg->getFrameWidth(), m_pImg->getFrameHeight());

	m_pMissileMgr = new missileManager;
	m_pMissileMgr->init("image/bullet.bmp", 200.0f, 10);
	m_nFireCount = 0;
	m_nRandFireCount = 10;
	m_fX = position.x;
	m_fY = position.y;

	m_destinationX = destinationPos.x;
	m_destinationY = destinationPos.y;

	m_fangle = MY_UTIL::getAngle(m_fX, m_fY, m_destinationX, m_destinationY);

	m_fShootAngle = m_fangle;

	m_fdeDistance = MY_UTIL::getDistance(m_fX, m_fY, m_destinationX, m_destinationY);

	m_bIsAlive = true;


	return S_OK;
}

HRESULT enemy::init(POINT position, POINT destinationPos, ENEMYKIND enemyKind)
{


	m_enemyKind = enemyKind;


	m_nCount = 0;
	m_nCurrFrameX = 0;
	m_nCurrFrameY = 0;

	m_fX = position.x;
	m_fY = position.y;

	m_destinationX = destinationPos.x;
	m_destinationY = destinationPos.y;

	m_fangle = MY_UTIL::getAngle(m_fX, m_fY, m_destinationX, m_destinationY);
	m_fShootAngle = m_fangle;


	m_pMissileMgr = new missileManager;
	m_pMissileMgr->init("image/bullet.bmp", 200.0f, 10);
	m_nFireCount = 0;
	m_nRandFireCount = 100;



	switch (m_enemyKind)
	{
	case INVADERAIR:
		m_pImg = IMAGEMANAGER->addImage("image/invaderAir.bmp", "image/invaderAir.bmp", 111, 66, true, RGB(255, 0, 255));
		m_pMissileMgr->setTarget(m_pTarget);
		m_rc = RectMakeCenter(position.x, position.y,
			m_pImg->getWidth(), m_pImg->getHeight());
		break;
	case INVADERGROUND:
		m_pImg = IMAGEMANAGER->addImage("image/invaderGround.bmp", "image/invaderGround.bmp", 111, 74, true, RGB(255, 0, 255));
		m_fShootAngle = PI / 2 + PI / 4;
		m_rc = RectMakeCenter(position.x, position.y,
			m_pImg->getWidth(), m_pImg->getHeight());
		break;
	case ZAKU:
		m_pImg = IMAGEMANAGER->addImage("image/zaku.bmp", "image/zaku.bmp",150, 50,3,1, true, RGB(255, 0, 255));
		m_fShootAngle = PI;
		m_rc = RectMakeCenter(position.x, position.y, m_pImg->getFrameWidth(), m_pImg->getFrameHeight());
		break;
	case JUZAKU:
		m_pImg = IMAGEMANAGER->addImage("image/juzaku.bmp", "image/juzaku.bmp", 58, 50, 3, 1, true, RGB(255, 0, 255));
		m_rc = RectMakeCenter(position.x, position.y, m_pImg->getWidth(), m_pImg->getHeight());
		break;
	default:

		break;
	}

	






	m_fdeDistance = MY_UTIL::getDistance(m_fX, m_fY, m_destinationX, m_destinationY);

	m_bIsAlive = true;


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

	if (m_pMissileMgr)
		m_pMissileMgr->update();

	if (m_bIsAlive == false)
		return;


		move();

		fire();


	if (m_fX < 0 ||m_fY<0||m_fY>WINSIZEY)
	{
		m_bIsAlive = false;
	}



}

void enemy::render(HDC hdc)
{
	if (m_pMissileMgr)
	{
		m_pMissileMgr->render(hdc);
	}
	if (m_bIsAlive == false)
		return;



	if (m_pImg)
	{
		//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);



		switch (m_enemyKind)
		{
		case INVADERAIR:
			m_pImg->render(hdc, m_fX - m_pImg->getWidth() / 2, m_fY - m_pImg->getHeight() / 2);
			break;
		case INVADERGROUND:
			m_pImg->render(hdc, m_fX - m_pImg->getWidth() / 2, m_fY - m_pImg->getHeight() / 2);
			break;
		case ZAKU:
			int frameX;
			if (m_nFireCount<m_nRandFireCount-30)
			{
				frameX = 0;
			}
			else if (m_fShootAngle!=PI)
			{
				frameX = 1;
			}
			else
			{
				frameX = 2;
			}
			m_pImg->frameRender(hdc,m_fX - m_pImg->getFrameWidth() / 2, m_fY - m_pImg->getFrameHeight() / 2, frameX, 0);
			break;
		case JUZAKU:
			m_pImg->render(hdc, m_fX - m_pImg->getWidth() / 2, m_fY - m_pImg->getHeight() / 2);
			break;
		default:
			break;
		}


	}


}

void enemy::move()
{



	switch (m_enemyKind)
	{
	case INVADERAIR:
		m_fX += cosf(m_fangle)*2.0f;
		m_fY += -sinf(m_fangle)*2.0f;
		m_rc = RectMakeCenter(m_fX, m_fY,
			m_pImg->getWidth(), m_pImg->getHeight());
		break;
	case INVADERGROUND:
		m_fX += cosf(m_fangle)*2.0f;
		m_fY += -sinf(m_fangle)*2.0f;
		m_rc = RectMakeCenter(m_fX, m_fY,
			m_pImg->getWidth(), m_pImg->getHeight());
		break;
	case ZAKU:
		m_fX += cosf(m_fangle)*3.0f;
		m_fY += -sinf(m_fangle)*3.0f;
		m_rc = RectMakeCenter(m_fX, m_fY, m_pImg->getFrameWidth(), m_pImg->getFrameHeight());

		break;
	case JUZAKU:
		m_fX += cosf(m_fangle)*2.0f;
		m_fY += -sinf(m_fangle)*2.0f;
		m_rc = RectMakeCenter(m_fX, m_fY, m_pImg->getWidth(), m_pImg->getHeight());

		break;
	default:
		m_pImg = IMAGEMANAGER->addImage("image/zaku.bmp", "image/zaku.bmp",
			150, 50, 3, 1, true, RGB(255, 0, 255));
		m_rc = RectMakeCenter(m_fX, m_fY, m_pImg->getFrameWidth(), m_pImg->getFrameHeight());
		break;
	}
	

}

void enemy::fire()
{

	switch (m_enemyKind)
	{
	case INVADERAIR:
		++m_nFireCount;
		if (m_nFireCount % m_nRandFireCount == 0)
		{
			m_pMissileMgr->setTarget(m_pTarget);

			m_pMissileMgr->fire(m_fX, m_fY,
				m_fangle, 3,2);


			m_nFireCount = 0;
			m_nRandFireCount = RANDOM->getFromIntTo(50, 150);
		}
		break;
	case INVADERGROUND:
		++m_nFireCount;
		if (m_nFireCount % m_nRandFireCount == 0)
		{
			m_pMissileMgr->fire(m_fX, m_fY,
				m_fShootAngle, 3,1);

			m_nFireCount = 0;
			m_nRandFireCount = RANDOM->getFromIntTo(50, 150);

		}
		break;
	case ZAKU:
		++m_nFireCount;
		if (m_nFireCount % m_nRandFireCount == 0)
		{
			m_pMissileMgr->fire(m_fX, m_fY,
				m_fShootAngle, 5);

			m_nFireCount = 0;
			m_nRandFireCount = RANDOM->getFromIntTo(50, 150);

			if (m_fShootAngle != PI)
			{
				m_fShootAngle = PI;
			}
			else
			{
				m_fShootAngle = PI + PI / 8;
			}

		}
		break;

	case JUZAKU:
		++m_nFireCount;
		if (m_nFireCount % m_nRandFireCount == 0)
		{
			m_fShootAngle = PI - PI / 8;
			m_pMissileMgr->fire(m_fX, m_fY,
				m_fShootAngle, 4);

			m_fShootAngle = PI;
			m_pMissileMgr->fire(m_fX, m_fY,
				m_fShootAngle, 4);

			m_fShootAngle = PI + PI / 8;
			m_pMissileMgr->fire(m_fX, m_fY,
				m_fShootAngle, 4);

			m_nFireCount = 0;
			m_nRandFireCount = RANDOM->getFromIntTo(100, 200);

		}
		break;
	default:
		break;
	}



}


void enemy::reSetting(POINT position, POINT destinationPos, ENEMYKIND enemyKind)
{
	m_enemyKind = enemyKind;


	m_nCount = 0;
	m_nCurrFrameX = 0;
	m_nCurrFrameY = 0;

	m_fX = position.x;
  	m_fY = position.y;

	m_destinationX = destinationPos.x;
	m_destinationY = destinationPos.y;

	m_fangle = MY_UTIL::getAngle(m_fX, m_fY, m_destinationX, m_destinationY);
	m_fShootAngle = m_fangle;

	switch (m_enemyKind)
	{
	case INVADERAIR:
		m_pImg = IMAGEMANAGER->addImage("image/invaderAir.bmp", "image/invaderAir.bmp", 111, 66, true, RGB(255, 0, 255));
		m_pMissileMgr->setTarget(m_pTarget);
		m_rc = RectMakeCenter(position.x, position.y,
			m_pImg->getWidth(), m_pImg->getHeight());
		break;
	case INVADERGROUND:
		m_pImg = IMAGEMANAGER->addImage("image/invaderGround.bmp", "image/invaderGround.bmp", 111, 74, true, RGB(255, 0, 255));
		m_fShootAngle = PI / 2 + PI / 4;
		m_rc = RectMakeCenter(position.x, position.y,
			m_pImg->getWidth(), m_pImg->getHeight());
		break;
	case ZAKU:


		m_pImg = IMAGEMANAGER->addImage("image/zaku.bmp", "image/zaku.bmp",
			150, 50, 3, 1, true, RGB(255, 0, 255));
		m_pMissileMgr->init("image/bullet.bmp", 200.0f, 10);
		m_rc = RectMakeCenter(position.x, position.y,
			m_pImg->getFrameWidth(), m_pImg->getFrameHeight());
		m_fShootAngle = 180.0f;
		
		break;
	case JUZAKU:
		m_pImg = IMAGEMANAGER->addImage("image/juzaku.bmp", "image/juzaku.bmp", 58, 50, 3, 1, true, RGB(255, 0, 255));
		m_rc = RectMakeCenter(position.x, position.y, m_pImg->getWidth(), m_pImg->getHeight());
		break;
	default:
		break;
	}






	
	m_nFireCount = 0;
	m_nRandFireCount = 10;


	

	m_fdeDistance = MY_UTIL::getDistance(m_fX, m_fY, m_destinationX, m_destinationY);

	m_bIsAlive = true;


}

enemy::enemy()
{
}


enemy::~enemy()
{
}
