#pragma once
class image;
class missileManager;
class player;
class animation;

#define AXE_ARMOR_RANGE 400

class enemy
{
private:


	image * m_pImgRMotion;
	image * m_pImgLMotion;
	RECT	m_rc;
	RECT	m_chaserRc;
	
	
	MonsterStatus m_mStatus;
	EnemyKind m_eKind;

	bool	m_bIsAlive;
	bool	m_bIsLeftSee;
	bool	m_bIsGround;
	bool	m_bIsMove;


	float	m_fX;
	float	m_fY;

	float	m_fMapX;
	float	m_fMapY;

	float	m_fSpeed;

	float	m_fAngle;
	float	m_fGravity;
	float	m_fElapsedTime;



	int*	m_pLAni1;
	int*	m_pLAni2;
	int*	m_pRAni1;
	int*	m_pRAni2;
	




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



	void ripperMapchackCollision();
	void axeAromorMapchackCollision();

	void ripperInit(POINT position, EnemyKind eKind);
	void ripperUpdate();
	void ripperMove();
	void ripperRender(HDC hdc);



	void axeArmorInit(POINT position, EnemyKind eKind);
	void axeArmorUpdate();
	void axeArmorRender(HDC hdc);

	inline missileManager* getMissileMgr()
	{ return m_pMissileMgr; }

	inline bool getIsAlive() { return m_bIsAlive; }
	inline void setIsAlive(bool isAlive) { m_bIsAlive = isAlive; }


	enemy();
	~enemy();
};

