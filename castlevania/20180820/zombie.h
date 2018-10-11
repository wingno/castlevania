#pragma once

class image;


class zombie
{

	image* m_imgzombi;
	SYNTHESIZE(RECT, m_rc, rc);
	


	//¾Ö³Ê¹Ì 1
	SYNTHESIZE(float, m_fZombieX, zomX);
	SYNTHESIZE(float, m_fZombiey, zomY);
	int m_nZombieFX;
	int m_nZombieFY;
	int m_nZombieIDX;
	int  m_nZombiecount;
	bool  m_bZombieMove, m_bZombiestand, m_bZombiedead;
 	SYNTHESIZE(bool, m_bAlive, Alive);

public:
	zombie();
	~zombie();

	HRESULT init(int startX, int startY);
	void release();
	void update();
	void render(HDC hdc);
};

