#pragma once
class slash
{
	RECT	m_rc[4];
	int		m_nRcHP[4];

	image*	m_imgSlash;

	SYNTHESIZE	(int,m_ndamage,Damage);
	
	SYNTHESIZE (bool,m_bisAlive,IsAlive);


public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	int* getRcHP() { return m_nRcHP; }
	void setRcHP(int idx, int RcHP) { m_nRcHP[idx] = RcHP; }

	RECT* getRc() { return m_rc; }
	void setRc(int idx, RECT rc) { m_rc[idx] = rc; }



	slash();
	~slash();
};

