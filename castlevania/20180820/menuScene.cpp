#include "stdafx.h"
#include "menuScene.h"
#include "player.h"


HRESULT menuScene::init()
{
	m_imgMenu = IMAGEMANAGER->addImage("image/menu.bmp", "image/menu.bmp", WINSIZEX, WINSIZEY, false, 0);

	m_pPlayer = g_mainGame.getPlayer();


	return S_OK;
}

void menuScene::release()
{
}

void menuScene::update()
{
}

void menuScene::render(HDC hdc)
{
	HFONT hFont= CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Slabberton");;
	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);


	menuRander(hdc, hFont, oldFont);

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
}

void menuScene::menuRander(HDC hdc,HFONT hFont, HFONT oldFont)
{


	char str[300];

	m_imgMenu->render(hdc, 0, 0);


	// 1. 폰트 추가하기. 
	AddFontResourceA("font/Slabberton.ttf");


	SetTextColor(hdc, RGB(243, 122, 40));
	sprintf_s(str, "HP   ");
	TextOut(hdc, WINSIZEX / 2 - 120, 50, str, lstrlen(str));

	sprintf_s(str, "ATT   %d", m_pPlayer->getState().currAtt);
	TextOut(hdc, WINSIZEX / 2 + 80, 120, str, lstrlen(str));

	SetTextColor(hdc, RGB(126, 117, 255));

	sprintf_s(str, "MP   ");
	TextOut(hdc, WINSIZEX / 2 - 120, 80, str, lstrlen(str));

	sprintf_s(str, "DEF   %d", m_pPlayer->getState().currDef);
	TextOut(hdc, WINSIZEX / 2 + 80, 150, str, lstrlen(str));




	SetTextColor(hdc, RGB(255, 255, 255));
	sprintf_s(str, " %d", m_pPlayer->getState().curHP);
	TextOut(hdc, WINSIZEX / 2 - 60, 50, str, lstrlen(str));

	sprintf_s(str, "/  %d", m_pPlayer->getState().fullHP);
	TextOut(hdc, WINSIZEX / 2 + 15, 50, str, lstrlen(str));

	sprintf_s(str, " %d", m_pPlayer->getState().curMP);
	TextOut(hdc, WINSIZEX / 2 - 60, 80, str, lstrlen(str));

	sprintf_s(str, "/  %d", m_pPlayer->getState().fullMP);
	TextOut(hdc, WINSIZEX / 2 + 15, 80, str, lstrlen(str));




	sprintf_s(str, "STR   %d", m_pPlayer->getState().curStr);
	TextOut(hdc, WINSIZEX / 2 - 120, 120, str, lstrlen(str));

	sprintf_s(str, "CON   %d", m_pPlayer->getState().curCon);
	TextOut(hdc, WINSIZEX / 2 - 120, 150, str, lstrlen(str));

	sprintf_s(str, "INT   %d", m_pPlayer->getState().curCon);
	TextOut(hdc, WINSIZEX / 2 - 120, 180, str, lstrlen(str));

	sprintf_s(str, "LCK   %d", m_pPlayer->getState().currLck);
	TextOut(hdc, WINSIZEX / 2 - 120, 210, str, lstrlen(str));





}

menuScene::menuScene()
{
}


menuScene::~menuScene()
{
}
