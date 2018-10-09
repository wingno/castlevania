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

	image*	m_imgRArrow;
	image*	m_imgLArrow;

	image*	m_imgEmptySoul;

	image*	m_imgSeleter;

	bool	m_bIsChangeScene;

	int m_nAlphaNum;

	int m_nSetStep;

	int m_nTypeSelet;
	
	int m_nFinalSelectNum;

	int m_nShowStarNum;

	int m_nShowEndChacker;


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

	void menuRander(HDC hdc );
	void menuUpdate();
	void sourSetRander(HDC hdc);
	void sourSetupdate();
	void equitRander(HDC hdc);
	void equitupdate();


	void fontPrint(HDC hdc);

	menuScene();
	~menuScene();
};

