#pragma once

class progressBar;
class animation;
class battleScene;
class slash;
class magic;
class missileManager;

enum bossState
	{
		BOSSIDLE,
		BOSSCHARGE,
		BOSSBIGSLICE,
		BOSSSETTING,
		BOSSSLICE,
		BOSSSTART,
		BOSSDEAD
	};
class sanger
{
private:
	image*	m_imgIdle;
	image*	m_imgBigSlice;
	image*	m_imgSetting;
	image*	m_imgSlice;
	image*	m_imgCharge;

	animation * m_pAni_1;
	animation * m_pAni_2;
	animation * m_pAni_3;
	animation * m_pAni_4;


	RECT	m_rc;
	float	m_fX;
	float	m_fY;

	progressBar*	m_pHPBar;
	int				m_nCurrHP;
	int				m_nMaxHP;

	int				m_nMissileNum;

	bool			m_bBigSlice;

	SYNTHESIZE(slash* ,m_pslash, Slash);

	int				m_nCoolTime;

	SYNTHESIZE(bool,m_bIsAlive,IsAlive);

	float	m_fdeadCount;

	SYNTHESIZE(bossState, m_bossState,BossState);

	SYNTHESIZE(battleScene*, m_pbattleScene, BattleScene);

	SYNTHESIZE(magic*, m_pMagic, Magic);

	SYNTHESIZE(missileManager*, m_pMissileMgr, MissileMgr);


public:

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	inline RECT getRect() { return m_rc; }
	inline float getX() { return m_fX; }
	inline float getY() { return m_fY; }

	inline void setCurrHP(int hp) { m_nCurrHP = hp; }
	//inline void damaged(int damage) { m_nCurrHP -= damage; }
	void damaged(int damage);


	sanger();
	~sanger();
};

