#include "stdafx.h"
#include "FountainRoom.h"
#include "player.h"

HRESULT FountainRoom::init()
{

	m_imgBg = IMAGEMANAGER->addImage("image/MAP1.bmp", "image/MAP1.bmp", 5784, 2012, true, RGB(0, 88, 24));
	//m_imgMap= IMAGEMANAGER->addImage("image/MAP1PIX.bmp", "image/MAP1PIX.bmp", 5784, 2012, true, RGB(255, 0, 255));

	colliderMake();

	m_posMap = PointMake(0, 0);
	m_posBG = PointMake(0, 0);



	m_rectGate = rectGate;
	m_rectObj = rectObj;

	
	




	return S_OK;
}

void FountainRoom::release()
{
	if (m_pMemDCInfo)
	{
		SelectObject(m_pMemDCInfo->hMemDC, m_pMemDCInfo->hOldBitmap);
		DeleteObject(m_pMemDCInfo->hBitmap);
		DeleteDC(m_pMemDCInfo->hMemDC);

		delete m_pMemDCInfo;
	}
}

void FountainRoom::update()
{

	if (m_posMap.x < 0)
	{
		m_posMap.x = 0;
		m_pPlayer->setXCameraOn(false);
	}
	else if (m_posMap.x > 512*3 -WINSIZEX)
	{
		m_posMap.x = 512 * 3 - WINSIZEX;
		m_pPlayer->setXCameraOn(false);


	}

	if (m_posMap.y < -10)
	{
		m_posMap.y = 0;
		m_pPlayer->setYCameraOn(false);
	}
	else if (m_posMap.y > 416 * 3 - WINSIZEY)
	{
		m_posMap.y = 416 * 3 - WINSIZEY;
		m_pPlayer->setYCameraOn(false);
	}

	
	m_rectGate[0] = RectMake(-30 - m_posMap.x, 193 - m_posMap.y, 30, 144);
	//- 30 �Ⱥ��̴� ���¿��� �浹�� ���̵�
	m_rectGate[1] = RectMake(1520 - m_posMap.x, 193 - m_posMap.y, 30, 144);
	m_rectGate[2] = RectMake(1520 - m_posMap.x, 960 - m_posMap.y, 30, 144);

	//2������Ʈ �� ��Ʈ
	rectObj[0]= RectMake(1345 - m_posMap.x, 864 - m_posMap.y, 100, 30);
	//�м��� ��Ʈ
	rectObj[1] = RectMake(590 - m_posMap.x, 1000 - m_posMap.y, 350, 50);

	rectColider();
	
}

void FountainRoom::render(HDC hdc)
{


	m_imgBg->render(hdc, 0, 0, 1801 + m_posMap.x / 3, 1551 + m_posMap.y / 3, 240, 160, 3);

	
	for (int i = 0; i < 3; i++)
	{
		Rectangle(hdc, m_rectGate[i].left, m_rectGate[i].top, m_rectGate[i].right, m_rectGate[i].bottom);
	}

	for (int i = 0; i < 2; i++)
	{
		Rectangle(hdc, m_rectObj[i].left, m_rectObj[i].top, m_rectObj[i].right, m_rectObj[i].bottom);
	}
}

void FountainRoom::colliderMake()
{


	HDC hdc = GetDC(g_hWnd);

	tagMemDCInfo tempInfo;

	// �⺻ DC�� �и��Ǵ� �޸� DC, ��Ʈ�� ����� ���� ����
	tempInfo.hMemDC = CreateCompatibleDC(hdc);
	// ���� DC�� ȣȯ�Ǵ� ��Ʈ�� ����
	tempInfo.hBitmap = (HBITMAP)LoadImage(
		g_hInstance,
		"image/MAP1PIX.bmp",
		IMAGE_BITMAP,
		5784, 2012,
		LR_LOADFROMFILE);
	// ���� ������ �޸�DC �� ���� ������ ��Ʈ���� ������Ų��
	tempInfo.hOldBitmap = (HBITMAP)SelectObject(tempInfo.hMemDC, tempInfo.hBitmap);

	tempInfo.nWidth = 5784;
	tempInfo.nHeight = 2012;


	m_pMemDCInfo = new tagMemDCInfo;
	// �⺻ DC�� �и��Ǵ� �޸� DC, ��Ʈ�� ����� ���� ����
	m_pMemDCInfo->hMemDC = CreateCompatibleDC(hdc);
	// ���� DC�� ȣȯ�Ǵ� ��Ʈ�� ����
	m_pMemDCInfo->hBitmap = CreateCompatibleBitmap(hdc, 512 * 3, 416 * 3);
	// ���� ������ �޸�DC �� ���� ������ ��Ʈ���� ������Ų��
	m_pMemDCInfo->hOldBitmap = (HBITMAP)SelectObject(m_pMemDCInfo->hMemDC, m_pMemDCInfo->hBitmap);

	m_pMemDCInfo->nWidth = 512 * 3;
	m_pMemDCInfo->nHeight = 416 * 3;


	GdiTransparentBlt(
		// ������
		m_pMemDCInfo->hMemDC,					// ����� ������ DC
		0, 0,			// ����� ��ǥ ������
		512 * 3, 416 * 3,	// ����� ũ��

						// ���
		tempInfo.hMemDC,	// ������ ��� DC
		1801, 1551,			// ����� ���� ������ǥ
		512, 416,	// ����� �������� ��ǥ

		RGB(255, 0, 255));			// ���翡�� ������ ����

	SelectObject(tempInfo.hMemDC, tempInfo.hOldBitmap);
	DeleteObject(tempInfo.hBitmap);
	DeleteDC(tempInfo.hMemDC);
}

void FountainRoom::rectColider()
{
	for (int i = 0; i < 3; i++)
	{
		RECT rc;
		POINT point;
		if (IntersectRect(&rc, &(m_pPlayer->getRc()), &(m_rectGate[i])))
		{
			switch (i)
			{
			case 0:
				m_pPlayer->setFY(293);
				m_pPlayer->setFx(WINSIZEX - (30 * 3));

				ROOMMANAGER->changeRoom("hallwayRoom1");

				
				point.x = 1276 * 3 - WINSIZEX;
				point.y = 0;

				ROOMMANAGER->getCurrRoom()->setPosMap(point);

				break;
			case 1:
				m_pPlayer->setFY(300);
				m_pPlayer->setFx(30 * 3);

				ROOMMANAGER->changeRoom("hallwayRoom2");

				
	
				break;

			case 2:
				m_pPlayer->setFY(330);
				m_pPlayer->setFx(40 * 3);


				ROOMMANAGER->changeRoom("saveroom");


		

				
				break;

				


			default:
				break;
			}
		}
	}


	for (int i = 0; i < 2; i++)
	{
		if (m_rectObj[i].top + 13 > m_pPlayer->getRc().bottom && m_rectObj[i].top - 7 < m_pPlayer->getRc().bottom
			&& (m_pPlayer->getRc().right > m_rectObj[i].left && m_pPlayer->getRc().left < m_rectObj[i].right))
		{

			m_pPlayer->setFY(m_rectObj[i].top - 50);
		}
	}



}

FountainRoom::FountainRoom()
{
}


FountainRoom::~FountainRoom()
{
}
