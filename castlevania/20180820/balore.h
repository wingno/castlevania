#pragma once

#define START_Y 392
#define START_ARMY 150

class balore
{
private:

	enum BaloreState
	{
		IDLE,
		ATTACK,
		ATTACK2,
		HIT
	};


	image* m_imgEye;
	image* m_imgHead;

	image* m_imgLHand;
	image* m_imgLarm;
	image* m_imgRHand;
	image* m_imgRarm;


	RECT m_rectEye;


	RECT m_handUpRect[2];
	RECT m_handDownRect[2];


	SYNTHESIZE(MonsterStatus, m_mStatus, MStatus);
	

	bool	m_bIsAlive;
	int		m_nPhase;
	int		m_nWhereSee;

	int		m_nPattern;

	
	player* m_pPlayer;

	float	m_fX;
	float	m_fY;

	float	m_fMapX;
	float	m_fMapY;

	float	m_fAngle;
	float	m_fDivineTime;
	float	m_fDamageY;

	float	m_fLArmMapY;
	float	m_fLArmMapX;
	float	m_fRArmMapY;
	float	m_fRArmMapX;

	float	m_fLArmY;
	float	m_fLArmX;
	float	m_fRArmY;
	float	m_fRArmX;

	float	m_fLHandMapY;
	float	m_fLHandMapX;
	float	m_fRHandMapY;
	float	m_fRHandMapX;

	float	m_fLHandY;
	float	m_fLHandX;
	float	m_fRHandY;
	float	m_fRHandX;

	float	m_fRArmAngle;
	float	m_fLArmAngle;



	bool	m_bIsUp;

	bool	m_bIsPatternEnd;

	bool	m_bIsLeft;



	SYNTHESIZE(int, m_nHitDmg, HitDmg);


public:
	HRESULT init();
	void release();
	void update();
	void headRender(HDC hdc);
	void armRender(HDC hdc);


	void phase1Update();

	balore();
	~balore();
};

