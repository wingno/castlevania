#include "stdafx.h"
#include "titleScene.h"


HRESULT titleScene::init()
{
	m_pBG = IMAGEMANAGER->addImage("titleBG", "image/titlebackground.bmp"
		, 600, 600,false,RGB(0,0,0));

	return S_OK;
}

void titleScene::release()
{
}

void titleScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SCENEMANAGER->changeScene("select");
	}
}

void titleScene::render(HDC hdc)
{
	char str[128];

	sprintf_s(str, 128, "Title Scene !!");
	
	m_pBG->render(hdc, 0, 0);


	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 0, 0));
	TextOut(hdc, WINSIZEX / 2 - 50, WINSIZEY / 2, str, strlen(str));
}

titleScene::titleScene()
{
}


titleScene::~titleScene()
{
}
