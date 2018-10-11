#include "stdafx.h"
#include "RoomObject.h"
#include "room.h"
#include "CoinObject.h"

HRESULT RoomObject::init(int MYX, int MYY, int Object)
{
	//오브잭트
	m_Candlelight = IMAGEMANAGER->addImage("candle", "image/object/candle.bmp", 198, 23, 11, 1, true, RGB(0, 64, 128));
	m_Candlelight = IMAGEMANAGER->addImage("minifire", "image/object/minifire.bmp", 56, 20, 4, 1, true, RGB(0, 64, 128));
	

	//오브잭트
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

	m_rc = RectMakeCenter(FX + 26, FY + 45, m_Candlelight->getWidth() / 4 - 3, m_Candlelight->getHeight() * 2);

	m_coin = new CoinObject;
	m_coin->init(FX, FY );


	return S_OK;
}

void RoomObject::release()
{
}

void RoomObject::update()
{
	ObjectCode();
	



	m_rc = RectMakeCenter(FX + 26 - ROOMMANAGER->getCurrRoom()->getPosMap().x, FY + 45- ROOMMANAGER->getCurrRoom()->getPosMap().y,
		 m_Candlelight->getWidth() / 4 - 3, m_Candlelight->getHeight() * 2);



}

void RoomObject::render(HDC hdc)
{
	if (Alive||
		Destruction||
		DestructionMove)
	{
		/*Rectangle(hdc, m_rc.left, m_rc.top,
			m_rc.right, m_rc.bottom);*/
		

		m_Candlelight->frameRender(hdc, FX - ROOMMANAGER->getCurrRoom()->getPosMap().x,
			FY - ROOMMANAGER->getCurrRoom()->getPosMap().y
			, FrameX, FrameY, 3);
	
		

	}
	

	m_coin->render(hdc);
	
}

void RoomObject::ObjectCode()
{
	m_coin->update();

	switch (OBnum)
	{
	case 0: //촛불
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
					OBnum = 0;
			
					DestructionMove = false;
				
					
					m_coin->setAlive(true);

				}
			}

		}
		break;

	case 1: //휏불
		m_Candlelight = IMAGEMANAGER->findImage("minifire");
		//기본동작
		if (Alive)
		{
			MyIdx++;
			if (MyIdx % 5 == 0)
			{
				FrameX++;
				if (FrameX > 3)
				{
					FrameX = 0;
				}
			}
		}


		break;
	case 2: 
	

	default:
		break;
	}

}




RoomObject::RoomObject()
{


}


RoomObject::~RoomObject()
{
}
