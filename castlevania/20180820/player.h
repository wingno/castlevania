#pragma once


class bulletSoul;
class guardianSoul;
class enchantSoul;
class handItem;
class bodyItem;
class accessoryItem;
class ItemUse;

class ItemUse;

class player
{
private:


	struct itemInven
	{
		std::vector<handItem*>	vecHandItem;
		std::vector<handItem*>::iterator	hiter;

		std::vector<bodyItem*>	vecBodyItem;
		std::vector<bodyItem*>::iterator	biter;

		std::vector<accessoryItem*>	vecAccessoryItem;
		std::vector<accessoryItem*>::iterator	aiter;

		std::vector<ItemUse*>	vecItemUse;
		std::vector<ItemUse*>::iterator	iiter;
	};



	struct soulInven
	{
		std::vector<bulletSoul*>	vecBulletSoul;
		std::vector<bulletSoul*>::iterator	biter;

		std::vector<guardianSoul*>	vecGuardianSoul;
		std::vector<guardianSoul*>::iterator	giter;

		std::vector<enchantSoul*>	vecEnchantSoul;
		std::vector<enchantSoul*>::iterator	eiter;
	};

	
	// 플레이어 이미지
	image *	 m_pImg;
	image *	 m_pImg2;
	image *	 m_pImg3;

	
	// 플레이어 렉트
	SYNTHESIZE (RECT, m_rc,Rc);
	SYNTHESIZE(RECT, m_Irc, IRC);
	
	// 플레이어 속성 값

	SYNTHESIZE(Status ,m_status,State);
	SYNTHESIZE(int, m_nGold, Gold);;


	float	m_fJumP;

	float	m_fSildeP;

	float	m_fBackP;

	int		m_nSildeC;

	int		m_nBackC;

	int		m_nJumC;

	int		m_nJumMC;
	
	float	m_fSpeed;

	int		m_nMotionC;

	int		m_nSkReadyC;


	SYNTHESIZE( float, m_fX,Fx);
	SYNTHESIZE(float, m_fY,FY);

	// 플레이어 프레임설정 속성
	int		m_nRCurrFrameX;
	int		m_nRCurrFrameY;

	int		m_nLCurrFrameX;
	int		m_nLCurrFrameY;
	int		m_nCount;

	float	m_fGravity;

	int		m_nNCurrFrameX;
	int		m_nNCurrFrameY;

	bool	m_bItem;

	// 플레이어가 보고 있는 방향 속성
	bool	m_bPlayerSee;

	// 플레이어의 공격 모션
	bool	m_bPlayerAttack;

	// 플레이어의 점프 모션
	int		m_nPlayerJump;
	bool	m_bPlayerJumpM;
	bool	m_bPlayerJumpDown;
	bool	m_bPlayerJumpAttack;

	// 플레이어의 앉기 모션
	int		m_nPlayerDown;
	bool	m_bPlayerDownAt;

	// 플레이어의 슬라이딩 모션
	bool	m_bPlayerSilde;

	// 플레이어의 백대쉬 모션
	bool	m_bPlayerBackDash;

	// 플레이어의 착지 모션
	SYNTHESIZE(bool, m_bPlayerStand, PlayerStand);

	bool	m_bPlayerSkReady;

	SYNTHESIZE(bool, m_bIsJump, IsJump);


	SYNTHESIZE(bool,m_xCameraOn,XCameraOn);
	SYNTHESIZE(bool, m_yCameraOn, YCameraOn);

	soulInven	m_soulInven;
	SoulSet		m_soulSet;

	itemInven	m_ItemInven;
	ItemSet		m_ItemSet;




	bool testB;



public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void mapMove();

	void mapchackCollision();

	void mapRectCollision();

	Status* getPState() { return &m_status; }

	player();
	~player();
};

