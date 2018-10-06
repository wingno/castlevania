#pragma once
#include "room.h"

class image;
class zombi;

class hallwayRoom1:public room
{
private:

	RECT rectGate[3];
	RECT rectObj[2];

	zombi* m_zombi;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);



	void colliderMake();
	void rectColider();

	hallwayRoom1();
	~hallwayRoom1();
};

