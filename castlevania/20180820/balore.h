#pragma once

#define START_Y 392
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
	
	player* m_pPlayer;

	float	m_fX;
	float	m_fY;

	float	m_fMapX;
	float	m_fMapY;

	float	m_fAngle;
	float	m_fDivineTime;
	float	m_fDamageY;

	float	m_lArmMapY;
	float	m_lArmMapX;
	float	m_RArmMapY;
	float	m_RArmMapX;

	float	m_lArmY;
	float	m_lArmX;
	float	m_RArmY;
	float	m_RArmX;




	SYNTHESIZE(int, m_nHitDmg, HitDmg);


public:
	HRESULT init();
	void release();
	void update();
	void headRender(HDC hdc);
	void armRender(HDC hdc);

	balore();
	~balore();
};

