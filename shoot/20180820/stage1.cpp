#include "stdafx.h"
#include "stage1.h"
#include "enemyManager.h"
#include "sanger.h"


HRESULT stage1::init()
{
	m_imgBg= IMAGEMANAGER->addImage("image/stage1.bmp", "image/stage1.bmp", 3072, 428, true, RGB(63, 72, 204));


	colliderMake(3072 * 3, 600);

	m_posMap = PointMake(0, 0);
	m_posBG = PointMake(0, 0);

	

	m_colliderRect[0] = RectMake(715*3, 55*3+10,30*3, 105*3-40);
	m_colliderRect[1] = RectMake(860 * 3, 55 * 3+10, 30 * 3, 155 * 3-40);
	m_colliderRect[2] = RectMake(1290 * 3, 55 * 3+10, 30 * 3, 135 * 3-40);

	m_posMap.x = g_mainGame.getSaveX();

	return S_OK;
}

void stage1::release()
{
	SAFE_DELETE(m_pEnemyMgr);
}

void stage1::update()
{
	m_pEnemyMgr->update();
	if (m_posMap.x <= (3070 * 3) - WINSIZEX )
	{
		m_posMap.x+=3;
		m_posBG.x+=3;

	}

	if (m_posMap.x > 1505 && m_posMap.x<1508)
	{
		g_mainGame.setSaveX(m_posMap.x);
	}
	if (m_posMap.x > 2800 && m_posMap.x<2804)
	{
		g_mainGame.setSaveX(m_posMap.x);

	}
	if (m_posMap.x > 3605 && m_posMap.x < 3608)
	{
		g_mainGame.setSaveX(m_posMap.x);
	}
	if (m_posMap.x > 7310 && m_posMap.x < 7315)
	{
		g_mainGame.setSaveX(m_posMap.x);
	}

	stage1EnemyMaking();

}

void stage1::render(HDC hdc)
{
	if (m_posBG.x > 510 * 3)
	{
		m_posBG.x = 0;
	}
	m_imgBg->render(hdc,  - m_posBG.x, - m_posBG.y,510*3,600 , 0, 214, 510, 206);
	m_imgBg->render(hdc, (510*3) - m_posBG.x,- m_posBG.y, 510 * 3, 600, 0, 214, 510, 206);


	mapPartRander(hdc);
	

	/*for (int i = 0; i < 3; i++)
	{
		Rectangle(hdc, m_colliderRect[i].left - m_posMap.x, m_colliderRect[i].top, m_colliderRect[i].right - m_posMap.x, m_colliderRect[i].bottom);
	}*/
	
	//420
}



void stage1::colliderMake(int width ,int height)
{

	HDC hdc = GetDC(g_hWnd);

	m_pMemDCInfo = new MEM_INFO;
	m_pMemDCInfo->hMemDC = CreateCompatibleDC(hdc);
	m_pMemDCInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	m_pMemDCInfo->hOldBitmap = (HBITMAP)SelectObject(m_pMemDCInfo->hMemDC, m_pMemDCInfo->hBitmap);

	m_pMemDCInfo->nWidth = width;
	m_pMemDCInfo->nHeight = height;



	GdiTransparentBlt(
		// 목적지
		m_pMemDCInfo->hMemDC,					// 복사될 목적지 DC
		0, 0,			// 복사될 좌표 시작점
		3072 * 3, 600,	// 복사될 크기

						// 대상
		m_imgBg->getMemDC(),	// 복사할 대상 DC
		0, 0,			// 복사될 영역 시작좌표
		3072, 206,	// 복사될 영역지정 좌표

		RGB(255, 0, 255));			// 복사에서 제외할 색상
}

void stage1::mapPartRander(HDC hdc)
{
	if (m_posMap.x <1500)
	{
		m_imgBg->render(hdc, -m_posMap.x, -m_posMap.y, 1024 * 3, 600, 0, 0, 1024, 206);
	}
	else if (m_posMap.x >= 1500 && m_posMap.x <3500)
	{
		m_imgBg->render(hdc, 512 * 3 - m_posMap.x, 0 - m_posMap.y, 1024 * 3, 600, 512, 0, 1024, 206);
	}
	else if (m_posMap.x >= 3500 && m_posMap.x <5000)
	{
		m_imgBg->render(hdc, 1024 * 3 - m_posMap.x, 0 - m_posMap.y, 1024 * 3, 600, 1024, 0, 1024, 206);
	}
	else if (m_posMap.x >= 5000 && m_posMap.x <6500)
	{
		m_imgBg->render(hdc, 1536 * 3 - m_posMap.x, 0 - m_posMap.y, 1024 * 3, 600, 1536, 0, 1024, 206);
	}
	else if (m_posMap.x >= 6500 && m_posMap.x < 9000)
	{
		m_imgBg->render(hdc, 2048 * 3 - m_posMap.x, 0 - m_posMap.y, 1024 * 3, 600, 2048, 0, 1024, 206);
	}

}

void stage1::stage1EnemyMaking()
{
	if (m_posMap.x > 250 && m_posMap.x<254)
	{
		m_pEnemyMgr->setEnemy(m_pPlayer, 1);
		m_pEnemyMgr->setEnemy(m_pPlayer, 4);
	}

	if (m_posMap.x > 420 && m_posMap.x<424)
	{
		m_pEnemyMgr->setEnemy(m_pPlayer, 2);

		m_pEnemyMgr->setEnemy(m_pPlayer, 4);
	}

	if (m_posMap.x > 800 && m_posMap.x<803)
	{
		m_pEnemyMgr->setEnemy(m_pPlayer, 3);
	}

	if (m_posMap.x > 1100 && m_posMap.x<1103)
	{
		m_pEnemyMgr->setEnemy(m_pPlayer, 5);
	}


	if (m_posMap.x > 1300 && m_posMap.x<1303)
	{
		m_pEnemyMgr->setEnemy(m_pPlayer, 3);
		     
	}

	if (m_posMap.x > 1500 && m_posMap.x<1504)
 	{
 		m_pEnemyMgr->setEnemy(m_pPlayer, 3);

		//m_pEnemyMgr->setEnemy(m_pPlayer, 7);
	}


	if (m_posMap.x > 2300 && m_posMap.x<2304)
	{
		m_pEnemyMgr->setEnemy(m_pPlayer, 2);
	}

	if (m_posMap.x > 2600 && m_posMap.x<2604)
	{
  		m_pEnemyMgr->setEnemy(m_pPlayer, 2);
		      
		//m_pEnemyMgr->setEnemy(m_pPlayer, 7);
	}



	if (m_posMap.x > 2900 && m_posMap.x<2904)
   	{  
  	 	m_pEnemyMgr->setEnemy(m_pPlayer, 3);

		m_pEnemyMgr->setEnemy(m_pPlayer, 7);
          
		m_pEnemyMgr->setEnemy(m_pPlayer,5);
   		  
	}    

	if (m_posMap.x > 3300 && m_posMap.x<3304)
	{
		m_pEnemyMgr->setEnemy(m_pPlayer, 4);
	}


	if (m_posMap.x > 3600 && m_posMap.x<3604)
	{


		m_pEnemyMgr->setEnemy(m_pPlayer, 4);
	}



	if (m_posMap.x > 3800 && m_posMap.x<3804)
	{


		m_pEnemyMgr->setEnemy(m_pPlayer, 6);
	}

	if (m_posMap.x > 4300 && m_posMap.x<4304)
	{

		m_pEnemyMgr->setEnemy(m_pPlayer, 5);
		m_pEnemyMgr->setEnemy(m_pPlayer, 8);
	}

	if (m_posMap.x > 4950 && m_posMap.x<4954)
	{
		m_pEnemyMgr->setEnemy(m_pPlayer, 1);
		m_pEnemyMgr->setEnemy(m_pPlayer, 4);
	}

	if (m_posMap.x > 5100 && m_posMap.x<5104)
	{
		m_pEnemyMgr->setEnemy(m_pPlayer, 2);
		m_pEnemyMgr->setEnemy(m_pPlayer, 5);
	}

	if (m_posMap.x > 5300 && m_posMap.x<5304)
	{
		m_pEnemyMgr->setEnemy(m_pPlayer, 2);
		m_pEnemyMgr->setEnemy(m_pPlayer, 5);
	}

	if (m_posMap.x > 5600 && m_posMap.x<5604)
	{
		m_pEnemyMgr->setEnemy(m_pPlayer, 3);
		m_pEnemyMgr->setEnemy(m_pPlayer, 5);
		m_pEnemyMgr->setEnemy(m_pPlayer, 4);
	}

	if (m_posMap.x > 5900 && m_posMap.x<5904)
	{
		m_pEnemyMgr->setEnemy(m_pPlayer, 2);
		m_pEnemyMgr->setEnemy(m_pPlayer, 6);
		m_pEnemyMgr->setEnemy(m_pPlayer, 3);
	}

	if (m_posMap.x > 6100 && m_posMap.x<6104)
	{
		m_pEnemyMgr->setEnemy(m_pPlayer, 8);
		m_pEnemyMgr->setEnemy(m_pPlayer, 4);
	}

	if (m_posMap.x > 6300 && m_posMap.x<6304)
	{
		m_pEnemyMgr->setEnemy(m_pPlayer, 5);
		m_pEnemyMgr->setEnemy(m_pPlayer, 1);
	}

	if (m_posMap.x > 6600 && m_posMap.x<6604)
	{
		
		m_pEnemyMgr->setEnemy(m_pPlayer, 3);
	}

	if (m_posMap.x > 6800 && m_posMap.x<6804)
	{

		m_pEnemyMgr->setEnemy(m_pPlayer, 4);
	}

	if (m_posMap.x > 7000 && m_posMap.x<7004)
	{
		m_pEnemyMgr->setEnemy(m_pPlayer, 7);

		m_pEnemyMgr->setEnemy(m_pPlayer, 5);
	}
	if (m_posMap.x > 7300 && m_posMap.x<7304)
	{
		for (int i = 0; i < 9; ++i)
		{
			m_pEnemyMgr->setEnemy(m_pPlayer, i);
		}
	}


	if (m_posMap.x >(3068 * 3) - WINSIZEX &&m_posMap.x <(3069 * 3) - WINSIZEX)
	{

		m_pSanger->setIsAlive(true);

	}
}

stage1::stage1()
{
}


stage1::~stage1()
{
}
