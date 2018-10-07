#pragma once
#include "scene.h"

class spaceShip;
class enemyManager;
class camel;
class player;
//·ë
class roomManager;
class hallwayRoom1;
class hallwayRoom2;
class hallwayRoom3;
class FountainRoom;
class gateRoom;
class SaveRoom;
class CastleHallway;
class BrickStaircaseroom;



class battleScene : public scene
{
private:
	image *			m_imgMap;
	spaceShip*		m_pSpaceShip;
	enemyManager*	m_pEnemyMgr;
	camel*			m_pCamel;


	//Á»ºñ
	zombi* m_zombi;

	//·Ò
	hallwayRoom1*	m_phallwayRoom1;
	hallwayRoom2*	m_phallwayRoom2;
	hallwayRoom3*	m_phallwayRoom3;
	FountainRoom*	m_pFountainRoom;
	gateRoom*		m_gateroom;
	SaveRoom*		m_SaveRoom;
	roomManager*	m_RoomMgr;
	CastleHallway*  m_CastleHallway;
	BrickStaircaseroom* m_BrickStaircaseroom;

	player*			m_pPlayer;

	int m_nstage;

	int* m_pscore;

	int m_nselectNum;

	bool m_benemyIsSetting;

	

	// save load test
	std::vector<std::string> m_vecLoad;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void checkCollision();

	inline void setIsScore(int* score) { m_pscore = score; }



	inline void setISpaceShip(spaceShip* SpaceShip) { m_pSpaceShip = SpaceShip; }

	battleScene();
	~battleScene();
};

