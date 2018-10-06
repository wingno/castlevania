#pragma once
#include "scene.h"

class menuProgressBar;

class menuScene :public scene
{
private:
	enum SceneState
	{
		MENU, EQUIT, ITEM,
	};
	struct seleter
	{
		int Select;
		int SelectMover;
		bool isLeft;
		float speed;
	};


	image*	m_imgMenu;

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

	menuScene();
	~menuScene();
};

