#pragma once
class player;

class missile
{
protected:
	image * m_pImg;
	RECT	m_rc;

	float	m_fSpeed;
	float	m_fX, m_fY;
	float	m_fFiredX, m_fFiredY;
	float	m_fAngle;
	float	m_fRange;
	bool	m_isFire;

	int		m_nKind;


	float m_fMapX;
	float m_fMapY;

	player* m_pPlayer;



public:
	HRESULT init();
	HRESULT init(const char* szImageName, float speed,
		float x, float y, float angle, float range,int kind);
	void release();
	void update();
	void render(HDC hdc);

	void fire(float x, float y);
	virtual void move();

	inline RECT getRect() { return m_rc; }
	inline void setIsFire(bool isFire) { m_isFire = isFire; }
	inline bool getIsFire() { return m_isFire; }


	missile();
	virtual ~missile();
};

