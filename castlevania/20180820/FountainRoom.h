#pragma once
#include "room.h"

class image;
class FountainRoom:public room
{
private:

	RECT rectGate[3];
	RECT rectObj[2];

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void colliderMake();
	void rectColider();	

	FountainRoom();
	~FountainRoom();
};

