#include "stdafx.h"
#include "battleScene.h"
#include "player.h"
#include "enemyManager.h"
#include "missileManager.h"
#include "stage1.h"
#include "scoreBoard.h"
#include "sanger.h"
#include "slash.h"
#include "magic.h"


HRESULT battleScene::init()
{
	IMAGEMANAGER->addImage("enemy_missile_1", "image/bullet.bmp",
		21, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("image/invadermissile.bmp", "image/invadermissile.bmp", 236, 174, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("image/invaderbullet.bmp", "image/invaderbullet.bmp", 12, 11, true, RGB(255, 0, 255));

	m_bIsEndding = false;
	m_bIsGameover = false;

	m_pPlayer = new player;
	m_pPlayer->init();
	
	m_pPlayer->setBattleScene(this);

	m_pSanger = new sanger;
	m_pSanger->setBattleScene(this);
	m_pSanger->init();


	m_pEnemyMgr = new enemyManager;
	m_pEnemyMgr->init();

	m_pStage1 = new stage1;
	m_pStage1->setEnemyMgr(m_pEnemyMgr);
	m_pStage1->setPlayer(m_pPlayer);
	m_pStage1->setSanger(m_pSanger);
	m_pStage1->init();
	//m_pEnemyMgr->setEnemy(9, m_pPlayer,1);
	m_pScoreBoard = new scoreBoard;
	m_pScoreBoard->init();

	return S_OK;
}

void battleScene::release()
{
	SAFE_DELETE(m_pStage1);
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pScoreBoard);
	SAFE_DELETE(m_pSanger);

}

void battleScene::update()
{

	m_pStage1->update();

	m_pPlayer->update();

	m_pEnemyMgr->update();

	m_pSanger->update();

	m_pScoreBoard->update();

	mapchackCollision();

	checkCollision();

	if (m_bIsGameover)
	{
		SCENEMANAGER->changeScene("gameover");
	}
	if (m_bIsEndding)
	{
		SCENEMANAGER->changeScene("endding");
	}

}

void battleScene::render(HDC hdc)
{
	m_pStage1->render(hdc);

	m_pEnemyMgr->render(hdc);

	m_pPlayer->render(hdc);

	m_pSanger->render(hdc);

	m_pScoreBoard->render(hdc);

	//TIMEMANAGER->render(hdc);

	
}

void battleScene::mapchackCollision()
{
	//m_pStage1->getCollMap()->getMemDC();
	RECT* prc = m_pStage1->getColliderRect();

	for (int i = 0; i < 3; i++)
	{
		RECT rc;
		RECT playerRC= m_pPlayer->getRect();
		playerRC.left += m_pStage1->getMap().x;
		playerRC.right += m_pStage1->getMap().x;
		if (IntersectRect(&rc, &playerRC, &(prc[i])))
		{
			return;
		}
	}



	for (int y = m_pPlayer->getRect().top; y <= m_pPlayer->getRect().bottom; y++)
	{
		for (int x = m_pPlayer->getRect().left; x < m_pPlayer->getRect().right; x++)
		{


			COLORREF color = GetPixel(m_pStage1->getMemDCInfo()->hMemDC,(int)x + m_pStage1->getMap().x, y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);


			if (!(r == 63 && g == 72 && b == 204))
			{
		
				m_pPlayer->mapCollider();
				break;
			}
		}

	}

}


void battleScene::checkCollision()
{
	// 적 미사일과 플레이어 확인
	std::vector<enemy*> vEnemy = m_pEnemyMgr->getVecEnemy();
	std::vector<enemy*>::iterator iter;
	if (m_pSanger->getIsAlive() == false)
	{


		for (iter = vEnemy.begin(); iter != vEnemy.end(); iter++)
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
					IntersectRect(&rc, &m_pPlayer->getRect(), &(*iterMissile)->getRect()))
				{
					// 미사일 삭제
					(*iterMissile)->setIsFire(false);

					// 플레이어 HP 감소
					m_pPlayer->damaged((*iterMissile)->getDamage());

				}

				if ((*iterMissile)->getKind() == 1)
				{
					std::vector<missile*> vPMissile = m_pPlayer->getMissileMgr()->getVecMissile();
					std::vector<missile*>::iterator iterPMissile;
				
					for (iterPMissile = vPMissile.begin(); iterPMissile != vPMissile.end(); iterPMissile++)
					{
						RECT rc;
						if ((*iterMissile)->getIsFire() && (*iterPMissile)->getIsFire() &&
							IntersectRect(&rc, &(*iterPMissile)->getRect(), &(*iterMissile)->getRect()))
						{
								// 미사일 삭제
								(*iterMissile)->setIsFire(false);

								// 미사일 삭제
								(*iterPMissile)->setIsFire(false);
						}
					}

				}


			}



			std::vector<missile*> vPMissile = m_pPlayer->getMissileMgr()->getVecMissile();
			std::vector<missile*>::iterator iterPMissile;

			for (iterPMissile = vPMissile.begin(); iterPMissile != vPMissile.end(); iterPMissile++)
			{
				RECT rc;
				if ((*iter)->getIsAlive() && (*iterPMissile)->getIsFire() &&
					IntersectRect(&rc, &(*iterPMissile)->getRect(), &(*iter)->getRect()))
				{
					(*iter)->setIsAlive(false);

					(*iterPMissile)->setIsFire(false);

					g_mainGame.setScore(g_mainGame.getScore() + ((*iter)->getKind()*100));

					//EFFECTMANAGER->play("explosion1", rc.left, rc.top);


				}
			}



		}
	}
	else
	{

	
		std::vector<missile*> vPMissile = m_pPlayer->getMissileMgr()->getVecMissile();
		std::vector<missile*>::iterator iterPMissile;

		for (iterPMissile = vPMissile.begin(); iterPMissile != vPMissile.end(); iterPMissile++)
		{
			RECT rc;
			if (m_pSanger->getIsAlive() && (*iterPMissile)->getIsFire() &&
				IntersectRect(&rc, &(*iterPMissile)->getRect(), &m_pSanger->getRect()))
			{

				(*iterPMissile)->setIsFire(false);


				m_pSanger->damaged((*iterPMissile)->getDamage());
			}

			for (int i = 0; i < 4; i++)

			{
				if (m_pSanger->getSlash()->getIsAlive()&&
					m_pSanger->getSlash()->getRcHP()[i]>0 && (*iterPMissile)->getIsFire() &&
					IntersectRect(&rc, &(*iterPMissile)->getRect(), &m_pSanger->getSlash()->getRc()[i]))
				{

					(*iterPMissile)->setIsFire(false);


					m_pSanger->getSlash()->setRcHP(i, m_pSanger->getSlash()->getRcHP()[i] - 3);
				}

			}

		}


		RECT rc;
		if (m_pSanger->getBossState() == BOSSSLICE&&
			IntersectRect(&rc, &m_pPlayer->getRect(), &m_pSanger->getRect()))
		{
			m_pPlayer->damaged(200);
		}


		for (int i = 0; i < 4; i++)

		{
			if (m_pSanger->getSlash()->getIsAlive() && m_pSanger->getSlash()->getRcHP()[i] > 0 && 
				IntersectRect(&rc, &m_pPlayer->getRect(), &m_pSanger->getSlash()->getRc()[i]))
			{
				m_pPlayer->damaged(m_pSanger->getSlash()->getDamage());

				m_pSanger->getSlash()->setIsAlive(false);
			}
		}


		std::vector<missile*> vmagicMissile = m_pSanger->getMagic()->getMissileMgr()->getVecMissile();
		std::vector<missile*>::iterator iterMagicMissile;

		for (iterMagicMissile = vmagicMissile.begin();
			iterMagicMissile != vmagicMissile.end();
			iterMagicMissile++)
		{

			RECT rc;
			if ((*iterMagicMissile)->getIsFire() &&
				IntersectRect(&rc, &m_pPlayer->getRect(), &(*iterMagicMissile)->getRect()))
			{
				// 미사일 삭제
				(*iterMagicMissile)->setIsFire(false);

				// 플레이어 HP 감소
				m_pPlayer->damaged((*iterMagicMissile)->getDamage());

			}

		}

		std::vector<missile*> vBoSSMissile = m_pSanger->getMissileMgr()->getVecMissile();
		std::vector<missile*>::iterator iterBossMissile;

		for (iterBossMissile = vBoSSMissile.begin();
			iterBossMissile != vBoSSMissile.end();
			iterBossMissile++)
		{

			RECT rc;
			if ((*iterBossMissile)->getIsFire() &&
				IntersectRect(&rc, &m_pPlayer->getRect(), &(*iterBossMissile)->getRect()))
			{
				// 미사일 삭제
				(*iterBossMissile)->setIsFire(false);

				// 플레이어 HP 감소
				m_pPlayer->damaged((*iterBossMissile)->getDamage());

			}

		}




	}
	// 플레이어 미사일과 적 확인
}



battleScene::battleScene()
{
}


battleScene::~battleScene()
{
}
