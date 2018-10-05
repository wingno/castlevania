#pragma once
#include "scene.h"

class spaceShip;
class enemyManager;
class camel;
class player;
class roomManager;
class hallwayRoom1;
class FountainRoom;
class gateRoom;
class zombi;


class battleScene : public scene
{
private:
	image *			m_imgMap;
	spaceShip*		m_pSpaceShip;
	enemyManager*	m_pEnemyMgr;
	camel*			m_pCamel;


	//����
	zombi* m_zombi;

	//��
	hallwayRoom1*	m_phallwayRoom1;
	FountainRoom*	m_pFountainRoom;
	gateRoom*		m_gateroom;


	roomManager*	m_RoomMgr;



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

