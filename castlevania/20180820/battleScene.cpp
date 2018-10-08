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
	IMAGEMANAGER->addImage("background", "image/mapImage.bmp", WINSIZEX, WINSIZEY, false, 0);

	
	m_pPlayer = g_mainGame.getPlayer();



	




	
	m_bIsChangeScene = false;
	m_nAlphaNum = 0;


	return S_OK;
}

void battleScene::release()
{


}

void battleScene::update()
{

	m_pPlayer->update();

	ROOMMANAGER->update();

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
