#include "stdafx.h"
#include "CoinObject.h"
#include "room.h"
#include "RoomObject.h"
#include "CoinObject.h"
#include "player.h"


HRESULT CoinObject::init(int XX, int XY)
{

	m_coin = IMAGEMANAGER->addImage("1coin", "image/object/onecoin.bmp", 33, 10, 3, 1, true, RGB(0, 64, 128));

	//오브잭트
	Alive = false;
	//파괴 여부를 채크
	Destruction = false;
	Down = false;
	m_bstand = false;
	//위치
	FX = XX ;
	FY = XY;
	
	//프레임 
	FrameX = 0;
	FrameY = 0;
	speed = 0;
	MyIdx = 0;
	MYCount = 0;

	m_rc = RectMakeCenter(FX , FY,
		m_coin->getWidth() / 2, m_coin->getHeight() * 2);
	return S_OK;

}

void CoinObject::release()
{
}

void CoinObject::update()
{
	
		if (Alive)
		{
			speed+=0.2;
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
			speed += 0.4f;
			FY += 0.8f * speed;
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


		if (m_bstand)
		{

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


	m_rc = RectMakeCenter(FX+ 18 - ROOMMANAGER->getCurrRoom()->getPosMap().x , FY +17  - ROOMMANAGER->getCurrRoom()->getPosMap().y,
		m_coin->getWidth() /2, m_coin->getHeight() * 2);


	
		RECT rc;

		if (IntersectRect(&rc, &m_rc, &ROOMMANAGER->getPlayer()->getIRC()))
		{
			
           Alive = false;
			Down = false;
			m_bstand = false;

		}










	for (int y = m_rc.top; y <= m_rc.bottom; y++)
	{
		COLORREF color = GetPixel(ROOMMANAGER->getCurrRoom()->getMemDCInfo()->hMemDC,
			FX, FY + 29.5f);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);



		if (y == m_rc.bottom )
		{
			color = GetPixel(ROOMMANAGER->getCurrRoom()->getMemDCInfo()->hMemDC,
				FX, FY + 29.5f );

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

	
			
			if (!(r == 0 && g == 88 && b == 24))
			{
				Down = false;
				m_bstand = true;
				
				
			}
		}
	}

	//수정해야함



	

}

void CoinObject::render(HDC hdc)
{


	if (Alive || m_bstand||
		 Down
		)
	{


		Rectangle(hdc, m_rc.left, m_rc.top,

			m_rc.right, m_rc.bottom);

		m_coin->frameRender(hdc, FX - ROOMMANAGER->getCurrRoom()->getPosMap().x ,FY - ROOMMANAGER->getCurrRoom()->getPosMap().y
			, FrameX, FrameY, 3);
		


	}
}


CoinObject::CoinObject()
{
}


CoinObject::~CoinObject()
{
}
