#include "stdafx.h"
#include "scoreBoard.h"


HRESULT scoreBoard::init()
{
	m_imgBoard = IMAGEMANAGER->addImage("image/frame_townlabel_bg.bmp", "image/frame_townlabel_bg.bmp", 200, 44, true, RGB(255, 0, 255));
	m_imgNum = IMAGEMANAGER->addImage("image/number.bmp", "image/number.bmp", 170, 16,10,1, true, RGB(255, 0, 255));

	return S_OK;
}

void scoreBoard::release()
{
}

void scoreBoard::update()
{
	
}

void scoreBoard::render(HDC hdc)
{
	m_imgBoard->render(hdc, WINSIZEX / 2 - 100, 10);

	int number=9;

	if (g_mainGame.getScore()>=1000000)
	{
		m_imgNum->frameRender(hdc, WINSIZEX / 2 - 60, 23, number, 0);
		m_imgNum->frameRender(hdc, WINSIZEX / 2 - 40, 23, number, 0);
		m_imgNum->frameRender(hdc, WINSIZEX / 2 - 20, 23, number, 0);
		m_imgNum->frameRender(hdc, WINSIZEX / 2 - 0, 23, number, 0);
		m_imgNum->frameRender(hdc, WINSIZEX / 2 + 20, 23, number, 0);
		m_imgNum->frameRender(hdc, WINSIZEX / 2 + 40, 23, number, 0);
	}
	else
	{
		number = (g_mainGame.getScore() / 100000);
		m_imgNum->frameRender(hdc, WINSIZEX / 2 - 60, 23, number, 0);
		number = (g_mainGame.getScore() / 10000) - ((g_mainGame.getScore() / 100000) * 10);
		m_imgNum->frameRender(hdc, WINSIZEX / 2 - 40, 23, number, 0);
		number = (g_mainGame.getScore() / 1000) - ((g_mainGame.getScore() / 10000) * 10);
		m_imgNum->frameRender(hdc, WINSIZEX / 2 - 20, 23, number, 0);
		number = (g_mainGame.getScore() / 100) - ((g_mainGame.getScore() / 1000) * 10);
		m_imgNum->frameRender(hdc, WINSIZEX / 2 - 0, 23, number, 0);
		number = (g_mainGame.getScore() / 10) -((g_mainGame.getScore() / 100)*10);
		m_imgNum->frameRender(hdc, WINSIZEX / 2 + 20, 23, number, 0);
		number =  (g_mainGame.getScore() % 10);
		m_imgNum->frameRender(hdc, WINSIZEX / 2 + 40, 23, number, 0);
	}

}

scoreBoard::scoreBoard()
{
}


scoreBoard::~scoreBoard()
{
}
