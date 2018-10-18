#include "stdafx.h"
#include "balore.h"
#include "room.h"
#include "player.h"


HRESULT balore::init()
{
	m_pPlayer = g_mainGame.getPlayer();
	m_imgEye= IMAGEMANAGER->addImage("image/eye.bmp", "image/eye.bmp", 29, 29, true, RGB(84, 109, 142));
	m_imgHead= IMAGEMANAGER->addImage("image/head.bmp", "image/head.bmp", 864, 65,8 ,1, true, RGB(84, 109, 142));


	m_imgRHand = IMAGEMANAGER->addImage("image/Rhand.bmp", "image/Rhand.bmp", 100, 100, true, RGB(84, 109, 142));
	m_imgRarm = IMAGEMANAGER->addImage("image/Rarm.bmp", "image/Rarm.bmp", 100, 100, true, RGB(84, 109, 142));
	m_imgLHand = IMAGEMANAGER->addImage("image/Lhand.bmp", "image/Lhand.bmp", 100, 100, true, RGB(84, 109, 142));
	m_imgLarm = IMAGEMANAGER->addImage("image/Larm.bmp", "image/Larm.bmp", 100, 100, true, RGB(84, 109, 142));



	m_bIsAlive = true;

	m_fMapX = 220*3;
	m_fMapY = 50*3;

	m_lArmMapY  =m_fY+ 150;
	m_lArmMapX = 950;
	m_RArmMapY = m_fY + 150;
	m_RArmMapX = 400;

	m_nWhereSee = 0;

	m_nPhase = 1;


	return S_OK;
}

void balore::release()
{
}	

void balore::update()
{
	m_fX = m_fMapX - ROOMMANAGER->getCurrRoom()->getPosMap().x;
	m_fY = m_fMapY - ROOMMANAGER->getCurrRoom()->getPosMap().y;

	m_lArmY= m_lArmMapY - ROOMMANAGER->getCurrRoom()->getPosMap().y;
	m_RArmY = m_RArmMapY - ROOMMANAGER->getCurrRoom()->getPosMap().y;
	m_lArmX= m_lArmMapX - ROOMMANAGER->getCurrRoom()->getPosMap().x;
	m_RArmX= m_RArmMapX - ROOMMANAGER->getCurrRoom()->getPosMap().x;


	if (m_pPlayer->getFx()+ ROOMMANAGER->getCurrRoom()->getPosMap().x < 220 * 3)
	{
		m_nWhereSee = 3;
	}
	else if (m_pPlayer->getFx()+ ROOMMANAGER->getCurrRoom()->getPosMap().x < 290 * 3)
	{
		m_nWhereSee = 1;
	}
	else
	{
		m_nWhereSee = 2;
	}



}

void balore::headRender(HDC hdc)
{
	if (m_nPhase==1)
	{

		switch (m_nWhereSee)
		{
		case 1:
			m_imgEye->render(hdc, m_fX + 125, m_fY - m_imgHead->getFrameHeight() / 2 + 37 - ((START_Y - m_pPlayer->getFY()) / 15), 3);
			break;
		case 2:
			m_imgEye->render(hdc, m_fX + 122, m_fY - m_imgHead->getFrameHeight() / 2 + 52 - ((START_Y - m_pPlayer->getFY()) / 15), 3);
			break;
		case 3:
			m_imgEye->render(hdc, m_fX + 120, m_fY - m_imgHead->getFrameHeight() / 2 + 45 - ((START_Y - m_pPlayer->getFY()) / 15), 3);
			break;
		default:
			break;
		}
		
		m_imgHead->frameRender(hdc, m_fX - m_imgHead->getFrameWidth() / 2, m_fY - m_imgHead->getFrameHeight() / 2, m_nWhereSee, 1,3);

	}

}

void balore::armRender(HDC hdc)
{
	//if (m_nPhase == 1)
	//{
	//	m_imgHead->frameRender(hdc, m_fX - m_imgHead->getFrameWidth() / 2, m_fY - m_imgHead->getFrameHeight() / 2, m_nWhereSee, 1, 3);
	//}

	m_imgRarm->rotateRender(hdc, 0, m_RArmX, m_lArmY - m_imgHead->getFrameHeight() / 2 + 52, 0.5f, 0.5f, 3);
	m_imgLarm->rotateRender(hdc, 0, m_lArmX, m_RArmY - m_imgHead->getFrameHeight() / 2 + 52, 0.5f, 0.5f, 3);
	m_imgRHand->rotateRender(hdc, 0, m_RArmX +100, m_RArmY - m_imgHead->getFrameHeight() / 2 + 52, 0.5f, 0.5f, 3);
	m_imgLHand->rotateRender(hdc, 0, m_lArmX-100, m_lArmY - m_imgHead->getFrameHeight() / 2 + 52, 0.5f, 0.5f, 3);
}

balore::balore()
{
}


balore::~balore()
{
}
