#pragma once
class titleScene;
class battleScene;
class scoreScene;
class selectScene;
class spaceShip;

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

	spaceShip* m_pspaceShip;


	// save load test
	//std::vector<std::string> m_vecLoad;

	// scene test
	titleScene*		m_pTitleScene;
	battleScene*	m_pBattleScene;
	scoreScene*		m_pscoreScene;
	selectScene*	m_pselectScene;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	inline void setISpaceShip(spaceShip* SpaceShip) { m_pspaceShip = SpaceShip; }
	inline spaceShip* getISpaceShip() { return m_pspaceShip; }


	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	mainGame();
	~mainGame();
};

