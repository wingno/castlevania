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

	
	// �÷��̾� �̹���
	image *	 m_pImg;
	image *	 m_pImg2;
	image *	 m_pImg3;

	
	// �÷��̾� ��Ʈ
	SYNTHESIZE (RECT, m_rc,Rc);
	SYNTHESIZE(RECT, m_Irc, IRC);
	
	// �÷��̾� �Ӽ� ��

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

	// �÷��̾� �����Ӽ��� �Ӽ�
	int		m_nRCurrFrameX;
	int		m_nRCurrFrameY;

	int		m_nLCurrFrameX;
	int		m_nLCurrFrameY;
	int		m_nCount;

	float	m_Gravity;

	int		m_nNCurrFrameX;
	int		m_nNCurrFrameY;

	bool	m_Item;

	// �÷��̾ ���� �ִ� ���� �Ӽ�
	bool	m_PlayerSee;

	// �÷��̾��� ���� ���
	bool	m_PlayerAttack;

	// �÷��̾��� ���� ���
	int		m_PlayerJump;
	bool	m_PlayerJumpM;
	bool	m_PlayerJumpDown;
	bool	m_PlayerJumpAttack;

	// �÷��̾��� �ɱ� ���
	int		m_PlayerDown;
	bool	m_PlayerDownAt;

	// �÷��̾��� �����̵� ���
	bool	m_PlayerSilde;

	// �÷��̾��� ��뽬 ���
	bool	m_PlayerBackDash;

	// �÷��̾��� ���� ���
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

