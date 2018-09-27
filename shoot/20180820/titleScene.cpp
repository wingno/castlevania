#include "stdafx.h"
#include "titleScene.h"


HRESULT titleScene::init()
{
	//Sleep(1500);

	m_pBG = IMAGEMANAGER->addImage("titleBG", "image/titlebg.bmp"
		, WINSIZEX, WINSIZEY);

	m_imgGuide = IMAGEMANAGER->addImage("image/anybutton.bmp", "image/anybutton.bmp", 362, 25, true, RGB(255, 0, 255));

	m_nCount = 0;

	return S_OK;
}

void titleScene::release()
{
}

void titleScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SCENEMANAGER->changeScene("battle");
	}
	m_nCount++;
	if (m_nCount > 100)
	{
		m_nCount = 0;
	}
	else
	{
		m_nCount++;
	}
}

void titleScene::render(HDC hdc)
{

	
	m_pBG->render(hdc, 0, 0);

	if (m_nCount <= 50)
	{
		m_imgGuide->render(hdc, WINSIZEX / 2-181, WINSIZEY/2 + 200);

	}





}

titleScene::titleScene()
{
}


titleScene::~titleScene()
{
}
