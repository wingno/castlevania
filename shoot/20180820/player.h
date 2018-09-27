#pragma once

class missileManager;
class progressBar;
class action;
class animation;
class battleScene;


enum state
{
	IDLE,
	FRONT,
	BACK,
	START,
	DEAD,
	NUM
};
class player
{
private:
	image * m_img;
	image * m_imgFront;
	image * m_imgBack;

	RECT	m_rc;
	float	m_fSpeed;
	float	m_fX;
	float	m_fY;

	float	m_fdeadCount;

	animation * m_pAni_1;
	animation * m_pAni_2;

	SYNTHESIZE( battleScene*, m_pbattleScene,BattleScene);

	state	m_shipState;


	

	missileManager*	m_pMissileMgr;


	progressBar*	m_pHPBar;
	int				m_nCurrHP;
	int				m_nMaxHP;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	inline RECT getRect() { return m_rc; }
	inline float getX() { return m_fX; }
	inline float getY() { return m_fY; }

	//inline progressBar* getHPBar() { return m_pHPBar; }
	inline void setCurrHP(int hp) { m_nCurrHP = hp; }
	//inline void damaged(int damage) { m_nCurrHP -= damage; }
	void damaged(int damage);

	inline missileManager* getMissileMgr()
	{
		return m_pMissileMgr;
	}

	void mapCollider();

	player();
	~player();
};

