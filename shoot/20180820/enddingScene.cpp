#include "stdafx.h"
#include "enddingScene.h"


HRESULT enddingScene::init()
{
	m_imgBG=IMAGEMANAGER->addImage("image/endding.bmp", "image/endding.bmp",WINSIZEX,WINSIZEY,true,RGB(255,0,255));
	m_falphaNum = 0;

	g_mainGame.setSaveX(0);
	return S_OK;
}

void enddingScene::release()
{
}

void enddingScene::update()
{

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && m_falphaNum >= 100)
	{
		SCENEMANAGER->changeScene("title");
	}
	if (m_falphaNum <= 100)
	{
		m_falphaNum += 0.5f;
	}
	else
	{
		m_falphaNum = 100;
	}

}

void enddingScene::render(HDC hdc)
{
	m_imgBG->alphaRender(hdc, 0, 0, m_falphaNum);
	if(m_falphaNum>=100)
		IMAGEMANAGER->findImage("image/anybutton.bmp")->render(hdc, WINSIZEX / 2 - 181, WINSIZEY / 2 + 200);
}

enddingScene::enddingScene()
{
}


enddingScene::~enddingScene()
{
}
