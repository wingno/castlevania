#include "stdafx.h"
#include "zombie.h"



HRESULT zombie::init(int startX, int startY)
{

	m_zombi = IMAGEMANAGER->addImage("M1", "MONSTER/NEWZOMBI.bmp", 140, 80, 7, 2, true, RGB(84, 109, 142));




	zombiX = startX;
	//350
	zombiy = startY;
	//310;
	zombiFX, zombiFY = 0;

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
		if (zombistand) //���񳪿��¸��
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

		if (zombimove) //�ܼ� �̵����
		{

			zombiX -= 1;
			m_rc.right -= 0.5;
			m_rc.left -= 0.5;

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

			if (zombicount == 500 || m_rc.left < 170) //�̵����� ī��Ʈ�� �־ ���� ī��Ʈ���Ǹ� ����� �ش��ϴ� ����ൿ
			{
				zombimove = false;
				zombistand = false;
				zombidead = true;
				zombicount = 0;
				zombiFX = 0;
				zombiFY = 1;

			}
		}


		if (zombidead) //���� ������������ ���� �̻� �����ϰ�� ������ ���� ����
		{

			zombiIDX++;
			if (zombiIDX % 20 == 0)
			{
				zombiFX++;
				if (zombiFX > 5)
				{
					zombiFX = 6;
					zombiX = zombiX + 200;
					m_rc.left = m_rc.left + 200;
					m_rc.right = m_rc.right + 200;

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
	}
}

void zombie::render(HDC hdc)
{
	if (m_Alive)
	{
		Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);

		m_zombi->frameRender(hdc, zombiX + 40 - m_zombi->getWidth() / 2, zombiy - m_zombi->getHeight() / 2, zombiFX, zombiFY, 3);
	}
}

zombie::zombie()
{
}


zombie::~zombie()
{
}
