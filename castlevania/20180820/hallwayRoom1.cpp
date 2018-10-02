#include "stdafx.h"
#include "hallwayRoom1.h"
#include "player.h"


HRESULT hallwayRoom1::init()
{
	m_imgBg = IMAGEMANAGER->addImage("image/MAP1.bmp", "image/MAP1.bmp", 5784, 2012, true, RGB(0, 88, 24));
	//m_imgMap= IMAGEMANAGER->addImage("image/MAP1PIX.bmp", "image/MAP1PIX.bmp", 5784, 2012, true, RGB(255, 0, 255));

	colliderMake();

	m_posMap = PointMake(0, 0);
	m_posBG = PointMake(0, 0);



	m_rectGate =rectGate;
	m_rectObj = rectObj;


	m_rectGate[0] = RectMake(0, 195, 30, 144);
	m_rectGate[1] = RectMake(1273 * 3 -30, 195, 30, 144);
	m_rectGate[2] = RectMake(353 * 3 , 0, 64*3, 30);


	m_rectObj[0] = RectMake(386 * 3, 88 * 3, 32 * 3, 7 * 3);
	m_rectObj[1] = RectMake(386 * 3, 47 * 3, 32 * 3, 7 * 3);




	return S_OK;
}

void hallwayRoom1::release()
{
	if (m_pMemDCInfo)
	{
		SelectObject(m_pMemDCInfo->hMemDC, m_pMemDCInfo->hOldBitmap);
		DeleteObject(m_pMemDCInfo->hBitmap);
		DeleteDC(m_pMemDCInfo->hMemDC);

		delete m_pMemDCInfo;
	}

}

void hallwayRoom1::update()
{

	if (m_posBG.x >= (2280))
	{
		m_posBG.x = 0;
	}
	else if(m_posBG.x<=0)
	{
		m_posBG.x = 2280;
	}

	if (m_posMap.x <0 )
	{
		m_posMap.x = 0;
		m_pPlayer->setXCameraOn(false);
	}
	else if (m_posMap.x > 3200)
	{
		m_posMap.x = 3200;
		m_pPlayer->setXCameraOn(false);
	}

	m_posMap.y = 0;
	m_posBG.y = 0;
	m_pPlayer->setYCameraOn(false);

	
	m_rectGate[0] = RectMake(0 - m_posMap.x, 195, 30, 144);
	m_rectGate[1] = RectMake(1273*3 - m_posMap.x, 195, 25, 144);
	m_rectGate[2] = RectMake(353 * 3 - m_posMap.x, 0, 64 * 3, 30);

	m_rectObj[0] = RectMake(384 * 3 - m_posMap.x, 80 * 3, 32 * 3, 7 * 3);
	m_rectObj[1] = RectMake(384 * 3 - m_posMap.x, 24 * 3, 32 * 3, 7 * 3);

	rectColider();
}

void hallwayRoom1::render(HDC hdc)
{



	m_imgBg->render(hdc, 0, 0, 542, 1839, 240, 160, 3);


	m_imgBg->render(hdc, 0, 140, 542 + m_posBG.x / 3, 1725, 240, 100,3);
	
	m_imgBg->render(hdc, 2280-m_posBG.x, 140, 542, 1725, 240, 100, 3);
	
	
	
	m_imgBg->render(hdc, 0,  0, 521+ m_posMap.x/3, 1551 + m_posMap.y / 3, 400, 160,3);

	for (int i = 0; i < 3; i++)
	{
		Rectangle(hdc, m_rectGate[i].left, m_rectGate[i].top, m_rectGate[i].right, m_rectGate[i].bottom);
	}
	for (int i = 0; i < 2; i++)
	{
		Rectangle(hdc, m_rectObj[i].left, m_rectObj[i].top, m_rectObj[i].right, m_rectObj[i].bottom);
	}
}

void hallwayRoom1::colliderMake()
{

	//HDC hdc = GetDC(g_hWnd);

	//m_pMemDCInfo = new MEM_INFO;
	//m_pMemDCInfo->hMemDC = CreateCompatibleDC(hdc);
	//m_pMemDCInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	//m_pMemDCInfo->hOldBitmap = (HBITMAP)SelectObject(m_pMemDCInfo->hMemDC, m_pMemDCInfo->hBitmap);

	//m_pMemDCInfo->nWidth = width;
	//m_pMemDCInfo->nHeight = height;

	HDC hdc = GetDC(g_hWnd);

	tagMemDCInfo tempInfo;

	// 기본 DC와 분리되는 메모리 DC, 비트맵 출력을 위한 공간
	tempInfo.hMemDC = CreateCompatibleDC(hdc);
	// 원본 DC와 호환되는 비트맵 생성
	tempInfo.hBitmap = (HBITMAP)LoadImage(
		g_hInstance,
		"image/MAP1PIX.bmp",
		IMAGE_BITMAP,
		5784, 2012,
		LR_LOADFROMFILE);
	// 새로 생성한 메모리DC 와 새로 생성한 비트맵을 연동시킨다
	tempInfo.hOldBitmap = (HBITMAP)SelectObject(tempInfo.hMemDC, tempInfo.hBitmap);

	tempInfo.nWidth = 5784;
	tempInfo.nHeight = 2012;


	m_pMemDCInfo = new tagMemDCInfo;
	// 기본 DC와 분리되는 메모리 DC, 비트맵 출력을 위한 공간
	m_pMemDCInfo->hMemDC = CreateCompatibleDC(hdc);
	// 원본 DC와 호환되는 비트맵 생성
	m_pMemDCInfo->hBitmap = CreateCompatibleBitmap(hdc, 1276 * 3, 160 * 3);
	// 새로 생성한 메모리DC 와 새로 생성한 비트맵을 연동시킨다
	m_pMemDCInfo->hOldBitmap = (HBITMAP)SelectObject(m_pMemDCInfo->hMemDC, m_pMemDCInfo->hBitmap);

	m_pMemDCInfo->nWidth = 1276 * 3;
	m_pMemDCInfo->nHeight = 160 * 3;


	GdiTransparentBlt(
		// 목적지
		m_pMemDCInfo->hMemDC,					// 복사될 목적지 DC
		0, 0,			// 복사될 좌표 시작점
		1276*3, 160*3,	// 복사될 크기

						// 대상
		tempInfo.hMemDC,	// 복사할 대상 DC
		521, 1551,			// 복사될 영역 시작좌표
		1276, 160,	// 복사될 영역지정 좌표

		RGB(255, 0, 255));			// 복사에서 제외할 색상

	SelectObject(tempInfo.hMemDC, tempInfo.hOldBitmap);
	DeleteObject(tempInfo.hBitmap);
	DeleteDC(tempInfo.hMemDC);
}

void hallwayRoom1::rectColider()
{



	for (int i = 0; i < 3; i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &(m_pPlayer->getRc()), &(m_rectGate[i])))
		{
			switch (i)
			{
			case 0:
				
				break;
			case 1:
				m_pPlayer->setFY(78 * 3);
				m_pPlayer->setFx(59 * 3);

				ROOMMANAGER->changeRoom("FountainRoom");
				break;
			case 2:


				break;


			default:
				break;
			}
		}

	}

	for (int i = 0; i < 2; i++)
	{
		if (m_rectObj[i].top + 7 > m_pPlayer->getRc().bottom && m_rectObj[i].top - 7 < m_pPlayer->getRc().bottom)
		{
			
			m_pPlayer->setFY(m_rectObj[i].top - 40);

		}

	}


}





hallwayRoom1::hallwayRoom1()
{
}


hallwayRoom1::~hallwayRoom1()
{
}
