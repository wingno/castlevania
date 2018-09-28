#pragma once
#include "room.h"

class image;
class player;
class enemyManager;

class hallwayRoom1
{

private:
	typedef struct tagMemDCInfo
	{
		HDC		hMemDC;	// 화면에 점, 선, 도형 등을 그릴 때 필요한 정보를 저장하는 객체
						// 그림을 그릴 때 필요한 메모리 공간 할당(도화지 개념)
		HBITMAP	hBitmap;	// 이미지파일 로드에 사용되는 객체
		HBITMAP hOldBitmap;
		int		nWidth;		// 이미지 너비
		int		nHeight;	// 이미지 높이


		tagMemDCInfo()
		{
			hMemDC = NULL;
			hBitmap = NULL;
			hOldBitmap = NULL;
			nWidth = 0;
			nHeight = 0;
		}//

		//void init();

		//~tagImageInfo() {}
	} MEM_INFO, *LPMEM_INFO;

	SYNTHESIZE(enemyManager*, m_pEnemyMgr, EnemyMgr);
	SYNTHESIZE(player*, m_pPlayer, Player);

	SYNTHESIZE(LPMEM_INFO, m_pMemDCInfo, MemDCInfo);

	image* m_imgBg;
	image* m_imgMap;

	SYNTHESIZE(POINT, m_posMap, Map)
	POINT m_posBG;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void colliderMake(int width, int height);

	hallwayRoom1();
	~hallwayRoom1();
};

