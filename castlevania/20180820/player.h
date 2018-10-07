#pragma once

class zombie;

class player
{
private:
	// �÷��̾� �̹���
	image *	 m_pImg;
	image *	 m_pImg2;
	image *	 m_pImg3;

	zombie* m_Zombie;
	
	// �÷��̾� ��Ʈ
	SYNTHESIZE (RECT, m_rc,Rc);
	SYNTHESIZE(RECT, m_Irc, IRC);
	
	// �÷��̾� �Ӽ� ��


	float	m_JumP;

	float	m_SildeP;

	float	m_BackP;

	int		m_SildeC;

	int		m_BackC;

	int		m_JumC;

	int		m_JumMC;
	
	float	m_Speed;


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

	// �÷��̾��� �ɱ� ���
	int		m_PlayerDown;

	// �÷��̾��� �����̵� ���
	bool	m_PlayerSilde;

	// �÷��̾��� ��뽬 ���
	bool	m_PlayerBackDash;

	// �÷��̾��� ���� ���
	bool	m_PlayerStand;

	SYNTHESIZE(bool,m_xCameraOn,XCameraOn);
	SYNTHESIZE(bool, m_yCameraOn, YCameraOn);
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

