#pragma once
#include "room.h"

class gateRoom :public room
{

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);



	gateRoom();
	~gateRoom();
};

