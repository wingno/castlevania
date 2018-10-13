#pragma once
class image;
class missileManager;

class enemy
{
private:


	image * m_pImgRMotion;
	image * m_pImgLMotion;
	RECT	m_rc;

	MonsterStatus m_mState;
	EnemyKind m_eKind;

	bool	m_bIsAlive;

	float	m_fX;
	float	m_fY;
	float	m_fSpeed;

	float	m_fangle;



	// 미사일 매니저
	missileManager*	m_pMissileMgr;


	



public:
	HRESULT init(const char* szFileName, POINT position);
	void release();
	void update();
	void render(HDC hdc);

	void move();
	void fire();

	inline missileManager* getMissileMgr()
	{ return m_pMissileMgr; }

	inline bool getIsAlive() { return m_bIsAlive; }
	inline void setIsAlive(bool isAlive) { m_bIsAlive = isAlive; }


	enemy();
	~enemy();
};

