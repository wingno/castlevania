#include "stdafx.h"
#include "sanger.h"
#include "animation.h"
#include "progressBar.h"
#include "battleScene.h"
#include "slash.h"
#include "magic.h"
#include "missileManager.h"

#define BOSS_WIDTH 50
#define BOSS_HEIGHT 50

HRESULT sanger::init()
{
	m_imgIdle = IMAGEMANAGER->addImage("image/bossidle.bmp", "image/bossidle.bmp", 146, 91, true, RGB(255, 0, 255));
	m_imgBigSlice = IMAGEMANAGER->addImage("bigSlice", "image/bigSlice.bmp", 260, 251,2,1, true, RGB(255, 0, 255));
	m_imgCharge = IMAGEMANAGER->addImage("charge", "image/charge.bmp", 600, 90,4,1, true, RGB(255, 0, 255)); 
	m_imgSetting= IMAGEMANAGER->addImage("setting", "image/setting.bmp", 600, 144,2,1, true, RGB(255, 0, 255));
	m_imgSlice= IMAGEMANAGER->addImage("slice", "image/slice.bmp", 1000, 90,4,1, true, RGB(255, 0, 255)); 
	
	m_pAni_1 = new animation;
	m_pAni_1->init(m_imgBigSlice->getWidth(), m_imgBigSlice->getHeight(), m_imgBigSlice->getFrameWidth(), m_imgBigSlice->getFrameHeight());
	m_pAni_1->setPlayFrame(0, 2, false);
	m_pAni_1->setFPS(10);

	m_pAni_2 = new animation;
	m_pAni_2->init(m_imgCharge->getWidth(), m_imgCharge->getHeight(), m_imgCharge->getFrameWidth(), m_imgCharge->getFrameHeight());
	m_pAni_2->setPlayFrame(0, 4, false);
	m_pAni_2->setFPS(1);

	m_pAni_3 = new animation;
	m_pAni_3->init(m_imgSetting->getWidth(), m_imgSetting->getHeight(), m_imgSetting->getFrameWidth(), m_imgSetting->getFrameHeight());
	m_pAni_3->setPlayFrame(0, 2, false);
	m_pAni_3->setFPS(1);

	m_pAni_4 = new animation;
	m_pAni_4->init(m_imgSlice->getWidth(), m_imgSlice->getHeight(), m_imgSlice->getFrameWidth(), m_imgSlice->getFrameHeight());
	m_pAni_4->setPlayFrame(0, 4, false);
	m_pAni_4->setFPS(5);

	m_bossState = BOSSSTART;

	m_pHPBar = new progressBar;
	m_pHPBar->init();

	m_pslash = new slash;
	m_pslash->init();

	m_pMagic = new magic;
	m_pMagic->init();

	m_pMissileMgr = new missileManager;
	m_pMissileMgr->init("image/bullet.bmp", 200.0f, 10);

	m_nCurrHP = 0;
	m_nMaxHP = 500;

	m_nCoolTime = 0;

	m_nMissileNum = 0;

	m_fdeadCount=0;
	m_fX = WINSIZEX +50;// -m_img->getWidth() / 2;
	m_fY = WINSIZEY / 2;// -m_img->getHeight() / 2 + 200;

	m_bIsAlive = false;
	m_bBigSlice = false;

	return S_OK;
}

void sanger::release()
{
	SAFE_DELETE(m_pAni_1);
	SAFE_DELETE(m_pAni_2);
	SAFE_DELETE(m_pAni_3);
	SAFE_DELETE(m_pAni_4);

	SAFE_DELETE(m_pHPBar);
	SAFE_DELETE(m_pslash);
}

void sanger::update()
{
	if (m_pslash->getIsAlive())
	{
		m_pslash->update();
	}

	if (m_pMagic->getIsAlive())
	{
		m_pMagic->update();
	}

		m_pMissileMgr->update();
	

	if (m_bIsAlive == false)
	{
		return;
	}
	
	if (m_bossState == BOSSDEAD)
	{
		if (m_fdeadCount <= 100)
		{
			m_fdeadCount += 3;
		}
		else
		{
			m_fdeadCount = 100;
			m_bIsAlive = false;
			m_pbattleScene->setIsEndding(true);

		}
		return;
	}

	if (m_bossState == BOSSSTART)
	{
		if (m_fX <0)
			m_pAni_1->start();

		m_fX -= 3.0f;

		m_rc = RectMakeCenter(m_fX, m_fY,
			BOSS_WIDTH, BOSS_HEIGHT);


		if (m_fX < WINSIZEX- 200)
		{
			m_bossState = BOSSIDLE;
		}


		if (m_nMaxHP > m_nCurrHP)
		{
			m_nCurrHP += 8;
		}
		if (m_nCurrHP>m_nMaxHP)
		{
			m_nCurrHP = m_nMaxHP;
		}


		m_pHPBar->setGauge(m_nCurrHP, m_nMaxHP);
		return;
	}

	








	m_rc = RectMakeCenter(m_fX, m_fY,
		BOSS_WIDTH, BOSS_HEIGHT);

	switch (m_bossState)
	{
	case BOSSIDLE:
		m_nMissileNum = 0;
		if (m_pslash->getIsAlive())
		{
			if (m_fY > WINSIZEY / 2)
			{
				m_fY-=5;
			}
			break;
		}

		if (m_nCoolTime < 200)
		{
			m_nCoolTime++;
		}
		else
		{
			m_nCoolTime = 0;

			int ranNum= 2;
			if (m_bBigSlice)
			{
				ranNum = 1;
			}

			switch (ranNum)
			{
			case 0:
				m_bossState = BOSSSETTING;
				m_pAni_3->start();
				break;
			case 1:
				m_fY -= 3.0f;
				m_bBigSlice = true;
				if (m_fY < 0)
				{
					m_bossState = BOSSBIGSLICE;
					m_pAni_1->start();

				}
				else
				{
					m_nCoolTime = 210;
					
				}

				break;
			case 2:
   				m_bossState = BOSSCHARGE;
				m_pAni_2->start();
				m_pMagic->setIsAlive(true);
		
				break;

			default:
				break;
			}
		}
		break;
	case BOSSBIGSLICE:
		m_bBigSlice = false;
		m_fY += 10.0f;

		if (m_fY > WINSIZEY)
		{
			m_pslash->setIsAlive(true);
			for (int i = 0; i < 4; i++)
			{
				m_pslash->getRc()[i].left = WINSIZEX - 500;
				m_pslash->getRc()[i].right = m_pslash->getRc()[i].left +288;
				m_pslash->getRcHP()[i] = 30;
			}

			m_bossState = BOSSIDLE;

		}




		m_pAni_1->frameUpdate(TIMEMANAGER->getElapsedTime());
		break;
	case BOSSCHARGE:

		
		
		
		if (m_pAni_2->getNowPlayIdx()!=1)
		{
			m_pAni_2->frameUpdate(TIMEMANAGER->getElapsedTime());

			
		}
		else
		{
			if (m_pMagic->getIsAlive()==false)
			{
				m_pAni_2->setNowPlayIdx(2);
				m_pMagic->getMissileMgr()->release();
				m_pMagic->setMissileMgr(new missileManager);
				m_pMagic->getMissileMgr()->init("image/bullet.bmp", 200.0f, 10);

			}
		}

		if (m_pAni_2->getNowPlayIdx() >= 3)
		{
			if (m_nMissileNum<100&&RANDOM->getInt(4)==1)
			{
				//m_pMissileMgr->fire(m_fX - 80, m_fY, RANDOM->getFromFloatTo(135.0f, 225.0f)*(PI/180) , 3.0f);
				m_pMissileMgr->fire(m_fX - 80, m_fY, RANDOM->getFromFloatTo(0.0f, 360.0f)*(PI / 180), 3.0f);
				m_nMissileNum++;
			}
			else if (m_nMissileNum >= 100)
			{
				m_bossState = BOSSIDLE;
				m_nMissileNum = 0;
			}
		}
		
		break;
	case BOSSSETTING:
		if (m_pAni_3->getIsPlaying() == false)
		{
			m_bossState = BOSSSLICE;
			m_pAni_4->start();
			
		}
		else
		{
			m_fX += 3.0f;
		}

		m_pAni_3->frameUpdate(TIMEMANAGER->getElapsedTime());
		break;
	case BOSSSLICE:
		m_fX -= 30.0f;

		if (m_fX < 0)
		{
			g_mainGame.setIsSlice(true);

			if (m_fX < -600)
			{
				g_mainGame.setIsSlice(false);
				m_fX = WINSIZEX - 200;
				m_bossState = BOSSIDLE;
			}
		}


		m_pAni_4->frameUpdate(TIMEMANAGER->getElapsedTime());
		break;
	default:
		break;
	}




	m_pHPBar->setGauge(m_nCurrHP, m_nMaxHP);

	if (m_nCurrHP <= 0)
	{
		m_bossState = BOSSDEAD;
	}


}

void sanger::render(HDC hdc)
{
	if (m_pslash->getIsAlive())
	{
		m_pslash->render(hdc);
	}

	if (m_pMagic->getIsAlive())
	{
		m_pMagic->render(hdc);
	}

	m_pMissileMgr->render(hdc);


	if (m_bIsAlive == false)
	{
		return;
	}

	//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	switch (m_bossState)
	{
	case BOSSBIGSLICE:
		m_imgBigSlice->aniRender(hdc, m_fX - m_imgBigSlice->getFrameWidth() / 2, m_fY - m_imgBigSlice->getFrameHeight(), m_pAni_1);
		break;
	case BOSSCHARGE:
		m_imgCharge->aniRender(hdc, m_fX - m_imgCharge->getFrameWidth() / 2, m_fY - m_imgCharge->getFrameHeight()+40, m_pAni_2);
		break;
	case BOSSSETTING:
		m_imgSetting->aniRender(hdc, m_fX - m_imgSetting->getFrameWidth() / 2, m_fY - m_imgSetting->getFrameHeight()+30, m_pAni_3);
		break;
	case BOSSSLICE:
		m_imgSlice->aniRender(hdc, m_fX - m_imgSlice->getFrameWidth() / 2, m_fY - m_imgSlice->getFrameHeight(), m_pAni_4);
		break;
	case BOSSSTART:
		m_imgSlice->frameRender(hdc, m_fX - m_imgSlice->getFrameWidth() / 2, m_fY - m_imgSlice->getFrameHeight() / 2,3,1);
		break;
	case BOSSIDLE:
		m_imgIdle->render(hdc, m_fX - m_imgIdle->getWidth() / 2, m_fY - m_imgIdle->getHeight() / 2);
		break;
	default:
		break;
	}




	m_pHPBar->render(hdc);
}

void sanger::damaged(int damage)
{
  	m_nCurrHP -= damage;
	if (m_nCurrHP <= 0)
	{
		m_nCurrHP = 0;


	}
}

sanger::sanger()
{
}


sanger::~sanger()
{
}
