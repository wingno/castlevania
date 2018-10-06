#include "stdafx.h"
#include "battleScene.h"
#include "spaceShip.h"
#include "enemyManager.h"
#include "missileManager.h"
#include "camel.h"
#include "selectScene.h"
#include "hallwayRoom1.h"
#include "FountainRoom.h"
#include "player.h"


HRESULT battleScene::init()
{
	IMAGEMANAGER->addImage("background", "image/mapImage.bmp", WINSIZEX, WINSIZEY, false, 0);

	
	m_pPlayer = g_mainGame.getPlayer();




	ROOMMANAGER->setPlayer(m_pPlayer);

	m_phallwayRoom1 = new hallwayRoom1;
	ROOMMANAGER->addRoom("hallwayRoom1", m_phallwayRoom1);

	m_pFountainRoom = new FountainRoom;
	ROOMMANAGER->addRoom("FountainRoom", m_pFountainRoom);


	ROOMMANAGER->changeRoom("hallwayRoom1");



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
		SCENEMANAGER->changeScene("menu");
	}

}

void battleScene::render(HDC hdc)
{
	//IMAGEMANAGER->findImage("background")->render(hdc, 0, 0);


	ROOMMANAGER->render(hdc);
	m_pPlayer->render(hdc);


	
}






battleScene::battleScene()
{
}


battleScene::~battleScene()
{
}
