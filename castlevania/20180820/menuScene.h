#pragma once
#include "scene.h"

class menuProgressBar;

class menuScene :public scene
{
private:
	enum SceneState
	{
		MENU,SOUL_SET, EQUIT, ITEM,
	};
	struct seleter
	{
		int Select;
		int SelectMover;
		bool isLeft;
		float speed;
	};


	image*	m_imgMenu;
	image*	m_imgEquit;
	image*	m_imgSoulSet;


	image*	m_imgSeleter;

	bool	m_bIsChangeScene;

	int m_nAlphaNum;

	seleter m_seleter;

	SceneState m_state;

	player* m_pPlayer;
	menuProgressBar* m_pHpBar;
	menuProgressBar* m_pMpBar;


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void menuRander(HDC hdc ,HFONT hFont ,HFONT oldFont);
	void menuUpdate();
	void sourSetRander(HDC hdc, HFONT hFont, HFONT oldFont);
	void sourSetupdate();
	void equitRander(HDC hdc, HFONT hFont, HFONT oldFont);
	void equitupdate();

	menuScene();
	~menuScene();
};

