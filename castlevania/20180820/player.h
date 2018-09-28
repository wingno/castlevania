#pragma once
class player
{
private:
	// 플레이어 이미지
	image *	 m_pImg;
	image *	 m_pImg2;
	
	// 플레이어 렉트
	RECT	 m_rc;
	
	// 플레이어 속성 값
	float	 m_Speed;
	float	 m_fX;
	float	 m_fY;

	float	m_JumP;

	// 플레이어 프레임설정 속성
	int		m_nRCurrFrameX;
	int		m_nRCurrFrameY;

	int		m_nLCurrFrameX;
	int		m_nLCurrFrameY;
	int		m_nCount;

	int		m_Gravity;

	// 플레이어가 보고 있는 방향 속성
	bool	m_PlayerSee;

	// 플레이어의 공격 모션
	bool	m_PlayerAttack;

	// 플레이어의 점프 모션
	int		m_PlayerJump;

	// 플레이어의 앉기 모션
	int		m_PlayerDown;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	player();
	~player();
};

