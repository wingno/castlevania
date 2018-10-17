#include "stdafx.h"
#include "battleScene.h"
#include "spaceShip.h"
#include "enemyManager.h"
#include "missileManager.h"
#include "camel.h"
#include "selectScene.h"
#include "player.h"
#include "progressBar.h"


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






battleScene::battleScene()
{
}


battleScene::~battleScene()
{
}
