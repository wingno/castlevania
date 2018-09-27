#pragma once
class titleScene;
class battleScene;
class loadingScene_1;
class enddingScene;
class gameoverScene;

class mainGame
{
private:
	// DC
	HDC hdc;

	// ¹é¹öÆÛ
	image * m_pBackBuffer;
	void setBackBuffer();

	char m_szText[128];

	SYNTHESIZE( bool, m_bIsSlice,IsSlice);
	SYNTHESIZE(int, m_nScore, Score);
	SYNTHESIZE(int, m_nSaveX, SaveX);

	// scene test
	titleScene*		m_pTitleScene;
	battleScene*	m_pBattleScene;
	enddingScene*	m_penddingScene;
	gameoverScene*	m_pGameoverScene;

	loadingScene_1*	m_pLoadingScene;



public:
	HRESULT init();
	void release();
	void update();
	void render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	mainGame();
	~mainGame();
};

