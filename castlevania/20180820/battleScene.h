#pragma once
#include "scene.h"

class spaceShip;
class enemyManager;
class camel;
class player;
class roomManager;
class hallwayRoom1;
class FountainRoom;



class battleScene : public scene
{
private:
	image *			m_imgMap;
	spaceShip*		m_pSpaceShip;
	enemyManager*	m_pEnemyMgr;
	camel*			m_pCamel;

	hallwayRoom1*	m_phallwayRoom1;
	FountainRoom*	m_pFountainRoom;
	
	roomManager*	m_RoomMgr;


	player*			m_pPlayer;

	int m_nstage;

	int* m_pscore;

	int m_nselectNum;

	bool m_benemyIsSetting;

	bool m_bIsChangeScene;



	int m_nAlphaNum;

	

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

