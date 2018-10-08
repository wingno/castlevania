#include "stdafx.h"
#include "zombie.h"
#include "room.h"



HRESULT zombie::init(int startX, int startY)
{

	m_zombi = IMAGEMANAGER->addImage("M1", "MONSTER/NEWZOMBI.bmp", 140, 80, 7, 2, true, RGB(84, 109, 142));


	

	zombiX = startX;
	//350
	zombiy = startY;
	//310;


	zombiFX= zombiFY = 0;

	zombiIDX = 0;

	zombistand = true;
	zombimove = false;
	zombidead = false;
	m_Alive = true;



	m_rc = RectMakeCenter(zombiX, zombiy + 30, m_zombi->getWidth() - 85, m_zombi->getHeight() + 35);


	return S_OK;
}

void zombie::release()
{
}

void zombie::update()
{

	

	if (m_Alive)
	{
		if (zombistand) //좀비나오는모습
		{

			zombiIDX++;
			if (zombiIDX % 12 == 0)
			{

				zombiFX++;
				if (zombiFX > 5)
				{

					zombiFX = 5;
					zombimove = true;
					zombistand = false;

				}
			}
		}

		if (zombimove) //단순 이동모션
		{

			zombiX -= 1;
			

			zombiIDX++;
			zombicount += 1;
			if (zombiIDX % 40
				== 0)

			{

				zombiFX++;
				if (zombiFX > 6)
				{
					zombiFX = 5;


				}
			}

			if (zombicount == 500|| m_rc.left < 170-ROOMMANAGER->getCurrRoom()->getPosMap().x) //이동도중 카운트를 주어서 일정 카운트가되면 데드로 해당하는 모션행동
			{
				zombimove = false;
				zombistand = false;
				zombidead = true;
				zombicount = 0;
				zombiFX = 0;
				zombiFY = 1;

			}
		}


		if (zombidead) //좀비가 데드라고했지만 일정 이상 움직일경우 땅으로 들어가개 만듬
		{

			zombiIDX++;
			if (zombiIDX % 20 == 0)
			{
				zombiFX++;
				if (zombiFX > 5)
				{
					zombiFX = 6;
					zombiX = zombiX + 200;


					zombidead = false;

				}
			}
			if (zombidead == false)
			{
				zombistand = true;
				zombiFY = 0;
				zombiFX = 0;
			}
		}

		m_rc = RectMakeCenter(zombiX - ROOMMANAGER->getCurrRoom()->getPosMap().x, zombiy + 30, m_zombi->getWidth() - 85, m_zombi->getHeight() + 35);
	}
}

void zombie::render(HDC hdc)
{
	if (m_Alive)
	{
		Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);

		m_zombi->frameRender(hdc, zombiX + 40 - m_zombi->getWidth() / 2  - ROOMMANAGER->getCurrRoom()->getPosMap().x, zombiy - m_zombi->getHeight() / 2, zombiFX, zombiFY, 3);
	}
}

zombie::zombie()
{
}


zombie::~zombie()
{
}
