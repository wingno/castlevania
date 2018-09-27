#pragma once
class scoreBoard
{
private:
	image* m_imgBoard;
	image* m_imgNum;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);


	scoreBoard();
	~scoreBoard();
};

