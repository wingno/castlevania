#include "stdafx.h"
#include "progressBar.h"

HRESULT progressBar::init(float x, float y,float width, float height)
{

	m_fX = x;
	m_fY = y;
	m_fWidth = width ;
	m_fWidthMp = width ;

	m_rc = RectMake(m_fX, m_fY,
		m_fWidth, height);

	
	m_imgHp = IMAGEMANAGER->addImage("HP",

			"image/object/HP.bmp", m_fWidth , height -10 , true, RGB(0, 128, 0));
	
		m_imgMp = IMAGEMANAGER->addImage("MP",
			"image/object/MP.bmp", m_fWidthMp, height -10 , true, RGB(0, 128, 0));


	m_imgeMenuProgress = IMAGEMANAGER->addImage("progressbar",
		"image/object/progressbar.bmp", 140, height, true, RGB(0, 128, 0));


	m_imgNum


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
	/*m_imgBg->render(hdc, 0, 0, 521 + m_posMap.x / 3, 1551 + m_posMap.y / 3, 400, 160, 3);*/
	/*Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);*/
	m_imgeMenuProgress->render(hdc, m_fX, m_fY,3);
	
	m_imgHp->render(hdc, m_fX +120 , m_fY + 19, 0, 0,
		m_fWidth, m_imgHp->getHeight());
	m_imgMp->render(hdc, m_fX + 120, m_fY + 34, 0, 0,
		m_fWidthMp, m_imgMp->getHeight());
	
}


void progressBar::setGauge(float currGauge, float maxGauge
	, float currGaugemp, float maxGaugemp)
{

	m_fWidth = (currGauge / maxGauge) * m_imgHp->getWidth();
	m_fWidthMp = (currGaugemp / maxGaugemp) * m_imgMp->getWidth();
	
}

progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}
