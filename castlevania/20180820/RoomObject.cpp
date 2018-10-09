#include "stdafx.h"
#include "RoomObject.h"
#include "player.h"

HRESULT RoomObject::init(int MYX, int MYY, int Object)
{
	m_Candlelight = IMAGEMANAGER->addImage("candle", "image/candle.bmp", 198, 23, 11, 1, true, RGB(0, 64, 128));


	Alive = true;
	//파괴 여부를 채크
	Destruction = false;
	DestructionMove = false;
	//위치
	FX = MYX;
	FY = MYY;
	//오브잭트 번호
	OBnum = Object;

	//프레임 
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
	//기본동작
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
	
	//충돌처리 점프공격이안돼기떄문에 'b'로 표현 
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
	// 죽을떄 취하는모션
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
