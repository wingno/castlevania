#include "stdafx.h"
#include "hallwayRoom1.h"
#include "player.h"


HRESULT hallwayRoom1::init()
{
	m_imgBg = IMAGEMANAGER->addImage("image/MAP1.bmp", "image/MAP1.bmp", 5784, 2012, true, RGB(0, 88, 24));
	m_imgMap= IMAGEMANAGER->addImage("image/MAP1PIX.bmp", "image/MAP1PIX.bmp", 5784, 2012, true, RGB(0, 88, 24));

	//colliderMake(3072 * 3, 600);

	m_posMap = PointMake(0, 0);
	m_posBG = PointMake(0, 0);




	
	



	return S_OK;
}

void hallwayRoom1::release()
{
	delete(m_pMemDCInfo);
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



}

void hallwayRoom1::render(HDC hdc)
{

	m_imgBg->render(hdc, 0, 0, 542, 1839, 240, 160, 3);


	m_imgBg->render(hdc, 0, 140, 542 + m_posBG.x / 3, 1725, 240, 100,3);
	
	m_imgBg->render(hdc, 2280-m_posBG.x, 140, 542, 1725, 240, 100, 3);
	
	
	
	m_imgBg->render(hdc, 0,  0, 521+ m_posMap.x/3, 1551, 400, 160,3);
}

void hallwayRoom1::colliderMake(int width, int height)
{

	//HDC hdc = GetDC(g_hWnd);

	//m_pMemDCInfo = new MEM_INFO;
	//m_pMemDCInfo->hMemDC = CreateCompatibleDC(hdc);
	//m_pMemDCInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	//m_pMemDCInfo->hOldBitmap = (HBITMAP)SelectObject(m_pMemDCInfo->hMemDC, m_pMemDCInfo->hBitmap);

	//m_pMemDCInfo->nWidth = width;
	//m_pMemDCInfo->nHeight = height;



	//GdiTransparentBlt(
	//	// 목적지
	//	m_pMemDCInfo->hMemDC,					// 복사될 목적지 DC
	//	0, 0,			// 복사될 좌표 시작점
	//	3072 * 3, 600,	// 복사될 크기

	//					// 대상
	//	m_imgMap->getMemDC(),	// 복사할 대상 DC
	//	0, 0,			// 복사될 영역 시작좌표
	//	3072, 206,	// 복사될 영역지정 좌표

	//	RGB(0, 88, 24));			// 복사에서 제외할 색상
}




hallwayRoom1::hallwayRoom1()
{
}


hallwayRoom1::~hallwayRoom1()
{
}
