#pragma once
class progressBar
{
private:
	RECT	m_rc;
	//MEnu X,Y
	int  m_fX, m_fY;

	float	m_fWidth;
	float	m_fWidthMp;

	image*  m_imgeMenuProgress;
	image*	m_imgTop;
	image*  m_imgMp;

public:
	HRESULT init(float x, float y, float width, float height);
	void release();
	void update();
	void render(HDC hdc);

	void setGauge(float currGauge, float maxGauge
		,float currGaugemp, float maxGaugemp);



	progressBar();
	~progressBar();
};

