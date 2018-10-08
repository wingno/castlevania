#include "stdafx.h"
#include "battleScene.h"
#include "spaceShip.h"
#include "enemyManager.h"
#include "missileManager.h"
#include "camel.h"
#include "selectScene.h"
#include "player.h"
#include"zombi.h"

//·ë
#include "hallwayRoom1.h"
#include "hallwayRoom2.h"
#include "hallwayRoom3.h"
#include "FountainRoom.h"
#include"gateroom.h"
#include "SaveRoom.h"
#include "CastleHallway.h"
#include "BrickStaircaseroom.h"

HRESULT battleScene::init()
{
	IMAGEMANAGER->addImage("background", "image/mapImage.bmp", WINSIZEX, WINSIZEY, false, 0);

	
	m_pPlayer = g_mainGame.getPlayer();



	


	// ·ë ÀÌ´Ï¼È¶óÀÌÁî
	m_phallwayRoom1 = new hallwayRoom1;
	ROOMMANAGER->addRoom("hallwayRoom1", m_phallwayRoom1);

	m_phallwayRoom2 = new hallwayRoom2;
	ROOMMANAGER->addRoom("hallwayRoom2", m_phallwayRoom2);

	m_phallwayRoom3 = new hallwayRoom3;
	ROOMMANAGER->addRoom("hallwayRoom3", m_phallwayRoom3);

	m_pFountainRoom = new FountainRoom;
	ROOMMANAGER->addRoom("FountainRoom", m_pFountainRoom);

	m_gateroom = new gateRoom;
	ROOMMANAGER->addRoom("gateroom", m_gateroom);

	m_SaveRoom = new SaveRoom;
	ROOMMANAGER->addRoom("saveroom", m_SaveRoom);

	m_CastleHallway = new CastleHallway;
	ROOMMANAGER->addRoom("CastleHallwayy", m_CastleHallway);
	

	m_BrickStaircaseroom = new BrickStaircaseroom;
	ROOMMANAGER->addRoom("BrickStaircaseroom", m_BrickStaircaseroom);

	ROOMMANAGER->changeRoom("hallwayRoom1");

	
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
