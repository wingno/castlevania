#include "stdafx.h"
#include "titleScene.h"


HRESULT titleScene::init()
{
	m_intro = IMAGEMANAGER->addImage("intro", "image/introcopy.bmp", 5280, 320, 22, 2, true, RGB(255, 0, 255));
	title1 = true;
	fIdx, Fcount, FX, FY = 0;

	m_select = IMAGEMANAGER->addImage("select", "image/title.bmp", 75, 75, 1, 3, true, RGB(255, 0, 255));
	m_select2 = IMAGEMANAGER->addImage("menu", "image/since.bmp", 232, 16, 1, 1, true, RGB(255, 0, 255));

	title2 = false;
	menuX = 210;
	menuY = 350;
	m_rc = RectMakeCenter(menuX, menuY, m_select->getWidth() / 2, m_select->getHeight() / 2);


	menuX2 = -20;
	menuY2 = 430;
	m_rc = RectMakeCenter(menuX2, menuY2, m_select2->getWidth() / 2, m_select2->getHeight() / 2);


	return S_OK;
}

void titleScene::release()
{
}

void titleScene::update()
{
	if (title1)
	{

		fIdx++;
		if (fIdx % 7 == 0)
		{

			FX++;
			if (FX > 21)
			{
				Fcount++;
				FX = 0;

				FY = 1;

			}

		}

		if (Fcount == 2)
		{
			FX = 22;
			title1 = false;
			title2 = true;
			Fcount = 0;

		}

	}

	if (title2)
	{


		if (menuFY < 1)
		{
			menuFY = 1;
		}
		if (menuFY > 2)
		{
			menuFY = 2;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			menuFY += 1;


		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			menuFY -= 1;

		}
		if (menuFY == 1)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				SCENEMANAGER->changeScene("battle");
			}
		}


	}




}

void titleScene::render(HDC hdc)
{
	if (title1)
	{
		m_intro->frameRender(hdc, 0, 0, FX, FY, WINSIZEX, WINSIZEY);
	}

	if (title2)
	{

		m_select->frameRender(hdc, menuX, menuY, 0, menuFY, 3);
		m_select2->frameRender(hdc, menuX2, menuY2, 0, 0, 3);

	}

}

titleScene::titleScene()
{
}


titleScene::~titleScene()
{
}
