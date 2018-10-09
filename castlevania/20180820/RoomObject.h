#pragma once
#include"room.h"

class image;



class RoomObject : public room
{
private:
	
	//�ı� ���θ� äũ
	bool DestructionMove;

	//��ġ
	int FX, FY;
	//������ 
	int FrameX, FrameY;
	//�ε���
	int MyIdx;
	//ī��Ʈ
	int MYCount;
	//������Ʈ ��ȣ
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

