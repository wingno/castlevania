#pragma once


class image;

class CoinObject;


class RoomObject 
{
private:
	
	//�ı� ���θ� äũ
	bool DestructionMove;
	//@@@@@@@@@@@@@@@@@@@@@@@@������Ʈ@@@@@@@@@@@@@@@@@@
	//��ġ

	//������ 
	int FrameX, FrameY;
	//�ε���
	int MyIdx;
	//ī��Ʈ
	int MYCount;
	//������Ʈ ��ȣ
	int OBnum;

	CoinObject* m_coin;

	//������Ʈ�̹���
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

