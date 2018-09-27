#pragma once
class image;
class missileManager;
class player;


enum ENEMYKIND
{
	ZAKU=1,
	JUZAKU,
	INVADERAIR,
	INVADERGROUND

};
class enemy
{
private:
	image * m_pImg;
	RECT	m_rc;

	int		m_nCurrFrameX;
	int		m_nCurrFrameY;
	int		m_nCount;

	float	m_fX;
	float	m_fY;

	float	m_fangle;
	float	m_fShootAngle;

	float	m_destinationX;
	float	m_destinationY;

	float	m_fdeDistance;


	//bool	m_bIsAlive;
	SYNTHESIZE(bool, m_bIsAlive, IsAlive);

	bool	m_bIsSetting;
	bool	m_bisAllSetting;

	// 미사일 매니저
	missileManager*	m_pMissileMgr;
	int				m_nFireCount;
	int				m_nRandFireCount;

	ENEMYKIND m_enemyKind;

	// 타겟
	player*		m_pTarget;

public:
	HRESULT init();
	HRESULT init(const char* szFileName, POINT position);
	HRESULT init(POINT position, POINT destinationPos, ENEMYKIND enemyKind);
	HRESULT init(const char * szFileName, POINT position, POINT destinationPos, ENEMYKIND enemyKind);
	void release();
	void update();
	void render(HDC hdc);

	void move();
	void fire();

	void reSetting(POINT position, POINT destinationPos, ENEMYKIND enemyKind);

	inline missileManager* getMissileMgr()
	{ return m_pMissileMgr; }

	inline RECT getRect() { return m_rc; }
	inline void setTarget(player* pTarget) { m_pTarget = pTarget; }

	inline ENEMYKIND getKind() { return m_enemyKind; }


	enemy();
	~enemy();
};

