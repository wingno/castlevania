#pragma once
#include "scene.h"

class titleScene : public scene
{
private:
	image * m_pBG;
	image * m_imgGuide;

	int		m_nCount;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	titleScene();
	~titleScene();
};

