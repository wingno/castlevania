#include "stdafx.h"
#include "gameoverScene.h"


HRESULT gameoverScene::init()
{

	m_pBG = IMAGEMANAGER->addImage("image/gameover.bmp", "image/gameover.bmp"
		, WINSIZEX, WINSIZEY);


	return S_OK;
}

void gameoverScene::release()
{
}

void gameoverScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SCENEMANAGER->changeScene("battle");
	}
}

void gameoverScene::render(HDC hdc)
{
	m_pBG->render(hdc, 0, 0);
}

gameoverScene::gameoverScene()
{
}


gameoverScene::~gameoverScene()
{
}
