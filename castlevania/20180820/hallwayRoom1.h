#pragma once
#include "room.h"

class image;
class zombie;


class hallwayRoom1:public room
{
private:

	RECT rectGate[3];
	RECT rectObj[2];

	zombie* m_Zombie;

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

