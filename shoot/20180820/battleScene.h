#pragma once
#include "scene.h"

class player;
class enemyManager;
class camel;
class button;
class stage1;
class scoreBoard;
class sanger;

class battleScene : public scene
{
private:
	
	//image *			m_imgMap;
	enemyManager*	m_pEnemyMgr;
	player*			m_pPlayer;
	stage1*			m_pStage1;
	scoreBoard*		m_pScoreBoard;
	sanger*			m_pSanger;
	

	SYNTHESIZE(bool, m_bIsGameover,IsGameover);
	SYNTHESIZE(bool, m_bIsEndding,IsEndding);


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void mapchackCollision();

	void checkCollision();






	battleScene();
	~battleScene();
};

