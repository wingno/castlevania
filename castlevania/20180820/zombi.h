#pragma once

class image;


class zombi
{

	image* m_zombi;
	RECT	m_rc;
	SYNTHESIZE(POINT, m_posMap, PosMap);



	//¾Ö³Ê¹Ì 1
	float zombiX, zombiy;
	int zombiFX, zombiFY;
	int zombiIDX;
	int  zombicount;
	bool  zombimove, zombistand, zombidead;
	bool Alive;

public:
	zombi();
	~zombi();

	inline bool getlive() { return Alive; }
	inline void setlive(bool live) { Alive = live; }
	


	HRESULT init(int startX, int startY);
	void release();
	void update();
	void render(HDC hdc);
};

