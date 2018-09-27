#include "stdafx.h"
#include "player.h"
#include "missileManager.h"
#include "progressBar.h"
#include "animation.h"
#include "battleScene.h"


#define PLAYER_WIDTH 30
#define PLAYER_HEIGHT 30


HRESULT player::init()
{
	

	m_img = IMAGEMANAGER->addImage("idle", "image/idle.bmp",68, 79, true, RGB(255, 0, 255));
	m_imgFront = IMAGEMANAGER->addImage("front", "image/front.bmp", 444, 85, true, RGB(255, 0, 255));
	m_imgBack = IMAGEMANAGER->addImage("back", "image/back.bmp", 180, 80, true, RGB(255, 0, 255));

	m_fSpeed = 5.0f;
	m_fX = -50;// -m_img->getWidth() / 2;
	m_fY = WINSIZEY / 2 ;// -m_img->getHeight() / 2 + 200;

	m_rc = RectMakeCenter(m_fX, m_fY, PLAYER_WIDTH, PLAYER_HEIGHT);

	m_pAni_1 = new animation;
	m_pAni_1->init(m_imgFront->getWidth(), m_imgFront->getHeight(),74,85);
	m_pAni_1->setPlayFrame(0,6,true);
	m_pAni_1->setFPS(10);

	m_pAni_2 = new animation;
	m_pAni_2->init(m_imgBack->getWidth(), m_imgBack->getHeight(), 60, 80);
	m_pAni_2->setPlayFrame(0, 3, true);
	m_pAni_2->setFPS(10);

	m_shipState = START;

	m_pMissileMgr = new missileManager;
	m_pMissileMgr->init();

	// Ã¼·Â¹Ù
	m_pHPBar = new progressBar;
	m_pHPBar->init(m_fX - (m_img->getWidth() / 2),
		m_fY - (m_img->getHeight() / 2) - 10,
		164, 318);

	m_nCurrHP = 0;
	m_nMaxHP = 200;

	m_fdeadCount = 0;

	return S_OK;
}

void player::release()
{
	SAFE_DELETE(m_pAni_1);
	SAFE_DELETE(m_pAni_2);
	SAFE_DELETE(m_pMissileMgr);
	//SAFE_DELETE(m_pActionMissile);
	delete m_pHPBar;
	//delete m_pMissile;
}

void player::update()
{
	m_pMissileMgr->update();
	m_pHPBar->setGauge(m_nCurrHP, m_nMaxHP);
	if (m_shipState == DEAD)
	{
		if (m_fdeadCount <= 100)
		{
			m_fdeadCount += 1;
		}
		else
		{
			m_fdeadCount = 100;
			m_pbattleScene->setIsGameover(true);
			
		}
		return;
	}

	if (m_shipState == START)
	{
		if(m_fX <0)
			m_pAni_1->start();

		m_fX += m_fSpeed;

		m_rc = RectMakeCenter(m_fX, m_fY,
			PLAYER_WIDTH, PLAYER_HEIGHT);


		if (m_fX > 200)
		{
			m_shipState = IDLE;
		}

		m_pAni_1->frameUpdate(TIMEMANAGER->getElapsedTime());

		if (m_nMaxHP > m_nCurrHP)
		{
			m_nCurrHP+=5;
		}
		if(m_nCurrHP>m_nMaxHP)
		{
			m_nCurrHP= m_nMaxHP;
		}
		

		m_pHPBar->setGauge(m_nCurrHP, m_nMaxHP);
		return;
	}

	m_shipState = IDLE;

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (m_pMissileMgr)
			m_pMissileMgr->fire(m_fX, m_fY);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		m_shipState = BACK;
		m_pAni_2->start();
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT)
		&& (m_fX > 0))
	{
		//m_img->setX(m_img->getX() - m_fSpeed);
		m_fX -= m_fSpeed;
		m_shipState = BACK;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT)
		&& (m_fX + m_img->getWidth() < WINSIZEX))
	{
		//m_img->setX(m_img->getX() + m_fSpeed);
		m_fX += m_fSpeed;
		m_shipState = FRONT;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		m_shipState = FRONT;
		m_pAni_1->start();
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP)
		&& (m_fY > 0))
	{
		//m_img->setY(m_img->getY() - m_fSpeed);
		m_fY -= m_fSpeed;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN) && (m_fY + m_img->getHeight() < WINSIZEY))
	{
		//m_img->setY(m_img->getY() + m_fSpeed);
		m_fY += m_fSpeed;
	}


	m_rc = RectMakeCenter(m_fX, m_fY, 
		PLAYER_WIDTH, PLAYER_HEIGHT);

	m_img->setX(m_fX);
	m_img->setY(m_fY);

	


	switch (m_shipState)
	{
	case IDLE:
		
		break;
	case FRONT:
		m_pAni_1->frameUpdate(TIMEMANAGER->getElapsedTime());
		break;
	case BACK:
		m_pAni_2->frameUpdate(TIMEMANAGER->getElapsedTime());
		break;
	default:
		break;
	}



	if (m_nCurrHP <= 0)
	{
		m_shipState = DEAD;
	}


}

void player::render(HDC hdc)
{
	//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);

	//m_img->render(hdc, m_fX - m_img->getWidth() / 2, m_fY - m_img->getHeight() / 2);


	switch (m_shipState)
	{
	case IDLE:
		m_img->render(hdc, m_fX - m_img->getWidth() / 2, m_fY - m_img->getHeight() / 2);

		break;
	case START:
	case FRONT:
		m_imgFront->aniRender(hdc, m_fX - m_img->getWidth() / 2, m_fY - m_img->getHeight() / 2, m_pAni_1);
		break;
	case BACK:
		m_imgBack->aniRender(hdc, m_fX - m_img->getWidth() / 2, m_fY - m_img->getHeight() / 2, m_pAni_2);
		break;
	case DEAD:
		if(m_fdeadCount <=100)
			m_img->alphaRender(hdc, m_fX - m_img->getWidth() / 2, m_fY - m_img->getHeight() / 2, 100-m_fdeadCount);
		break;

	default:
		break;
	}

	//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);


	m_pHPBar->render(hdc);

	
	m_pMissileMgr->render(hdc);

}

void player::damaged(int damage)
{
	m_nCurrHP -= damage;
	if (m_nCurrHP <= 0)
	{
		m_nCurrHP = 0;


	}
}

void player::mapCollider()
{
	if (m_shipState == START)
	{
		return;
	}
	else
	{
		m_nCurrHP = 0;
	}
}

player::player()
{
}


player::~player()
{
}
