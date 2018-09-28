#include "stdafx.h"
#include "battleScene.h"
#include "spaceShip.h"
#include "enemyManager.h"
#include "missileManager.h"
#include "camel.h"
#include "selectScene.h"
#include "player.h"


HRESULT battleScene::init()
{
	//m_nstage = 1;
	//m_benemyIsSetting = false;


	IMAGEMANAGER->addImage("background", "image/background.bmp", WINSIZEX, WINSIZEY, false, 0);
	//IMAGEMANAGER->addImage("missile_1", "image/missile.bmp",
	//	26, 124, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("enemy_missile_1", "image/bullet.bmp",
	//	21, 21, true, RGB(255, 0, 255));

	//// 우주선
	//m_pSpaceShip = g_mainGame.getISpaceShip();

	//
	////m_pSpaceShip->init();

	////load
	//vector<int> vec;
	//vec = TXTDATA->txtLoadInt("stage/stage1.txt");
	//// 적
	//m_pEnemyMgr = new enemyManager;
	//m_pEnemyMgr->init();
	//m_pEnemyMgr->setEnemy(vec, m_nstage);
	//m_pEnemyMgr->setTarget(m_pSpaceShip);

	//// 낙타 애니메이션 테스트
	//m_pCamel = new camel;
	//m_pCamel->init();

	//*m_pscore =  0;

	m_pPlayer = new player;
	m_pPlayer->init();



	return S_OK;
}

void battleScene::release()
{
	/*m_pCamel->release();

	SAFE_DELETE(m_pCamel);
	SAFE_DELETE(m_pSpaceShip);
	g_mainGame.setISpaceShip(NULL);
	SAFE_DELETE(m_pEnemyMgr);*/

	SAFE_DELETE(m_pPlayer);
}

void battleScene::update()
{

	m_pPlayer->update();

	//if (m_pEnemyMgr->getIsSetting())
	//{
	//	m_benemyIsSetting = true;
	//	m_pSpaceShip->update();
	// 주석테스트

	//}
	//else
	//{
	//	m_pSpaceShip->getMissileMgr()->release();
	//}

	//m_pEnemyMgr->update();


	//if (m_pCamel)
	//{
	//	m_pCamel->update();
	//}


	//checkCollision();

	//EFFECTMANAGER->update();


	//if (m_pEnemyMgr->getisAllClear())
	//{
	//	vector<int> vec;
	//	vec = TXTDATA->txtLoadInt("stage/stage2.txt");

	//	m_nstage++;
	//	m_pEnemyMgr->release();
	//	m_pEnemyMgr->setEnemy(vec, m_nstage);
	//	m_pEnemyMgr->setTarget(m_pSpaceShip);

	//	m_pSpaceShip->restart();

	//	if (m_nstage >= 3)
	//	{
	//		SCENEMANAGER->changeScene("score");
	//	}
	//}
}

void battleScene::render(HDC hdc)
{
	IMAGEMANAGER->findImage("background")->render(hdc, 0, 0);
	//char str[128];

	//sprintf_s(str, 128, "score : %d", *m_pscore);

	//m_pSpaceShip->render(hdc);
	//m_pEnemyMgr->render(hdc);

	m_pPlayer->render(hdc);

	//SetBkMode(hdc, TRANSPARENT);
	//SetTextColor(hdc, RGB(255, 0, 0));
	//TextOut(hdc, 10, 10, str, strlen(str));
	////TIMEMANAGER->render(hdc);

	//if (m_pCamel)
	//{
	//	m_pCamel->render(hdc);
	//}

	//// save load test
	//char str[128];
	//for (int i = 0; i < m_vecLoad.size(); i++)
	//{
	//// string type과 char 배열은 엄연히 다른 타입이다
	//sprintf_s(str, 128, "이름_%d : %s", i, m_vecLoad[i].c_str());
	//TextOut(hdc, 100, 100 + i * 30, str, strlen(str));

	//EFFECTMANAGER->render(hdc);
	
}




void battleScene::checkCollision()
{
	// 적 미사일과 플레이어 확인
	std::vector<enemy*> vEnemy = m_pEnemyMgr->getVecEnemy();
	std::vector<enemy*>::iterator iter;

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
				IntersectRect(&rc, &m_pSpaceShip->getRect(), &(*iterMissile)->getRect()))
			{
				// 미사일 삭제
				(*iterMissile)->setIsFire(false);

				// 플레이어 HP 감소
				m_pSpaceShip->damaged(1);
				*m_pscore-=1;
			}

			std::vector<missile*> vPMissile = m_pSpaceShip->getMissileMgr()->getVecMissile();
			std::vector<missile*>::iterator iterPMissile;

			for (iterPMissile = vPMissile.begin(); iterPMissile != vPMissile.end(); iterPMissile++)
			{
				RECT rc;
				if ((*iterMissile)->getIsFire() && (*iterPMissile)->getIsFire() &&
					IntersectRect(&rc, &(*iterPMissile)->getRect(), &(*iterMissile)->getRect()))
				{
					(*iterMissile)->setIsFire(false);

					(*iterPMissile)->setIsFire(false);

					EFFECTMANAGER->play("explosion1", rc.left, rc.top);


				}
			}
		}



		std::vector<missile*> vPMissile = m_pSpaceShip->getMissileMgr()->getVecMissile();
		std::vector<missile*>::iterator iterPMissile;

		for (iterPMissile = vPMissile.begin(); iterPMissile != vPMissile.end(); iterPMissile++)
		{
			RECT rc;
			if ((*iter)->getIsAlive() && (*iterPMissile)->getIsFire() &&
				IntersectRect(&rc, &(*iterPMissile)->getRect(), &(*iter)->getRect()))
			{
				(*iter)->setIsAlive(false);

				(*iterPMissile)->setIsFire(false);

				EFFECTMANAGER->play("explosion1", rc.left, rc.top);

  				*m_pscore+=1;


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
