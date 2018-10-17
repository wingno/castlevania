#pragma once

class player;
class RoomObject;


class SubObject
{

	//���������Ʈ �����̹��� 
	image* m_imgCoin;
	//����� ��Ÿ���� �����̹���
	//1��
	image* m_imgOneCoin;

	//ī��Ʈ
	int m_nCount;
	//��ġ X,Y Speed
	float m_fX, m_fY, m_fSpeed;
	//������, �ε���
	int m_nFrameX, m_nFrameY, m_nIndex;
	//�ൿ����
	bool m_bDown, m_bStand, m_bOneCoin ;


	//������Ʈ �ѹ�
	int SubObjectNum;
	//�������Ʈ 
	RoomObject* m_RoomObject;
	//�÷��̾�
	player* m_Player;
	//������Ʈ ����ִ°��
	SYNTHESIZE(bool, m_bAlive, Alive);
	//������Ʈ ��Ʈ
	SYNTHESIZE(RECT, m_rc, rc);
	

public:

	virtual HRESULT init(int XX, int XY);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void checkCollision();
	void SetSubObjectNum(int Num);



	SubObject();
	~SubObject();
};

