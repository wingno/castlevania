#include "stdafx.h"
#include "RoomObject.h"
#include "player.h"

HRESULT RoomObject::init(int MYX, int MYY, int Object)
{
	m_Candlelight = IMAGEMANAGER->addImage("candle", "image/candle.bmp", 198, 23, 11, 1, true, RGB(0, 64, 128));


	Alive = true;
	//�ı� ���θ� äũ
	Destruction = false;
	DestructionMove = false;
	//��ġ
	FX = MYX;
	FY = MYY;
	//������Ʈ ��ȣ
	OBnum = Object;

	//������ 
	FrameX = 0;
	FrameY = 0;

	MyIdx = 0;
	MYCount = 0;

	m_rc = RectMakeCenter(FX , FY,m_Candlelight->getX() , m_Candlelight->getY());


	return S_OK;
}

void RoomObject::release()
{
}

void RoomObject::update()
{
	switch (OBnum)
	{
	case 0:
		m_Candlelight = IMAGEMANAGER->findImage("candle");
	//�⺻����
	if (Alive)
	{
		MyIdx++;
		if (MyIdx % 7 == 0)
		{
			FrameX++;
			if (FrameX > 5)
			{
				FrameX = 0;
			}
		}
	}
	
	//�浹ó�� ���������̾ȵű⋚���� 'b'�� ǥ�� 
	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		Destruction = true;
		Alive = false;
		FrameX = 6;
	}
	
	
	if (Destruction)
	{

		MyIdx++;
		if (MyIdx % 3 == 0)
		{
			FrameX++;
			if (FrameX > 8)
			{
				FrameX = 8;
				if (FrameX = 8)
				{
					FY -= 4;
					MYCount++;

					if (MYCount == 5)
					{
						FrameX = 8;
						Destruction = false;
						DestructionMove = true;
					
					}
					
				}
			}
		}

	}
	// ������ ���ϴ¸��
	if (DestructionMove)
	{

		MyIdx++;
		if (MyIdx % 5 == 0)
		{
			FrameX++;
			if (FrameX > 10)
			{
				DestructionMove = false;
			}
		}

	}
	break;

	case 1:
	default:
		break;
	}


}

void RoomObject::render(HDC hdc)
{
	if (Alive||
		Destruction||
		DestructionMove)
	{
		
		Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);

		m_Candlelight->frameRender(hdc, FX - ROOMMANAGER->getCurrRoom()->getPosMap().x,
			FY , FrameX, FrameY, 3);

		

	}
	
	
}


RoomObject::RoomObject()
{


}


RoomObject::~RoomObject()
{
}
