#pragma once
class image;
class missileManager;
class spaceShip;

class enemy
{
private:
	image * m_pImg;
	RECT	m_rc;

	int		m_nCurrFrameX;
	int		m_nCurrFrameY;
	int		m_nCount;

	bool	m_bIsAlive;

	float	m_fX;
	float	m_fY;

	float	m_fangle;

	float	m_destinationX;
	float	m_destinationY;

	float	m_fdeDistance;

	bool	m_bIsSetting;
	bool	m_bisAllSetting;

	// 미사일 매니저
	missileManager*	m_pMissileMgr;
	int				m_nFireCount;
	int				m_nRandFireCount;

	// 타겟
	spaceShip*		m_pTarget;

public:
	HRESULT init();
	HRESULT init(const char* szFileName, POINT position);
	HRESULT init(const char * szFileName, POINT position, POINT destinationPos);
	void release();
	void update();
	void render(HDC hdc);

	void move();
	void fire();

	inline missileManager* getMissileMgr()
	{ return m_pMissileMgr; }

	inline bool getIsAlive() { return m_bIsAlive; }
	inline void setIsAlive(bool isAlive) { m_bIsAlive = isAlive; }

	inline bool getIsSetting() { return m_bIsSetting; }

	inline void setIsAllSetting(bool isAllSetting) { m_bisAllSetting = isAllSetting; }

	inline RECT getRect() { return m_rc; }
	inline void setTarget(spaceShip* pTarget) { m_pTarget = pTarget; }

	enemy();
	~enemy();
};

