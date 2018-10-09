#pragma once
#include "room.h"

class image;


class CastleHallway : public room
{
private:
	//¹®
	RECT rectGate[3];
	//¹ßÆÇ
	RECT rectObj[12];

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void colliderMake();
	void rectColider();

	
	CastleHallway();
	~CastleHallway();
};

