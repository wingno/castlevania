#pragma once


class image;

class CoinObject;


class RoomObject 
{
private:
	
	//파괴 여부를 채크
	bool DestructionMove;
	//@@@@@@@@@@@@@@@@@@@@@@@@오브잭트@@@@@@@@@@@@@@@@@@
	//위치

	//프레임 
	int FrameX, FrameY;
	//인덱스
	int MyIdx;
	//카운트
	int MYCount;
	//오브잭트 번호
	int OBnum;

	CoinObject* m_coin;

	//오브잭트이미지
	image* m_Candlelight;
	
	SYNTHESIZE(int, FX, FX);
	SYNTHESIZE(int, FY, FY);
	SYNTHESIZE(bool, Alive, Alive);
	SYNTHESIZE(bool, Destruction, Destruction);
	SYNTHESIZE(RECT, m_rc, rc);


public:

	virtual HRESULT init(int MYX, int MYY, int Object);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void ObjectCode();
	


	RoomObject();
	~RoomObject();
};

