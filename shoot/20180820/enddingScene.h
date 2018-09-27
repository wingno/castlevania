#pragma once
#include "scene.h"
class enddingScene:public scene
{
	image* m_imgBG;
	float m_falphaNum;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);


	enddingScene();
	~enddingScene();
};

