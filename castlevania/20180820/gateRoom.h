#pragma once
#include "room.h"
class image;
class gateRoom :public room
{
	
	RECT rectGate[1];
	RECT rectObj[6];

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void colliderMake();
	void rectColider();


	gateRoom();
	~gateRoom();
};

