#include "stdafx.h"
#include "mainGame.h"
#include "titleScene.h"
#include "battleScene.h"
#include "enddingScene.h"
#include "gameoverScene.h"



void mainGame::setBackBuffer()
{
	m_pBackBuffer = new image;
	m_pBackBuffer->init(WINSIZEX+30, WINSIZEY);
}

HRESULT mainGame::init()
{
	hdc = GetDC(g_hWnd);

	//HANDLE hTimer = (HANDLE)SetTimer(g_hWnd, 1, 10, NULL);
	KEYMANAGER->init();
	IMAGEMANAGER->init();
	TIMEMANAGER->init();
	SCENEMANAGER->init();

	setBackBuffer();

	// 필요한 리소스 미리 로드
	m_nSaveX =0;
	// scene test
	m_pTitleScene = new titleScene;
	SCENEMANAGER->addScene("title", m_pTitleScene);

	m_pBattleScene = new battleScene;
	SCENEMANAGER->addScene("battle", m_pBattleScene);

	m_penddingScene = new enddingScene;
	SCENEMANAGER->addScene("endding", m_penddingScene);

	m_pGameoverScene = new gameoverScene;
	SCENEMANAGER->addScene("gameover",  m_pGameoverScene);

	//m_pLoadingScene = new loadingScene_1;
	//SCENEMANAGER->addLoadingScene("loading_1", m_pLoadingScene);
	
	SCENEMANAGER->changeScene("title");

	m_bIsSlice = false;


	return S_OK;
}

void mainGame::release()
{
	// 씬 매니저 내부(SCENEMANAGER->release())에서 처리하므로
	// 여기서는 삭제
	//m_pBattleScene->release();
	//SAFE_DELETE(m_pBattleScene);

	//m_pTitleScene->release();
	//SAFE_DELETE(m_pTitleScene);

	SAFE_DELETE(m_pBackBuffer);

	//KillTimer(g_hWnd, 1);
	ReleaseDC(g_hWnd, hdc);

	KEYMANAGER->release();
	IMAGEMANAGER->release();
	TIMEMANAGER->release();
	SCENEMANAGER->release();

	KEYMANAGER->releaseSingleton();
	IMAGEMANAGER->releaseSingleton();
	TIMEMANAGER->releaseSingleton();
	SCENEMANAGER->releaseSingleton();

}

LRESULT mainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;

		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	//case WM_COMMAND:
	//	switch (LOWORD(wParam))
	//	{
	//	case 0:
	//		m_pTileMapScene->mapSave();
	//		break;
	//	case 1:
	//		m_pTileMapScene->mapLoad();
	//		break;
	//	case 2:
	//		m_pTileMapScene->tilePrint();
	//		break;
	//	case 3:
	//		m_pTileMapScene->objectPrint();
	//		break;
	//	case 4:
	//		m_pTileMapScene->tileEraser();
	//		break;
	//	default:
	//		break;
	//	}
	//	break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

void mainGame::update()
{

	InvalidateRect(g_hWnd, NULL, false);
	SCENEMANAGER->update();
}

void mainGame::render()
{
	HDC backDC = m_pBackBuffer->getMemDC();



	SCENEMANAGER->render(backDC);

	

	if (m_bIsSlice)
	{
		
		HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));

		RECT rc;
		rc.top = WINSIZEY / 2 - 5;
		rc.bottom = rc.top + 10;
		rc.left = 0;
		rc.right = WINSIZEX;

		FillRect(m_pBackBuffer->getMemDC(), &rc, brush);

		m_pBackBuffer->setTransColor(true,RGB(255, 0, 255));

		m_pBackBuffer->render(hdc, -30, 0,WINSIZEX+30,WINSIZEY/2,0,0, WINSIZEX+30, WINSIZEY / 2);
		//m_pBackBuffer->render(hdc, 0, 0,0,0,WINSIZEX-1,WINSIZEY/2 );
		//m_pBackBuffer->render(hdc, 30, WINSIZEY/2, 0, WINSIZEY, WINSIZEX, WINSIZEY / 2);
		m_pBackBuffer->setIsTransparent(false);
	}
	else
	{
		m_pBackBuffer->render(hdc, 0, 0);
	}

}

mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}
