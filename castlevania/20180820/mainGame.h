#pragma once
class titleScene;
class battleScene;
class scoreScene;
class selectScene;
class menuScene;
class spaceShip;
class player;

class mainGame
{
private:
	// DC
	HDC hdc;

	// ¹é¹öÆÛ
	image * m_pBackBuffer;
	void setBackBuffer();

	char m_szText[128];

	int m_nscore;

	SYNTHESIZE( player*, m_pPlayer,Player);


	// save load test
	//std::vector<std::string> m_vecLoad;

	// scene test
	titleScene*		m_pTitleScene;
	battleScene*	m_pBattleScene;
	scoreScene*		m_pscoreScene;
	selectScene*	m_pselectScene;
	menuScene*		m_pmenuScene;

public:
	HRESULT init();
	void release();
	void update();
	void render();




	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	mainGame();
	~mainGame();
};

