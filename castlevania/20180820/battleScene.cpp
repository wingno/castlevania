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
	IMAGEMANAGER->addImage("background", "image/background.bmp", WINSIZEX, WINSIZEY, false, 0);

	


	m_pPlayer = new player;
	m_pPlayer->init();
	ROOMMANAGER->setPlayer(m_pPlayer);

	


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

	return S_OK;
}

void battleScene::release()
{
	//·ë »èÁ¦
	SAFE_DELETE(m_phallwayRoom1);
	SAFE_DELETE(m_phallwayRoom2);
	SAFE_DELETE(m_pFountainRoom);
	SAFE_DELETE(m_gateroom);
	SAFE_DELETE(m_CastleHallway);
	

	SAFE_DELETE(m_pPlayer);


}

void battleScene::update()
{

	m_pPlayer->update();

	ROOMMANAGER->update();



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
