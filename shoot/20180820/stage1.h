#pragma once

class enemyManager;
class player;
class sanger;

class stage1
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
		}

		//void init();

		//~tagImageInfo() {}
	} MEM_INFO, *LPMEM_INFO;

	image* m_imgBg;

	SYNTHESIZE(enemyManager*, m_pEnemyMgr, EnemyMgr);
	SYNTHESIZE(player*, m_pPlayer, Player);
	SYNTHESIZE(sanger*, m_pSanger, Sanger);

	SYNTHESIZE(LPMEM_INFO, m_pMemDCInfo, MemDCInfo);

	POINT m_posBG;
	SYNTHESIZE(POINT, m_posMap, Map)

	RECT m_colliderRect[3];


	
public:

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	RECT* getColliderRect() { return m_colliderRect; }

	void colliderMake(int width,int height);

	void mapPartRander(HDC hdc);

	void stage1EnemyMaking();

	stage1();
	~stage1();
};

