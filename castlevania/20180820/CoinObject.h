#pragma once
#include"RoomObject.h"

class player;


class CoinObject : public RoomObject
{

private:

	//@@@@@@@@@@@@@@@@@@����@@@@@@@@@@@@@@@@

	//���ο�����Ʈ �ѹ�
	int CoinNum;
	//�����̹���
	image* m_coin;
	//��ġ
	int FX, FY;
	float speed;
	//������ 
	int FrameX, FrameY;
	//�ε���
	int MyIdx;
	//ī��Ʈ
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

