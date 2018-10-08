#pragma once
#include "scene.h"

class titleScene : public scene
{
private:
	image * m_intro;
	int FX, FY, fIdx;
	int Fcount;

	image* m_select;
	image* m_select2;
	int menuX, menuY, menuFY;
	int menuX2, menuY2;

	bool title1, title2;
	RECT m_rc;


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	titleScene();
	~titleScene();
};

