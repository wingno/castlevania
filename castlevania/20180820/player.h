#pragma once
class player
{
private:
	struct Status
	{
		int str;
		int con;
		int intel;
		int lck;

		int Att;
		int Def;

		int HP;
		int MP;

		int exp;

	};
	
	// �÷��̾� �̹���
	image *	 m_pImg;
	image *	 m_pImg2;
	
	// �÷��̾� ��Ʈ
	SYNTHESIZE (RECT, m_rc,Rc);
	
	// �÷��̾� �Ӽ� ��

	Status m_status;
	int gold;

	float	m_JumP;

	float	m_SildeP;

	float	m_BackP;

	int		m_SildeC;

	int		m_BackC;

	int		m_JumC;
	
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

	// �÷��̾ ���� �ִ� ���� �Ӽ�
	bool	m_PlayerSee;

	// �÷��̾��� ���� ���
	bool	m_PlayerAttack;

	// �÷��̾��� ���� ���
	int		m_PlayerJump;
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

