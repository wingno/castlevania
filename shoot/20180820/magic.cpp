#include "stdafx.h"
#include "magic.h"
#include "missileManager.h"


HRESULT magic::init()
{
	m_imgmagic= IMAGEMANAGER->addImage("image/magic.bmp", "image/magic.bmp", 130, 125, true, RGB(255, 0, 255));
	
	m_pMissileMg = new missileManager;
	m_pMissileMg->init("image/bullet.bmp", 200.0f, 10);

	m_fangle = 0;

	m_fX = WINSIZEX - 350;
	m_fY = WINSIZEY / 2 ;

	m_bIsAlive = false;

	return S_OK;
}

void magic::release()
{

}

void magic::update()
{
	if (m_pMissileMg)
	{
		m_pMissileMg->update();
	}

	m_fangle += 1;

	if ((int)m_fangle % 3 == 0)
	{
		m_pMissileMg->fire(m_fX, m_fY , m_fangle, 2.0f);
	}


	if (m_fangle > 900)
	{
		m_bIsAlive = false;
		m_fangle = 0;
	}
}

void magic::render(HDC hdc)
{
	m_imgmagic->rotateRender(hdc, m_fangle, m_fX, m_fY);

	if (m_pMissileMg)
	{
		m_pMissileMg->render(hdc);
	}

}

magic::magic()
{
}


magic::~magic()
{
}
