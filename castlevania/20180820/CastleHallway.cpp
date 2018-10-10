#include "stdafx.h"
#include "CastleHallway.h"
#include "player.h"
#include "RoomObject.h"

HRESULT CastleHallway::init()
{
	m_imgBg = IMAGEMANAGER->addImage("image/MAP1.bmp", "image/MAP1.bmp", 5784, 2012, true, RGB(0, 88, 24));
	//m_imgMap= IMAGEMANAGER->addImage("image/MAP1PIX.bmp", "image/MAP1PIX.bmp", 5784, 2012, true, RGB(255, 0, 255));

	colliderMake();


	m_posMap = PointMake(0, 0);
	m_posBG = PointMake(0, 0);



	m_rectGate = rectGate;
	m_rectObj = rectObj;


	m_OBJ = new RoomObject[14];

	for (int i = 0; i < 14; i++)
	{
		//촛불
		m_OBJ[0].init(361, 4058, 0);
		m_OBJ[1].init(650, 4058, 0);
		m_OBJ[2].init(937, 4058, 0);



		//횟불
		m_OBJ[3].init(772, 3450, 1);
		m_OBJ[4].init(339, 3162, 1);
		m_OBJ[5].init(630, 2301, 1);
		m_OBJ[6].init(868, 2301, 1);
		m_OBJ[7].init(1397, 2010, 1);
		
		m_OBJ[8].init(868, 1819, 1);
		m_OBJ[9].init(628, 1725, 1);

		m_OBJ[10].init(628, 1244, 1);
		m_OBJ[11].init(868, 1147, 1);
		m_OBJ[12].init(628, 572, 1);
		m_OBJ[13].init(868, 572, 1);
		

	}
	return S_OK;
}
 void CastleHallway::release()
{
	if (m_pMemDCInfo)
	{
		SelectObject(m_pMemDCInfo->hMemDC, m_pMemDCInfo->hOldBitmap);
		DeleteObject(m_pMemDCInfo->hBitmap);
		DeleteDC(m_pMemDCInfo->hMemDC);

		delete m_pMemDCInfo;
	}
}

void CastleHallway::update()
{

	//촛불
	for (int i = 0; i < 14; i++)
	{
		m_OBJ[i].update();
	}
	if (m_posMap.x < 0)
	{
		m_posMap.x = 0;
		m_pPlayer->setXCameraOn(false);


	}
	else if (m_posMap.x > 512 * 3 - WINSIZEX)
	{
		m_posMap.x = 512 * 3 - WINSIZEX;

	
			m_pPlayer->setXCameraOn(false);
		
	}

	if (m_posMap.y < 0 && m_posMap.x < !0)
	{

		
		m_pPlayer->setXCameraOn(false);
		
	}
	else if (m_posMap.y > 1440 * 3 - WINSIZEY)
	{

		m_posMap.y = 1440 * 3 - WINSIZEY;
		m_pPlayer->setYCameraOn(false);


	}


	m_rectGate[0] = RectMake(-20 - m_posMap.x, 4032 - m_posMap.y, 30, 144);
	m_rectGate[1] = RectMake(1530 - m_posMap.x, 4032 - m_posMap.y, 30, 144);

	//발판 오브잭트
	//오른쪽

	m_rectObj[0] = RectMake(1250 - m_posMap.x, 4078 - m_posMap.y, 100, 30);
	m_rectObj[1] = RectMake(1342 - m_posMap.x, 2203 - m_posMap.y, 100, 30);
	m_rectObj[2] = RectMake(1342 - m_posMap.x, 2400 - m_posMap.y, 100, 30);
	m_rectObj[3] = RectMake(1249 - m_posMap.x, 2584 - m_posMap.y, 100, 30);
	m_rectObj[4] = RectMake(1342 - m_posMap.x, 2732 - m_posMap.y, 100, 30);
	m_rectObj[5] = RectMake(1249 - m_posMap.x, 2875 - m_posMap.y, 100, 30);
	m_rectObj[6] = RectMake(1342 - m_posMap.x, 3211 - m_posMap.y, 100, 30);
	m_rectObj[10] = RectMake(1342 - m_posMap.x, 1051 - m_posMap.y, 100, 30);

	//왼쪽
	m_rectObj[9] = RectMake(96 - m_posMap.x, 1778 - m_posMap.y, 97, 30);
	m_rectObj[8] = RectMake(96 - m_posMap.x, 2593 - m_posMap.y, 97, 30);
	m_rectObj[7] = RectMake(96 - m_posMap.x, 3505 - m_posMap.y, 242, 25);


	rectColider();
}

void CastleHallway::render(HDC hdc)
{
	m_imgBg->render(hdc, 0, 0, 125, 1796, 300, 160, 3);


	m_imgBg->render(hdc, 0, 0, 3081 + m_posMap.x / 3, 271 + m_posMap.y / 3, 300, 160, 3);

	//게이트 오브젝트
	for (int i = 0; i < 3; i++)
	{
		Rectangle(hdc, m_rectGate[i].left, m_rectGate[i].top, m_rectGate[i].right, m_rectGate[i].bottom);

	}
	//발판 오브젝트
	for (int i = 0; i < 12; i++)
	{
		Rectangle(hdc, m_rectObj[i].left, m_rectObj[i].top, m_rectObj[i].right, m_rectObj[i].bottom);
	}


	for (int i = 0; i < 14; i++)
	{
		m_OBJ[i].render(hdc);
	}
}

void CastleHallway::rectColider()
{
	for (int i = 0; i < 2; i++)
	{
		POINT point;
		RECT rc;
		if (IntersectRect(&rc, &(m_pPlayer->getRc()), &(m_rectGate[i])))
		{
			switch (i)
			{
			case 0:

				m_pPlayer->setFY(293);
				m_pPlayer->setFx(WINSIZEX - (20 * 3));

				ROOMMANAGER->changeRoom("hallwayRoom2");


				point.x = 780 * 3 - WINSIZEX;
				point.y = 0;

				ROOMMANAGER->getCurrRoom()->setPosMap(point);
			
				break;
			case 1:

				m_pPlayer->setFY(300);
				m_pPlayer->setFx(30 * 3);

				ROOMMANAGER->changeRoom("hallwayRoom3");
				break;
			case 2:


				break;


			default:
				break;
			}
		}
	}

	for (int i = 0; i < 12; i++)
	{
		if (m_rectObj[i].top + 13 > m_pPlayer->getRc().bottom && m_rectObj[i].top - 7 < m_pPlayer->getRc().bottom
			&& (m_pPlayer->getRc().right > m_rectObj[i].left && m_pPlayer->getRc().left < m_rectObj[i].right))
		{

			m_pPlayer->setFY(m_rectObj[i].top - 50);


			//맵에걸릴경우 내려가는거 임시방편 나중에 수정해야함 !!!
			if (m_rectObj[i].top - 50)
			{
				if (KEYMANAGER->isOnceKeyDown('C'))
				{
					m_pPlayer->setFY(m_rectObj[i].top - 10);
				}
			}


		}
	}

}

void CastleHallway::checkCollision()
{
	RECT rc;


	for (int i = 0; i < 14; i++)
	{


		if (m_OBJ[i].getAlive() && IntersectRect(&rc, &m_pPlayer->getIRC(), &m_OBJ[i].getrc()))
		{
			m_OBJ[i].setAlive(false);

			m_OBJ[i].setDestruction(true);
		}

	}
}

void CastleHallway::colliderMake()
{
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
	m_pMemDCInfo->hBitmap = CreateCompatibleBitmap(hdc, 512 * 3, 1440 * 3);
	// 새로 생성한 메모리DC 와 새로 생성한 비트맵을 연동시킨다
	m_pMemDCInfo->hOldBitmap = (HBITMAP)SelectObject(m_pMemDCInfo->hMemDC, m_pMemDCInfo->hBitmap);

	m_pMemDCInfo->nWidth = 512 * 3;
	m_pMemDCInfo->nHeight = 1440 * 3;


	GdiTransparentBlt(
		// 목적지
		m_pMemDCInfo->hMemDC,					// 복사될 목적지 DC
		0, 0,			// 복사될 좌표 시작점
		512 * 3, 1440 * 3,	// 복사될 크기

						// 대상
		tempInfo.hMemDC,	// 복사할 대상 DC
		3081, 271,			// 복사될 영역 시작좌표
		512, 1440,	// 복사될 영역지정 좌표

		RGB(255, 0, 255));			// 복사에서 제외할 색상

	SelectObject(tempInfo.hMemDC, tempInfo.hOldBitmap);
	DeleteObject(tempInfo.hBitmap);
	DeleteDC(tempInfo.hMemDC);
}



CastleHallway::CastleHallway()
{
}


CastleHallway::~CastleHallway()
{
}
