#include "stdafx.h"
#include "slash.h"


HRESULT slash::init()
{
	m_imgSlash = IMAGEMANAGER->addImage("image/slash.bmp", "image/slash.bmp", 288, 600, true, RGB(255, 0, 255));

	m_rc[0] = RectMake(WINSIZEX - 500,0,288,150);
	m_rc[1] = RectMake(WINSIZEX - 500, 150, 288, 150);
	m_rc[2] = RectMake(WINSIZEX - 500, 300, 288, 150);
	m_rc[3] = RectMake(WINSIZEX - 500, 450, 288, 150);

	for (int i = 0; i < 4; i++)
	{
		m_nRcHP[i] = 30;
	}

	m_ndamage = 50;

	m_bisAlive = false;

	return S_OK;
}

void slash::release()
{
}

void slash::update()
{


	for (int i = 0; i < 4; i++)
	{
		if (m_nRcHP[i] <= 0)
		{
			continue;
		}
		
		m_rc[i].left -= 2.0f;
		m_rc[i].right -= 2.0f;

		if (m_rc[i].right < 0)
		{
			m_bisAlive = false;
		}
		
	}

}

void slash::render(HDC hdc)
{


	for (int i = 0; i < 4; i++)
	{
		if (m_nRcHP[i] <= 0)
		{
			continue;
		}

		m_imgSlash->render(hdc, m_rc[i].left, m_rc[i].top, 0, 150 * i, 288, 150);
		

	}


}

slash::slash()
{
}


slash::~slash()
{
}
