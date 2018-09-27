#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"


HRESULT enemyManager::init()
{
	return S_OK;
}

void enemyManager::release()
{
	// vector의 첫 원소부터 마지막 원소까지 순회하며 각 원소를 delete한다
	for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
	{
		delete (*m_iter);
	}
	// vector 자체를 삭제한다
	m_vecEnemy.clear();
}

void enemyManager::update()
{
	// vector의 첫 원소부터 마지막 원소까지 순회하며 각 원소를 update한다
	for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
	{
	
			(*m_iter)->update();
	}
}

void enemyManager::render(HDC hdc)
{
	// vector의 첫 원소부터 마지막 원소까지 순회하며 각 원소를 render한다
	for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
	{
 			(*m_iter)->render(hdc);
		

	}
}

void enemyManager::setEnemy(int countX, int countY)
{
	for (int i = 0; i < countY; i++)
	{
		for (int j = 0; j < countX; j++)
		{
			enemy* pEnemy;
			pEnemy = new enemy;
			pEnemy->init(PointMake(WINSIZEY + 50,WINSIZEY/2), PointMake(130 + 70 * j, 100 + 60 * i), ZAKU);

			// vector의 마지막 원소 뒤에 새로운 데이터를 추가한다
			m_vecEnemy.push_back(pEnemy);
		}
	}
}

void enemyManager::setEnemy( player * pTarget, int Phase)
{
	switch (Phase)
	{
		case 1:
			for (int i = 0; i < 5; i++)
			{
				enemy* pEnemy;
				pEnemy = NULL;
				for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
				{
					if ((*m_iter) != NULL)
					{
						if (!(*m_iter)->getIsAlive())
						{
							pEnemy = (*m_iter);
							pEnemy->setTarget(pTarget);
							pEnemy->reSetting(PointMake(WINSIZEX + 100, 50), PointMake(-100, 50 + 90 * i), ZAKU);
						}
					}
					break;
				}
				if (pEnemy == NULL)
				{
					pEnemy = new enemy;
					pEnemy->setTarget(pTarget);
					pEnemy->init(PointMake(WINSIZEX + 100, 50), PointMake(-100, 50 + 90 * i), ZAKU);
					m_vecEnemy.push_back(pEnemy);
				}

				// vector의 마지막 원소 뒤에 새로운 데이터를 추가한다
			}
			break;

		case 2:

			for (int i = 0; i < 5; i++)
			{
				enemy* pEnemy;
				pEnemy = NULL;
				for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
				{
					if ((*m_iter) != NULL)
					{
						if (!(*m_iter)->getIsAlive())
						{
							pEnemy = (*m_iter);
							pEnemy->setTarget(pTarget);
							pEnemy->reSetting(PointMake(WINSIZEX + 100, WINSIZEY-50), PointMake(-100, 50 + 90 * i), ZAKU);
						}
					}
					break;
				}
				if (pEnemy == NULL)
				{
					pEnemy = new enemy;
					pEnemy->setTarget(pTarget);
					pEnemy->init(PointMake(WINSIZEX + 100, WINSIZEY - 50), PointMake(-100, 50 + 90 * i), ZAKU);
					m_vecEnemy.push_back(pEnemy);
				}

				// vector의 마지막 원소 뒤에 새로운 데이터를 추가한다
			}
			break;

		case 3:
			for (int i = 0; i < 5; i++)
			{
				enemy* pEnemy;
				pEnemy = NULL;
				for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
				{
					if ((*m_iter) != NULL)
					{
						if (!(*m_iter)->getIsAlive())
						{
							pEnemy = (*m_iter);
							pEnemy->setTarget(pTarget);
							pEnemy->reSetting(PointMake(WINSIZEX + 100, WINSIZEY/2), PointMake(-100, 50 + 90 * i), ZAKU);
						}
					}
					break;
				}
				if (pEnemy == NULL)
				{
					pEnemy = new enemy;
					pEnemy->setTarget(pTarget);
					pEnemy->init(PointMake(WINSIZEX + 100, WINSIZEY/2), PointMake(-100, 50 + 90 * i), ZAKU);
					m_vecEnemy.push_back(pEnemy);
				}

				// vector의 마지막 원소 뒤에 새로운 데이터를 추가한다
			}


			break;

		case 4:
			for (int i = 0; i < 1; i++)
			{
				enemy* pEnemy;
				pEnemy = NULL;
				for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
				{
					if ((*m_iter) != NULL)
					{
						if (!(*m_iter)->getIsAlive())
						{
							pEnemy = (*m_iter);
							pEnemy->setTarget(pTarget);
							pEnemy->reSetting(PointMake(WINSIZEX + (80 * i), WINSIZEY - 60), PointMake(-100, WINSIZEY - 60), INVADERGROUND);
						}
					}
					break;
				}
				if (pEnemy == NULL)
				{
					pEnemy = new enemy;
					pEnemy->setTarget(pTarget);
					pEnemy->init(PointMake(WINSIZEX + (80 * i), WINSIZEY-60), PointMake(-100, WINSIZEY - 60 ), INVADERGROUND);
					m_vecEnemy.push_back(pEnemy);
				}

				// vector의 마지막 원소 뒤에 새로운 데이터를 추가한다
			}
			break;

		case 5:
			for (int i = 0; i < 1; i++)
			{
				enemy* pEnemy;
				pEnemy = NULL;
				for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
				{
					if ((*m_iter) != NULL)
					{
						if (!(*m_iter)->getIsAlive())
						{
							pEnemy = (*m_iter);
							pEnemy->setTarget(pTarget);
							pEnemy->init(PointMake(WINSIZEX + (150 * i), WINSIZEY - 400), PointMake(-100, WINSIZEY - 90), INVADERAIR);
						}
					}
					break;
				}
				if (pEnemy == NULL)
				{
					pEnemy = new enemy;
					pEnemy->setTarget(pTarget);
					pEnemy->init(PointMake(WINSIZEX + (150 * i), WINSIZEY - 400), PointMake(-100, WINSIZEY - 90), INVADERAIR);
					m_vecEnemy.push_back(pEnemy);
				}

				// vector의 마지막 원소 뒤에 새로운 데이터를 추가한다
			}
			break;
		case 6:
			for (int i = 0; i < 3; i++)
			{
				enemy* pEnemy;
				pEnemy = NULL;
				for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
				{
					if ((*m_iter) != NULL)
					{
						if (!(*m_iter)->getIsAlive())
						{
							pEnemy = (*m_iter);
							pEnemy->setTarget(pTarget);
							pEnemy->reSetting(PointMake(WINSIZEX + 100 * i, 50+(50 *i)), PointMake(-100, 50 + 90 * i), JUZAKU);
						}
					}
					break;
				}
				if (pEnemy == NULL)
				{
					pEnemy = new enemy;
					pEnemy->setTarget(pTarget);
					pEnemy->init(PointMake(WINSIZEX + 100 * i, 50 + (50 * i)), PointMake(-100, 50 + 90 * i), JUZAKU);
					m_vecEnemy.push_back(pEnemy);
				}

				// vector의 마지막 원소 뒤에 새로운 데이터를 추가한다
			}
			break;

		case 7:
			for (int i = 0; i < 3; i++)
			{
				enemy* pEnemy;
				pEnemy = NULL;
				for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
				{
					if ((*m_iter) != NULL)
					{
						if (!(*m_iter)->getIsAlive())
						{
							pEnemy = (*m_iter);
							pEnemy->setTarget(pTarget);
							pEnemy->reSetting(PointMake(WINSIZEX + 100 * i, 450 + (50 * i)), PointMake(-100, 50 + 90 * i), JUZAKU);
						}
					}
					break;
				}
				if (pEnemy == NULL)
				{
					pEnemy = new enemy;
					pEnemy->setTarget(pTarget);
					pEnemy->init(PointMake(WINSIZEX + 100 * i, 450 + (50 * i)), PointMake(-100, 50 + 90 * i), JUZAKU);
					m_vecEnemy.push_back(pEnemy);
				}

				// vector의 마지막 원소 뒤에 새로운 데이터를 추가한다
			}
			break;

		case 8:
			for (int i = 0; i < 8; i++)
			{
				enemy* pEnemy;
				pEnemy = NULL;
				for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
				{
					if ((*m_iter) != NULL)
					{
						if (!(*m_iter)->getIsAlive())
						{
							pEnemy = (*m_iter);
							pEnemy->setTarget(pTarget);
							pEnemy->reSetting(PointMake(WINSIZEX + 100 * i, 300 + (20 * i)), PointMake(-100, -100), JUZAKU);
						}
					}
					break;
				}
				if (pEnemy == NULL)
				{
					pEnemy = new enemy;
					pEnemy->setTarget(pTarget);
					pEnemy->init(PointMake(WINSIZEX + 100 * i, 300 + (20 * i)), PointMake(-100, -100 ), JUZAKU);
					m_vecEnemy.push_back(pEnemy);
				}

				// vector의 마지막 원소 뒤에 새로운 데이터를 추가한다
			}
			break;
		default:
			break;
	}

	
}

void enemyManager::setTarget(player * pTarget)
{
	for (m_iter = m_vecEnemy.begin(); m_iter != m_vecEnemy.end(); m_iter++)
	{
		(*m_iter)->setTarget(pTarget);
	}
}

enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}
