#include "stdafx.h"
#include "mainGame.h"
#include "titleScene.h"
#include "battleScene.h"
#include "scoreScene.h"
#include "selectScene.h"
#include "spaceShip.h"
#include "menuScene.h"
#include "player.h"


/*
	게임 window 창띄우기 (winmain () )

*/

void mainGame::setBackBuffer()
{
	m_pBackBuffer = new image;
	m_pBackBuffer->init(WINSIZEX, WINSIZEY);
}

HRESULT mainGame::init()
{
	hdc = GetDC(g_hWnd);

	//변수
	m_nscore = 0;

	m_pPlayer = new player;
	m_pPlayer->init();

	//HANDLE hTimer = (HANDLE)SetTimer(g_hWnd, 1, 10, NULL);
	KEYMANAGER->init();
	IMAGEMANAGER->init();
	TIMEMANAGER->init();
	EFFECTMANAGER->init();

	setBackBuffer();

	EFFECTMANAGER->addEffect("explosion1", "image/explosion.bmp", 832, 62, 32, 62, 30, 10);



	/*m_pTitleScene = new titleScene;
	SCENEMANAGER->addScene("title", m_pTitleScene);
*/
	m_pBattleScene = new battleScene;
	SCENEMANAGER->addScene("battle", m_pBattleScene);

	m_pmenuScene = new menuScene;
	SCENEMANAGER->addScene("menu", m_pmenuScene);

	//m_pscoreScene = new scoreScene;
	//SCENEMANAGER->addScene("score", m_pscoreScene);

	//m_pselectScene = new selectScene;
	//SCENEMANAGER->addScene("select", m_pselectScene);



	SCENEMANAGER->changeScene("menu");
	

	//m_pBattleScene->setIsScore(&m_nscore);
	//m_pscoreScene->setIsScore(&m_nscore);
	//



	// 낙타 애니메이션 테스트


	// 파일 생성 테스트
	//TXTDATA->txtSave("test.txt");
	//TXTDATA->txtLoad("test.txt");

	// 0 ) 오류 수정
	// 1 )우리반 학생 이름 전부를 넣은 파일 생성
	//vector<string> vec;
	//vec.push_back("이순현");
	//vec.push_back("정지수");
	//vec.push_back("정민욱");
	//vec.push_back("최정수");
	//TXTDATA->txtSave("test1.txt", vec);

	//// 2) 세이브 파일 로드해서 vector에 다시 넣어서 화면에 출력
	//m_vecLoad = TXTDATA->txtLoad("test1.txt");
	



	return S_OK;
}

void mainGame::release()
{


	if (m_pBackBuffer)	delete m_pBackBuffer;

	//KillTimer(g_hWnd, 1);
	ReleaseDC(g_hWnd, hdc);

	TXTDATA->release();
	KEYMANAGER->release();
	IMAGEMANAGER->release();
	TIMEMANAGER->release();
	EFFECTMANAGER->release();
	SCENEMANAGER->release();

	TXTDATA->releaseSingleton();
	KEYMANAGER->releaseSingleton();
	IMAGEMANAGER->releaseSingleton();
	TIMEMANAGER->releaseSingleton();
	SCENEMANAGER->releaseSingleton();

	SAFE_DELETE(m_pPlayer);
}

LRESULT mainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//HDC hdc;
	//PAINTSTRUCT ps;

	switch (iMessage)
	{
	//case WM_TIMER:
	//	//this->update();
	//	break;
	//case WM_PAINT:
	//{
	//	hdc = BeginPaint(hWnd, &ps);
	//	this->render(hdc);
	//	EndPaint(hWnd, &ps);
	//}
	//break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
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
	
	TIMEMANAGER->render(backDC);

	m_pBackBuffer->render(hdc, 0, 0);
}



mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}
