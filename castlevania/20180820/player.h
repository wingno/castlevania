#pragma once

class zombie;


class bulletSoul;
class guardianSoul;
class enchantSoul;

class player
{
private:
	struct Status
	{
		int curStr;
		int originStr;
		int curCon;
		int originCon;
		int curInt;
		int originInt;
		int currLck;
		int originLck;

		int currAtt;
		int originAtt;
		int currDef;
		int originDef;

		int fullHP;
		int curHP;

		int fullMP;
		int curMP;

		int exp;

		int nextExp;

	};

	struct SoulSet
	{
		bulletSoul* bS;
		guardianSoul* gS;
		enchantSoul* eS;
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

	zombie* m_Zombie;
	
	// 플레이어 렉트
	SYNTHESIZE (RECT, m_rc,Rc);
	SYNTHESIZE(RECT, m_Irc, IRC);
	
	// 플레이어 속성 값

	SYNTHESIZE(Status ,m_status,State);
	SYNTHESIZE(int, m_nGold, Gold);;

	float	m_JumP;

	float	m_SildeP;

	float	m_BackP;

	int		m_SildeC;

	int		m_BackC;

	int		m_JumC;

	int		m_JumMC;
	
	float	m_Speed;

	int		m_motionC;


	SYNTHESIZE( float, m_fX,Fx);
	SYNTHESIZE(float, m_fY,FY);

	// 플레이어 프레임설정 속성
	int		m_nRCurrFrameX;
	int		m_nRCurrFrameY;

	int		m_nLCurrFrameX;
	int		m_nLCurrFrameY;
	int		m_nCount;

	float	m_Gravity;

	int		m_nNCurrFrameX;
	int		m_nNCurrFrameY;

	bool	m_Item;

	// 플레이어가 보고 있는 방향 속성
	bool	m_PlayerSee;

	// 플레이어의 공격 모션
	bool	m_PlayerAttack;

	// 플레이어의 점프 모션
	int		m_PlayerJump;
	bool	m_PlayerJumpM;
	bool	m_PlayerJumpDown;
	bool	m_PlayerJumpAttack;

	// 플레이어의 앉기 모션
	int		m_PlayerDown;
	bool	m_PlayerDownAt;

	// 플레이어의 슬라이딩 모션
	bool	m_PlayerSilde;

	// 플레이어의 백대쉬 모션
	bool	m_PlayerBackDash;

	// 플레이어의 착지 모션
	bool	m_PlayerStand;

	SYNTHESIZE(bool, m_bIsJump, IsJump);


	SYNTHESIZE(bool,m_xCameraOn,XCameraOn);
	SYNTHESIZE(bool, m_yCameraOn, YCameraOn);

	soulInven	m_soulInven;
	SoulSet		m_soulSet;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void mapMove();

	void mapchackCollision();

	player();
	~player();
};

