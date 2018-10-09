#pragma once
#include"room.h"

class image;



class RoomObject : public room
{
private:
	
	//파괴 여부를 채크
	bool DestructionMove;

	//위치
	int FX, FY;
	//프레임 
	int FrameX, FrameY;
	//인덱스
	int MyIdx;
	//카운트
	int MYCount;
	//오브잭트 번호
	int OBnum;

	
	image* m_Candlelight;
	SYNTHESIZE(bool, Alive, Alive);
	SYNTHESIZE(bool, Destruction, Destruction);
	SYNTHESIZE(RECT, m_rc, rc);


public:

	virtual HRESULT init(int MYX, int MYY, int Object);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);


	RoomObject();
	~RoomObject();
};

