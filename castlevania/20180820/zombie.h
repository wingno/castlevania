#pragma once

class image;


class zombie
{

	image* m_zombi;
	SYNTHESIZE(RECT, m_rc, rc);
	SYNTHESIZE(POINT, m_posMap, PosMap);



	//¾Ö³Ê¹Ì 1
	SYNTHESIZE(float, zombiX, zomX);
	SYNTHESIZE(float, zombiy, zomY);
	int zombiFX;
	int zombiFY;
	int zombiIDX;
	int  zombicount;
	bool  zombimove, zombistand, zombidead;
 	SYNTHESIZE(bool, m_Alive, Alive);

public:
	zombie();
	~zombie();

	HRESULT init(int startX, int startY);
	void release();
	void update();
	void render(HDC hdc);
};

