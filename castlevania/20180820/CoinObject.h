#pragma once
#include"RoomObject.h"

class player;


class CoinObject : public RoomObject
{

private:

	//@@@@@@@@@@@@@@@@@@코인@@@@@@@@@@@@@@@@

	//코인오브젝트 넘버
	int CoinNum;
	//코인이미지
	image* m_coin;
	//위치
	int FX, FY;
	float speed;
	//프레임 
	int FrameX, FrameY;
	//인덱스
	int MyIdx;
	//카운트
	int MYCount;

	bool Down;
	bool m_bstand;
	RoomObject* m_RoomOBJ;


	SYNTHESIZE(bool, Alive, Alive);
	SYNTHESIZE(bool, Destruction, Destruction);
	SYNTHESIZE(RECT, m_rc, rc);

public:

		virtual HRESULT init(int XX, int XY);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);



	CoinObject();
	~CoinObject();
};

