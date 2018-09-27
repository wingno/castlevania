#include "stdafx.h"
#include "progressBar.h"

HRESULT progressBar::init(float x, float y, float width, float height)
{
	m_fX = x;
	m_fY = y;

	//m_rc = RectMake(m_fX, m_fY, m_fWidth, height);

	m_imgBottom = IMAGEMANAGER->addImage("barBottom",
		"image/magic_meter_fill.bmp", 52, 221, true, RGB(255, 0, 255));
	m_imgTop = IMAGEMANAGER->addImage("barTop",
		"image/magic_meter_frame.bmp", 164, 318, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("head", "image/head.bmp", 116, 128, true, RGB(255, 0, 255));

	m_isPlayer = true;

	return S_OK;
}

HRESULT progressBar::init()
{


	//m_rc = RectMake(m_fX, m_fY, m_fWidth, height);

	m_imgBottom = IMAGEMANAGER->addImage("barBottom",
		"image/magic_meter_fill.bmp", WINSIZEX- 52, 221, true, RGB(255, 0, 255));
	m_imgTop = IMAGEMANAGER->addImage("barTop",
		"image/magic_meter_frame.bmp", WINSIZEX - 164, 318, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bosshead", "image/bosshead.bmp", 54, 38, true, RGB(255, 0, 255));
	m_isPlayer = false;

	return S_OK;
}

void progressBar::release()
{
}

void progressBar::update()
{
}

void progressBar::render(HDC hdc)
{
	if (m_isPlayer)
	{
		IMAGEMANAGER->findImage("head")->render(hdc, 30, WINSIZEY / 2-85, 39, 43,0,0, 116, 128);
		IMAGEMANAGER->findImage("barBottom")->render(hdc, 10, WINSIZEY / 2 - 55+(110-m_nLenght) , 20, m_nLenght, 0, (221 - m_fgauge), 52, m_fgauge);
		IMAGEMANAGER->findImage("barTop")->render(hdc, 0, WINSIZEY/2 -90,82,159,0,0,164,318);
	}
	else
	{
		IMAGEMANAGER->findImage("bosshead")->render(hdc, WINSIZEX-58, WINSIZEY / 2 - 78);
		IMAGEMANAGER->findImage("barBottom")->render(hdc, WINSIZEX - 70, WINSIZEY / 2 - 55 + (110 - m_nLenght), 20, m_nLenght, 0, (221 - m_fgauge), 52, m_fgauge);
		IMAGEMANAGER->findImage("barTop")->render(hdc, WINSIZEX-80, WINSIZEY / 2 - 90, 82, 159, 0, 0, 164, 318);
	}

}

void progressBar::setGauge(float currGauge, float maxGauge)
{
	m_fgauge = ( (currGauge / maxGauge) * m_imgBottom->getHeight());
	m_nLenght = 110 * (currGauge / maxGauge);
}

progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}
