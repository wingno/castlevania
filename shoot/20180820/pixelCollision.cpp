#include "stdafx.h"
#include "pixelCollision.h"


HRESULT pixelCollision::init()
{
	IMAGEMANAGER->addImage("image/background.bmp",
		"image/background.bmp", 600, 800, true, RGB(255, 0, 255));
	m_pImgMountain = IMAGEMANAGER->addImage("image/mountain.bmp",
		"image/mountain.bmp", 800, 600, true, RGB(255, 0, 255));
	m_pImgBall = IMAGEMANAGER->addImage("image/ball.bmp",
		"image/ball.bmp", 60, 60, true, RGB(255, 0, 255));

	m_position.x = WINSIZEX / 2;
	m_position.y = WINSIZEY / 2;

	m_rc = RectMakeCenter(m_position.x, m_currY,
		100, 100);

	m_currY = m_position.y + m_pImgBall->getHeight() / 2;

	return S_OK;
}

void pixelCollision::release()
{
}

void pixelCollision::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		m_position.x -= 2.0f;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		m_position.x += 2.0f;
	}

	m_currY = (int)m_position.y + m_pImgBall->getHeight() / 2;
	for (int i = m_currY - 50; i < m_currY + 50; i++)
	{
		COLORREF color = GetPixel(m_pImgMountain->getMemDC(),
			(int)m_position.x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//if (r == 255 && g == 0 && b == 255)
		//{
		//	m_position.y = i - m_pImgBall->getHeight() / 2;

		//	m_rc = RectMakeCenter(m_position.x, i,
		//		100, 100);
		//}

		if (!(r == 255 && g == 0 && b == 255))
		{
			m_position.y = i - m_pImgBall->getHeight() / 2;

			m_rc = RectMakeCenter(m_position.x, i,
				100, 100);
			break;
		}
	}
}

void pixelCollision::render(HDC hdc)
{
	IMAGEMANAGER->findImage("image/background.bmp")->render(hdc, 0, 0);

	m_pImgMountain->render(hdc, 0, 0);
	m_pImgBall->render(hdc, m_position.x - m_pImgBall->getWidth() / 2,
		m_position.y - m_pImgBall->getHeight() / 2);

	//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
}

pixelCollision::pixelCollision()
{
}


pixelCollision::~pixelCollision()
{
}
