#include "stdafx.h"
#include "battleScene.h"
#include "enemyManager.h"
#include "missileManager.h"
#include "selectScene.h"
#include "player.h"
#include "progressBar.h"
#include "room.h"


HRESULT battleScene::init()
{
	IMAGEMANAGER->addImage("background", "image/mapImage.bmp", WINSIZEX, WINSIZEY, false, 0);


	m_pPlayer = g_mainGame.getPlayer();


	//IMAGEMANAGER->addImage("enemy_missile_1", "image/bullet.bmp", 21, 21, true, RGB(255,0,255));

	m_bIsChangeScene = false;
	m_nAlphaNum = 0;


	m_progressBar = new progressBar;

	m_progressBar->init(0, 0,230,25);

	m_progressBar->setGauge(m_pPlayer->getState().curHP , m_pPlayer->getState().fullHP
					, m_pPlayer->getState().curMP, m_pPlayer->getState().fullMP);




	return S_OK;
}

void battleScene::release()
{


}

void battleScene::update()
{

	m_pPlayer->update();
	ROOMMANAGER->update();
	m_progressBar->setGauge(m_pPlayer->getState().curHP, m_pPlayer->getState().fullHP
		, m_pPlayer->getState().curMP, m_pPlayer->getState().fullMP);
	
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		m_bIsChangeScene = true;

	}

	if (m_bIsChangeScene)
	{


		if (m_nAlphaNum < 200)
		{
			m_nAlphaNum += 50;
		}
		else
		{
			SCENEMANAGER->changeScene("menu");
		}

	}
	checkCollision();
}

void battleScene::render(HDC hdc)
{
	//IMAGEMANAGER->findImage("background")->render(hdc, 0, 0);


	ROOMMANAGER->render(hdc);
	m_pPlayer->render(hdc);
	m_progressBar->render(hdc);
	if (m_bIsChangeScene)
	{
		IMAGEMANAGER->findImage("background")->alphaRender(hdc, m_nAlphaNum);

	}



}

void battleScene::checkCollision()
{
	std::vector<enemy*> vEnemy = ROOMMANAGER->getCurrRoom()->getEnemyMgr()->getVecEnemy();
	std::vector<enemy*>::iterator iter;
	for (iter = vEnemy.begin(); iter != vEnemy.end(); iter++)
	{
		if ((*iter)->getMissileMgr() != NULL)
		{
			std::vector<missile*> vMissile
				= (*iter)->getMissileMgr()->getVecMissile();
			std::vector<missile*>::iterator iterMissile;

			for (iterMissile = vMissile.begin();
				iterMissile != vMissile.end();
				iterMissile++)
			{

				RECT rc;
				if ((*iterMissile)->getIsFire() &&
					IntersectRect(&rc, &m_pPlayer->getRc(), &(*iterMissile)->getRect()))
				{
					int damage = (*iterMissile)->getDmg() - m_pPlayer->getState().curDef;

					if (damage < 1)
					{
						damage = 1;
					}

					if (m_pPlayer->getHitDivineC() == 100)
					{
						m_pPlayer->setHitDmg(damage);
						m_pPlayer->hitCollision(damage);
						

					}

					
					// 미사일 삭제




					//(*iterMissile)->setIsFire(false);



				}

				if ((*iterMissile)->getIsFire() && IntersectRect(&rc, &m_pPlayer->getIRC(), &(*iterMissile)->getRect()))
				{
					// 미사일 삭제
					(*iterMissile)->setIsFire(false);

				}





			}

		}




		RECT rc;
		if ((*iter)->getIsAlive() && 
			IntersectRect(&rc, &m_pPlayer->getIRC(), &(*iter)->getRc()))
		{
			//(*iter)->setIsAlive(false);

	
			int damage = m_pPlayer->getState().curAtt - (*iter)->getMStatus().curDef;

			if (damage < 1)
			{
				damage = 1;
			}

			if(!((*iter)->getIshit()))
				(*iter)->setHitDmg(damage);

		}

		
		if ((*iter)->getIsAlive() &&
			(IntersectRect(&rc, &m_pPlayer->getRc(), &(*iter)->getRc()) || IntersectRect(&rc, &m_pPlayer->getRc(), &(*iter)->getAttackRect()))                )
		{
			//(*iter)->setIsAlive(false);


			int damage = (*iter)->getMStatus().curAtt - m_pPlayer->getState().curDef;

			if (damage < 1)
			{
				damage = 1;
			}

			if (m_pPlayer->getHitDivineC() == 100)
			{
				m_pPlayer->setHitDmg(damage);
				m_pPlayer->hitCollision(damage);

			}

		}


	}


}






battleScene::battleScene()
{
}


battleScene::~battleScene()
{
}
