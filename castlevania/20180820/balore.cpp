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

	m_fLHandMapY=m_fLArmMapY  =m_fY+ 150;
	m_fLHandMapX= m_fLArmMapX = 950;
	m_fRHandMapY =m_fRArmMapY = m_fY + 150;
	m_fRHandMapX= m_fRArmMapX = 400;

	m_nWhereSee = 0;

	m_nPhase = 1;

	m_nPattern = 1;

	m_fRArmAngle =m_fLArmAngle = 0;

	m_bIsUp = true;

	m_bIsLeft = true;

	m_bIsPatternEnd = false;

	return S_OK;
}

void balore::release()
{
}	

void balore::update()
{
	m_fX = m_fMapX - ROOMMANAGER->getCurrRoom()->getPosMap().x;
	m_fY = m_fMapY - ROOMMANAGER->getCurrRoom()->getPosMap().y;

	if (m_pPlayer->getFx() + ROOMMANAGER->getCurrRoom()->getPosMap().x < 220 * 3)
	{
		m_nWhereSee = 3;
	}
	else if (m_pPlayer->getFx() + ROOMMANAGER->getCurrRoom()->getPosMap().x < 290 * 3)
	{
		m_nWhereSee = 1;
	}
	else
	{
		m_nWhereSee = 2;

	}

	switch (m_nPhase)
	{
		case 1:
			phase1Update();
			break;

		case 2:

			break;

		default:
			break;
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

	m_imgRarm->rotateRender(hdc, -m_fRArmAngle, m_fRArmX, m_fRArmY - m_imgHead->getFrameHeight() / 2 + 52, 0.5f, 0.5f, 3);
	m_imgLarm->rotateRender(hdc, m_fLArmAngle, m_fLArmX, m_fLArmY - m_imgHead->getFrameHeight() / 2 + 52, 0.5f, 0.5f, 3);
	m_imgRHand->rotateRender(hdc, -m_fRArmAngle, m_fRHandX +100, m_fRHandY - m_imgHead->getFrameHeight() / 2 + 52, 0.5f, 0.5f, 3);
	m_imgLHand->rotateRender(hdc, m_fLArmAngle, m_fLHandX-100, m_fLHandY - m_imgHead->getFrameHeight() / 2 + 52, 0.5f, 0.5f, 3);
}

void balore::phase1Update()
{

	m_fLArmY = m_fLArmMapY - ROOMMANAGER->getCurrRoom()->getPosMap().y;
	m_fRArmY = m_fRArmMapY - ROOMMANAGER->getCurrRoom()->getPosMap().y;
	m_fLArmX = m_fLArmMapX - ROOMMANAGER->getCurrRoom()->getPosMap().x;
	m_fRArmX = m_fRArmMapX - ROOMMANAGER->getCurrRoom()->getPosMap().x;


	m_fLHandY = m_fLHandMapY - ROOMMANAGER->getCurrRoom()->getPosMap().y;
	m_fRHandY = m_fRHandMapY - ROOMMANAGER->getCurrRoom()->getPosMap().y;
	m_fLHandX = m_fLHandMapX - ROOMMANAGER->getCurrRoom()->getPosMap().x;
	m_fRHandX = m_fRHandMapX - ROOMMANAGER->getCurrRoom()->getPosMap().x;

	if (m_bIsPatternEnd)
	{
		if (START_ARMY < m_fRArmMapY)
		{
			m_fRArmMapY--;
			m_fRHandMapY -= 1.2;
		}
		else if(START_ARMY > m_fRArmMapY)
		{
			m_fRArmMapY++;
			m_fRHandMapY += 1.2;
		}

		if (START_ARMY < m_fLArmMapY)
		{
			m_fLArmMapY--;
			m_fLHandMapY -= 1.2;
		}
		else if (START_ARMY > m_fLArmMapY)
		{
			m_fLArmMapY++;
			m_fLHandMapY += 1.2;
		}




		if (400 < m_fRHandMapX)
		{
			m_fRArmMapX--;
			m_fRHandMapX --;
		}
		else if (400 > m_fRHandMapX)
		{
			m_fRArmMapX++;
			m_fRHandMapX ++;
		}

		if (950 < m_fLHandMapX)
		{
			m_fLArmMapX--;
			m_fLHandMapX --;
		}
		else if (950 > m_fLHandMapX)
		{
			m_fLArmMapX++;
			m_fLHandMapX++;
		}

		if ((m_fRArmMapY == START_ARMY)&&( m_fLArmMapY == START_ARMY) && (m_fLHandMapX == 950) && (400 == m_fRHandMapX))
		{
			m_bIsPatternEnd = false;
		}

	}
	else
	{
		m_bIsPatternEnd = false;

		switch (m_nPattern)
		{
			case 0:

				if (m_bIsUp)
				{
					m_fRArmMapY -= 2;
					m_fRHandMapY -= 2.4;

					m_fLArmMapY -= 2;
					m_fLHandMapY -= 2.4;

					m_fLArmMapX++;
					m_fRArmMapX--;
					m_fLHandMapX++;
					m_fRHandMapX--;
				}
				else
				{
					m_fRArmMapY += 8;
					m_fRHandMapY += 9.6;

					m_fLArmMapY += 8;
					m_fLHandMapY += 9.6;

					m_fLArmMapX -= 4;
					m_fRArmMapX += 4;
					m_fLHandMapX -= 4;
					m_fRHandMapX += 4;
				}



				if (m_fRArmMapY < -20)
				{
					m_bIsUp = false;
				}
				else if (m_fRArmMapY > 250)
				{
					m_bIsUp = true;
					m_bIsPatternEnd = true;
					m_nPattern = 1;
				}

				break;

			case 1:

				if (m_bIsLeft)
				{
					//m_fRArmMapY -= 2;
					//m_fRHandMapY -= 2.4;

					//m_fLArmMapY -= 2;
					//m_fLHandMapY -= 2.4;

					m_fLArmMapX+=2;
					m_fRArmMapX-=2;
					m_fLHandMapX+=2;
					m_fRHandMapX-=2;
				}
				else
				{
					m_fRArmMapY -= 2;
					m_fRHandMapY -= 2.4;

					m_fLArmMapY += 2;
					m_fLHandMapY += 2.4;

					m_fLArmMapX -= 8;
					m_fRArmMapX += 8;
					m_fLHandMapX -= 8;
					m_fRHandMapX += 8;
				}



				if (m_fRArmMapX < 200)
				{
					m_bIsLeft = false;
				}
				else if (m_fRArmMapX > 600)
				{
					m_bIsLeft = true;
					m_bIsPatternEnd = true;
					m_nPattern = 0;
				}
				break;


			default:
				break;
		}

	}



	m_fRArmAngle = ((START_ARMY - m_fRArmMapY) * 10)*(PI / 180);
	m_fLArmAngle = ((START_ARMY - m_fLArmMapY) * 10)*(PI / 180);




}

balore::balore()
{
}


balore::~balore()
{
}
