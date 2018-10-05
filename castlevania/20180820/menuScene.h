#pragma once
#include "scene.h"
class menuScene :public scene
{
private:
	enum SceneState
	{
		MENU, EQUIT, item
	};

	image*	m_imgMenu;

	player* m_pPlayer;



public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void menuRander(HDC hdc ,HFONT hFont ,HFONT oldFont);

	menuScene();
	~menuScene();
};

