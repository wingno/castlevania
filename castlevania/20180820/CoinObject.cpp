#include "stdafx.h"
#include "CoinObject.h"
#include "room.h"
#include "RoomObject.h"
#include "CoinObject.h"

HRESULT CoinObject::init(int XX, int XY)
{

	m_coin = IMAGEMANAGER->addImage("1coin", "image/object/onecoin.bmp", 33, 10, 3, 1, true, RGB(0, 64, 128));

	//오브잭트
	Alive = false;
	//파괴 여부를 채크
	Destruction = false;
	Down = false;
	//위치
	FX = XX ;
	FY = XY ;
	
	//프레임 
	FrameX = 0;
	FrameY = 0;
	speed = 0;
	MyIdx = 0;
	MYCount = 0;

	return S_OK;

}

void CoinObject::release()
{
}

void CoinObject::update()
{
	
		if (Alive)
		{
			speed+=1.4f;
			FY -= 1 * speed;
			MyIdx++;
			MYCount++;
			if (MyIdx % 3 == 0)
			{
				FrameX++;
				
				if (FrameX > 3)
				{

					FrameX = 0;
				}

			}

			if (MYCount == 10)
			{

				Down = true;
				Alive = false;
			}

		}


		if (Down)
		{
			speed += 0.2f;
			FY += 0.5f * speed;
			MyIdx++;
			if (MyIdx % 3 == 0)
			{
				FrameX++;

				if (FrameX > 3)
				{
					FrameX = 0;
				}

			}
		}



	m_rc = RectMakeCenter(FX +25 - ROOMMANAGER->getCurrRoom()->getPosMap().x , FY +26 - ROOMMANAGER->getCurrRoom()->getPosMap().y,
		m_coin->getWidth() /2, m_coin->getHeight() * 2);

}

void CoinObject::render(HDC hdc)
{


	if (Alive ||
		Destruction|| Down
		)
	{


		Rectangle(hdc, m_rc.left, m_rc.top,

			m_rc.right, m_rc.bottom);

		m_coin->frameRender(hdc, FX + 8- ROOMMANAGER->getCurrRoom()->getPosMap().x ,FY - ROOMMANAGER->getCurrRoom()->getPosMap().y +10
			, FrameX, FrameY, 3);



	}
}


CoinObject::CoinObject()
{
}


CoinObject::~CoinObject()
{
}
