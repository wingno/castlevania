#pragma once

class image;


class zombie
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
	SYNTHESIZE(bool, m_Alive, Avlie);

public:
	zombie();
	~zombie();

	HRESULT init(int startX, int startY);
	void release();
	void update();
	void render(HDC hdc);
};

