#pragma once
class progressBar
{
private:
	RECT	m_rc;
	//HP X,Y
	float	m_fHpX, m_fHpY;
	//MP X,Y
	float   m_fMpX, m_fMpY;
	//MEnu X,Y
	int  m_nMenuX, m_nMenuY;
	float	m_fWidth;


	image*  m_imgeMenuProgress;
	image*	m_imgHP;
	image*	m_imgMP;

public:
	HRESULT init(float x, float y);
	void release();
	void update();
	void render(HDC hdc);

	void setGauge(float currGauge, float maxGauge);

	inline void setX(float x) { m_fHpX = x; }
	inline void setY(float y) { m_fHpY = y; }

	progressBar();
	~progressBar();
};

