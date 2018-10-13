#include "stdafx.h"
#include "enemyManager.h"
#include "spaceShip.h"


HRESULT enemyManager::init()
{

	return S_OK;
}

void enemyManager::release()
{
	// vector�� ù ���Һ��� ������ ���ұ��� ��ȸ�ϸ� �� ���Ҹ� delete�Ѵ�
	for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
	{
		delete (*m_iter);
	}
	// vector ��ü�� �����Ѵ�
	m_vecEnemy.clear();
}

void enemyManager::update()
{

	// vector�� ù ���Һ��� ������ ���ұ��� ��ȸ�ϸ� �� ���Ҹ� update�Ѵ�
	for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
	{
		if ((*m_iter)->getIsAlive())
		{
			(*m_iter)->update();

		}

		//m_bisSetting = (*m_iter)->getIsSetting();
	}


}

void enemyManager::render(HDC hdc)
{
	// vector�� ù ���Һ��� ������ ���ұ��� ��ȸ�ϸ� �� ���Ҹ� render�Ѵ�
	for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
	{
		if ((*m_iter)->getIsAlive())
			(*m_iter)->render(hdc);


	}
}

void enemyManager::setEnemy(int baseX,int baseY)
{
	

		enemy* pEnemy = new enemy;
		pEnemy->init("image/ufo.bmp", PointMake(baseX, baseY));

		// vector�� ������ ���� �ڿ� ���ο� �����͸� �߰��Ѵ�
		m_vecEnemy.push_back(pEnemy);

}






enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}
