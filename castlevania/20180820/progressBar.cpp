#include "stdafx.h"
#include "progressBar.h"

HRESULT progressBar::init(float x, float y)
{
	m_nMenuX = x;
	m_nMenuY = y;
	
	m_fHpX = m_nMenuX +109;
	m_fHpY = m_nMenuY + 24.5f;


	m_fMpX = m_nMenuX + 109;
	m_fMpY = m_nMenuY + 40;

	m_imgeMenuProgress = IMAGEMANAGER->addImage("progressbar",
		"image/object/progressbar.bmp", 122, 30, true, RGB(0, 128, 0));
	m_imgHP = IMAGEMANAGER->addImage("HP",
		"image/object/HP.bmp", m_fWidth, 5, true, RGB(0, 128, 0));
	m_imgMP = IMAGEMANAGER->addImage("MP",
		"image/object/MP.bmp", 10, 5, true, RGB(0, 128, 0));


	//m_rc = RectMake(m_nMenuX, m_nMenuY, 
	//	m_imgeMenuProgress->getWidth(), m_imgeMenuProgress->getHeight()*3);
	//m_rc = RectMake(m_fHpX, m_fHpY, m_imgHP->getWidth()*3, m_imgHP->getHeight()*3);
	//m_rc = RectMake(m_fMpX, m_fMpX, m_imgMP->getWidth() * 3,m_imgMP->getHeight()*3);



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

	Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	IMAGEMANAGER->findImage("progressbar")->render(hdc, m_nMenuX, m_nMenuY,3);
	IMAGEMANAGER->findImage("HP")->render(hdc, m_fHpX, m_fHpY,3);
	IMAGEMANAGER->findImage("MP")->render(hdc, m_fMpX, m_fMpY, 3);
	//IMAGEMANAGER->findImage("barTop")->render(hdc, m_fX, m_fY,
	//	0, 0, m_fWidth, m_imgHP->getHeight());
}

void progressBar::setGauge(float currGauge, float maxGauge)
{
	m_fWidth = (currGauge / maxGauge) * m_imgHP->getWidth();

}

progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}
