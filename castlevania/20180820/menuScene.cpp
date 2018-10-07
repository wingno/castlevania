#include "stdafx.h"
#include "menuScene.h"
#include "player.h"
#include "menuProgressBar.h"



HRESULT menuScene::init()
{
	m_imgMenu = IMAGEMANAGER->addImage("image/menu.bmp", "image/menu.bmp", WINSIZEX, WINSIZEY, false, 0);

	m_imgSoulSet = IMAGEMANAGER->addImage("image/soul.bmp", "image/soul.bmp", WINSIZEX, WINSIZEY, false, 0);

	m_imgEquit= IMAGEMANAGER->addImage("image/arms.bmp", "image/arms.bmp", WINSIZEX, WINSIZEY, false, 0);

	m_imgSeleter = IMAGEMANAGER->addImage("image/seleter.bmp", "image/seleter.bmp", 16, 16, true, RGB(255,0,255));

	m_imgLArrow = IMAGEMANAGER->addImage("image/leftArrow.bmp", "image/leftArrow.bmp", 17, 21, true, RGB(255, 0, 255));
	
	m_imgRArrow = IMAGEMANAGER->addImage("image/rightArrow.bmp", "image/rightArrow.bmp", 17, 21, true, RGB(255, 0, 255));

	m_imgEmptySoul= IMAGEMANAGER->addImage("image/4303.bmp", "image/4303.bmp", 16, 16, true, RGB(255, 0, 255));

	m_pPlayer = g_mainGame.getPlayer();

	m_pHpBar = new menuProgressBar;

	m_pMpBar = new menuProgressBar;

	m_pHpBar->init(WINSIZEX / 2 + 100, 50, 190, 24, true);

	m_pMpBar->init(WINSIZEX / 2 + 100, 80, 190, 24, false);

	m_pHpBar->setGauge(m_pPlayer->getState().curHP, m_pPlayer->getState().fullHP);
	m_pMpBar->setGauge(m_pPlayer->getState().curMP, m_pPlayer->getState().fullMP);

	m_seleter = {0,0,true,2.5f};

	m_state = MENU;

	m_bIsChangeScene = false;

	m_nAlphaNum = 0;

	m_nSetStep = 0;

	m_nTypeSelet = 0;

	return S_OK;
}

void menuScene::release()
{

	SAFE_DELETE(m_pHpBar);
	SAFE_DELETE(m_pMpBar);
}

void menuScene::update()
{
	switch (m_state)
	{
	case MENU:
		menuUpdate();
		break;
	case SOUL_SET:
		sourSetupdate();
		break;
	case EQUIT:
		equitupdate();
		break;
	case ITEM:
		break;

	default:
		break;
	}

	if (m_state != MENU)
	{
		if (KEYMANAGER->isOnceKeyDown('X')&& m_nSetStep==0)
		{
			m_state = MENU;
			m_nTypeSelet = 0;
		}

		
	}
	else
	{
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			m_bIsChangeScene = true;
		}
	}



	if (m_bIsChangeScene)
	{
		
		
		if (m_nAlphaNum < 200)
		{
			m_nAlphaNum+=50;
		}
		else
		{
			m_pPlayer->setIsJump(false);
			SCENEMANAGER->changeScene("battle");
		}

	}
}

void menuScene::render(HDC hdc)
{
	AddFontResourceA("font/Slabberton.ttf");

	HFONT hFont= CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Slabberton");;
	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);


	switch (m_state)
	{
	case MENU:
		menuRander(hdc, hFont, oldFont);
		break;
	case SOUL_SET:
		sourSetRander(hdc, hFont, oldFont);
		break;
	case EQUIT:
		equitRander(hdc, hFont, oldFont);
		break;
	case ITEM:
		break;

	default:
		break;
	}

	if (m_seleter.SelectMover <= 0)
	{
		m_seleter.isLeft = true;
	}
	else if (m_seleter.SelectMover >= 30)
	{
		m_seleter.isLeft = false;
	}

	if (m_seleter.isLeft)
		m_seleter.SelectMover += m_seleter.speed;
	else
		m_seleter.SelectMover -= m_seleter.speed;

	

	if (m_bIsChangeScene)
	{
		IMAGEMANAGER->findImage("background")->alphaRender(hdc, m_nAlphaNum);

	}

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
}

void menuScene::menuRander(HDC hdc,HFONT hFont, HFONT oldFont)
{


	char str[300];

	m_imgMenu->render(hdc, 0, 0);



	// 1. 폰트 추가하기. 



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


	//경험치
	sprintf_s(str, "EXP           %d", m_pPlayer->getState().exp);
	TextOut(hdc, WINSIZEX / 2 - 40, 290, str, lstrlen(str));

	sprintf_s(str, "NEXT         %d", m_pPlayer->getState().nextExp- m_pPlayer->getState().exp);
	TextOut(hdc, WINSIZEX / 2 - 40, 310, str, lstrlen(str));

	//돈
	SetTextColor(hdc, RGB(243, 206, 91));
	sprintf_s(str, "GOLD : %d   ",m_pPlayer->getGold());
	TextOut(hdc, WINSIZEX / 2+50, 210, str, lstrlen(str));


	//메뉴바
	SetTextColor(hdc, RGB(158, 159, 153));

	sprintf_s(str, "SOUL SET");
	TextOut(hdc, 40, 290, str, lstrlen(str));

	sprintf_s(str, "EQUIP");
	TextOut(hdc, 40, 330, str, lstrlen(str));

	sprintf_s(str, "ITEM USE");
	TextOut(hdc, 40, 370, str, lstrlen(str));

	sprintf_s(str, "EXIT");
	TextOut(hdc, 40, 410, str, lstrlen(str));




	SetTextColor(hdc, RGB(255, 255, 255));
	switch (m_seleter.Select)
	{
		case 0:
			sprintf_s(str, "SOUL SET");
			TextOut(hdc, 40, 290, str, lstrlen(str));
			break;
		case 1:
			sprintf_s(str, "EQUIP");
			TextOut(hdc, 40, 330, str, lstrlen(str));
			break;
		case 2:
			sprintf_s(str, "ITEM USE");
			TextOut(hdc, 40, 370, str, lstrlen(str));
			break;
		case 3:
			sprintf_s(str, "EXIT");
			TextOut(hdc, 40, 410, str, lstrlen(str));
			break;
		default:
			break;
	}


	m_imgSeleter->render(hdc, -5- m_seleter.SelectMover, 270 + (40*m_seleter.Select), 3);


	m_pHpBar->render(hdc);
	m_pMpBar->render(hdc);



}

void menuScene::menuUpdate()
{
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (m_seleter.Select > 0)
		{
			m_seleter.Select--;

		}
		else
		{
			m_seleter.Select = 3;
		}

	}
	else if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{

		if (m_seleter.Select < 3)
		{
			m_seleter.Select++;

		}
		else
		{
			m_seleter.Select = 0;
		}
		
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		switch (m_seleter.Select)
		{
		case 0:
			m_state = SOUL_SET;
			break;
		case 1:
			m_state = EQUIT;
			break;
		case 2:
			m_state = ITEM;
			break;
		case 3:
			m_bIsChangeScene = true;
			break;
		default:
			break;
		}
	}



}

void menuScene::sourSetRander(HDC hdc, HFONT hFont, HFONT oldFont)
{



	m_imgSoulSet->render(hdc, 0, 0);

	m_imgSeleter->render(hdc, m_nSetStep==0? - m_seleter.SelectMover:0, 80 + (40 * m_nTypeSelet), 3);

	//m_imgSeleter->render(hdc, 0 , 80 + (40 * m_TypeSelet), 3);
	if (m_nSetStep == 0)
	{
		m_imgLArrow->render(hdc, 20 - m_seleter.SelectMover/3, 60);
		m_imgRArrow->render(hdc, 325 + m_seleter.SelectMover/3, 60);

	}

	if(m_nSetStep==1)
		m_imgSeleter->render(hdc, -m_seleter.SelectMover, WINSIZEY/2-10, 3);


	fontPrint(hdc);


}

void menuScene::sourSetupdate()
{

	switch (m_nSetStep)
	{
	case 0:
		if (m_nSetStep == 0 && (KEYMANAGER->isOnceKeyDown(VK_LEFT) || KEYMANAGER->isOnceKeyDown(VK_RIGHT)))
		{
			m_state = EQUIT;
			m_seleter.Select = 1;
			m_nTypeSelet = 0;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (m_nTypeSelet > 0)
			{
				m_nTypeSelet--;

			}
			else
			{
				m_nTypeSelet = 2;
			}

		}
		else if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{

			if (m_nTypeSelet < 2)
			{
				m_nTypeSelet++;

			}
			else
			{
				m_nTypeSelet = 0;
			}

		}

		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			m_nSetStep++;
		}
		break;
	case 1:
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			m_nSetStep--;
		}
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			m_nSetStep--;
		}
		break;
	default:
		break;
	}



}

void menuScene::equitRander(HDC hdc, HFONT hFont, HFONT oldFont)
{
	m_imgEquit->render(hdc, 0, 0);

	m_imgSeleter->render(hdc, m_nSetStep == 0 ? -m_seleter.SelectMover : 0, 80 + (40 * m_nTypeSelet), 3);


	//m_imgSeleter->render(hdc, 0 , 80 + (40 * m_TypeSelet), 3);
	if (m_nSetStep == 0)
	{
		m_imgLArrow->render(hdc, 20 - m_seleter.SelectMover / 3, 60);
		m_imgRArrow->render(hdc, 325 + m_seleter.SelectMover / 3, 60);

	}

	if (m_nSetStep == 1)
		m_imgSeleter->render(hdc, -m_seleter.SelectMover, WINSIZEY / 2 - 10, 3);





	fontPrint(hdc);
}

void menuScene::equitupdate()
{
	if (m_nSetStep == 0 && (KEYMANAGER->isOnceKeyDown(VK_LEFT) || KEYMANAGER->isOnceKeyDown(VK_RIGHT)))
	{
		m_state = SOUL_SET;
		m_seleter.Select = 0;
		m_nTypeSelet = 0;
	}

	switch (m_nSetStep)
	{
	case 0:
		if (m_nSetStep == 0 && (KEYMANAGER->isOnceKeyDown(VK_LEFT) || KEYMANAGER->isOnceKeyDown(VK_RIGHT)))
		{
			m_state = EQUIT;
			m_seleter.Select = 1;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (m_nTypeSelet > 0)
			{
				m_nTypeSelet--;

			}
			else
			{
				m_nTypeSelet = 2;
			}

		}
		else if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{

			if (m_nTypeSelet < 2)
			{
				m_nTypeSelet++;

			}
			else
			{
				m_nTypeSelet = 0;
			}

		}

		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			m_nSetStep++;
		}
		break;
	case 1:
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			m_nSetStep--;
		}

		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			m_nSetStep--;
		}
		break;
	default:
		break;
	}
}

void menuScene::fontPrint(HDC hdc)
{

	char str[300];

	SetTextColor(hdc, RGB(243, 122, 40));


	sprintf_s(str, "ATT      %d", m_pPlayer->getState().currAtt);
	TextOut(hdc, WINSIZEX / 2 + 60, 80, str, lstrlen(str));

	SetTextColor(hdc, RGB(126, 117, 255));

	sprintf_s(str, "DEF      %d", m_pPlayer->getState().currDef);
	TextOut(hdc, WINSIZEX / 2 + 60, 100, str, lstrlen(str));




	SetTextColor(hdc, RGB(255, 255, 255));
	sprintf_s(str, "STR      %d", m_pPlayer->getState().curStr);
	TextOut(hdc, WINSIZEX / 2 + 60, 120, str, lstrlen(str));

	sprintf_s(str, "CON      %d", m_pPlayer->getState().curCon);
	TextOut(hdc, WINSIZEX / 2 + 60, 140, str, lstrlen(str));

	sprintf_s(str, "INT      %d", m_pPlayer->getState().curCon);
	TextOut(hdc, WINSIZEX / 2 + 60, 160, str, lstrlen(str));

	sprintf_s(str, "LCK      %d", m_pPlayer->getState().currLck);
	TextOut(hdc, WINSIZEX / 2 + 60, 180, str, lstrlen(str));



	if (m_state == EQUIT)
	{
		switch (m_nTypeSelet)
		{
		case 0:

			sprintf_s(str, "HAND", m_pPlayer->getState().currLck);
			TextOut(hdc, WINSIZEX / 2 -180,WINSIZEY/2-33, str, lstrlen(str));
			break;
		case 1:
			sprintf_s(str, "BODY", m_pPlayer->getState().currLck);
			TextOut(hdc, WINSIZEX / 2 - 180, WINSIZEY / 2 - 33, str, lstrlen(str));
			break;
		case 2:
			sprintf_s(str, "ACCESSORY", m_pPlayer->getState().currLck);
			TextOut(hdc, WINSIZEX / 2 - 210, WINSIZEY / 2 - 33, str, lstrlen(str));
			break;
		default:
			break;
		}
	}
	else
	{
		switch (m_nTypeSelet)
		{
		case 0:
			sprintf_s(str, "BULLET", m_pPlayer->getState().currLck);
			TextOut(hdc, WINSIZEX / 2 - 190, WINSIZEY / 2 - 33, str, lstrlen(str));
			break;
		case 1:
			sprintf_s(str, "GUARDIAN", m_pPlayer->getState().currLck);
			TextOut(hdc, WINSIZEX / 2 - 210, WINSIZEY / 2 - 33, str, lstrlen(str));
			break;
		case 2:
			sprintf_s(str, "ENCHANT", m_pPlayer->getState().currLck);
			TextOut(hdc, WINSIZEX / 2 - 200, WINSIZEY / 2 - 33, str, lstrlen(str));
			break;
		default:
			break;
		}
	}

}

menuScene::menuScene()
{
}


menuScene::~menuScene()
{
}
