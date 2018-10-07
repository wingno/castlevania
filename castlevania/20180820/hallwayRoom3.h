#pragma once
#include "room.h"
class image;


class hallwayRoom3: public room
{


private:

	RECT rectGate[3];
	RECT rectObj[2];

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	void rectColider();
	void colliderMake();

	hallwayRoom3();
	~hallwayRoom3();
};

