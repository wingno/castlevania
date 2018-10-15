#pragma once
class image;
class missileManager;
class player;
class animation;
class enemy
{
private:


	image * m_pImgRMotion;
	image * m_pImgLMotion;
	RECT	m_rc;
	
	
	MonsterStatus m_mStatus;
	EnemyKind m_eKind;

	bool	m_bIsAlive;
	bool	m_bIsLeftSee;
	bool	m_bIsGround;

	float	m_fX;
	float	m_fY;

	float	m_fMapX;
	float	m_fMapY;

	float	m_fSpeed;

	float	m_fAngle;
	float	m_fGravity;


	



	// 미사일 매니저
	missileManager*	m_pMissileMgr;
	player* m_pPlayer;

	animation* m_aniL1;
	animation* m_aniL2;
	animation* m_aniR1;
	animation* m_aniR2;
	



public:
	HRESULT init( POINT position, EnemyKind eKind);	
	void release();
	void update();
	void render(HDC hdc);

	void move();
	void fire();
	void mapchackCollision();

	inline missileManager* getMissileMgr()
	{ return m_pMissileMgr; }

	inline bool getIsAlive() { return m_bIsAlive; }
	inline void setIsAlive(bool isAlive) { m_bIsAlive = isAlive; }


	enemy();
	~enemy();
};

