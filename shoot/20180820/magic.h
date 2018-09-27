#pragma once
class missileManager;

class magic
{
private:
	image*	m_imgmagic;
	SYNTHESIZE( missileManager*	,m_pMissileMg, MissileMgr);

	SYNTHESIZE(bool, m_bIsAlive, IsAlive);

	int m_fX;
	int m_fY;
	

	float	m_fangle;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	magic();
	~magic();
};

