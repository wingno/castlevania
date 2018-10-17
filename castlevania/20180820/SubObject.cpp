#include "stdafx.h"
#include "SubObject.h"
#include "room.h"
#include "RoomObject.h"
#include "CoinObject.h"
#include "player.h"

HRESULT SubObject::init(int XX, int XY)
{
	m_imgCoin = IMAGEMANAGER->addImage("1coin", "image/object/onecoin.bmp", 33, 10, 3, 1, true, RGB(0, 64, 128));
	m_imgOneCoin = IMAGEMANAGER->addImage("1won", "image/object/1won.bmp", 143 / 1.2, 75 / 1.2, 1, 1, true, RGB(255, 0, 255));

	m_bAlive = false;
	m_bOneCoin = false;
	m_bDown = false;
	m_bStand = false;
	SubObjectNum = 0;
	m_fX = XX;
	m_fY = XY;
	m_fSpeed = 0;
	m_nFrameX = 0;
	m_nFrameY = 0;
	m_nIndex = 0;
	m_nCount = 0;




	return S_OK;
}

void SubObject::release()
{

}

void SubObject::update()
{

	
	switch (SubObjectNum)
	{
	case 0:
		
		if (m_bAlive)
		{
			m_fSpeed += 0.2;
			m_fY -= 1 * m_fSpeed;
			m_nIndex++;
			m_nCount++;
			if (m_nIndex % 3 == 0)
			{
				m_nFrameX++;

				if (m_nFrameX > 3)
				{
					m_nFrameX = 0;
				}
			}
			if (m_nCount == 10)
			{
				m_nCount = 0;
				m_bDown = true;
				m_bAlive = false;
			}

		}
		if (m_bDown)
		{
			m_fSpeed += 0.4f;
			m_fY += 0.8f * m_fSpeed;
			m_nIndex++;
			if (m_nIndex % 3 == 0)
			{
				m_nFrameX++;

				if (m_nFrameX > 3)
				{
					m_nFrameX = 0;
				}

			}
		}
		if (m_bStand)
		{
			m_fY = m_fY;
			m_nIndex++;
			if (m_nIndex % 3 == 0)
			{
				m_nFrameX++;
				if (m_nFrameX > 3)
				{
					m_nFrameX = 0;
				}
			}
		}
		if (m_bOneCoin)
		{
			m_nCount++;

			if (m_nCount == 100)
			{
				m_bOneCoin = false;
			}
		}
		break;
	case 1:
		break;
	default:
		break;
	}

	
	checkCollision();
	
	m_rc = RectMakeCenter(m_fX + 18 - ROOMMANAGER->getCurrRoom()->getPosMap().x, m_fY + 17 - ROOMMANAGER->getCurrRoom()->getPosMap().y,
		m_imgCoin->getWidth() / 2, m_imgCoin->getHeight() * 2);
	
	if(!m_bAlive &&!m_bStand &&!m_bDown)
	{
		m_rc = RectMakeCenter(-10, -10,
			-1,-1);
	}

}

void SubObject::render(HDC hdc)
{

	Rectangle(hdc, m_rc.left, m_rc.top,
		m_rc.right, m_rc.bottom);

	if (m_bAlive || m_bStand ||
		m_bDown
		)
	{
		
		m_imgCoin->frameRender(hdc, m_fX - ROOMMANAGER->getCurrRoom()->getPosMap().x, m_fY - ROOMMANAGER->getCurrRoom()->getPosMap().y
			, m_nFrameX, m_nFrameY, 3);
	}

	if (m_bOneCoin)
	{
		m_imgOneCoin->render(hdc, 0, 420);

	}



}





void SubObject::checkCollision()
{
	for (int y = m_rc.top; y <= m_rc.bottom; y++)
	{
		COLORREF color = GetPixel(ROOMMANAGER->getCurrRoom()->getMemDCInfo()->hMemDC,
			m_fX, m_fY + 20);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);


		if (y == m_rc.bottom)
		{
		color = GetPixel(ROOMMANAGER->getCurrRoom()->getMemDCInfo()->hMemDC,
			m_fX, m_fY +20 );
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);



			if (!(r == 0 && g == 88 && b == 24))
			{
				m_bDown = false;
				m_bStand = true;
				m_fY = m_fY - 10;
			}
		}
	}

	//수정해야함

	RECT rc;

	if (IntersectRect(&rc, &m_rc, &ROOMMANAGER->getPlayer()->getRc()))
	{
		m_bAlive = false;
		m_bStand = false;
		
		
		switch (SubObjectNum)
		{
		case 0:
			m_bOneCoin = true;
			break;
		}

	}

}

void SubObject::SetSubObjectNum(int Num)
{
	SubObjectNum = Num;

}



SubObject::SubObject()
{
}


SubObject::~SubObject()
{
}
