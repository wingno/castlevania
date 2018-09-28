#pragma once
class room
{
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);


	room();
	~room();
};

