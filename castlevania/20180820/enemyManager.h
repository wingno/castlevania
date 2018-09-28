#pragma once
#include <vector>
#include "enemy.h"

class enemyManager
{
private:
	// std::vector 사용 원소 : enemy*
	// 기존에 알고 있던 배열과 같은 형태로 저장된다
	std::vector<enemy*>	m_vecEnemy;
	// <enemy* 를 원소로 가지는 vector>의 원소의 주소값을 담는 변수
	std::vector<enemy*>::iterator	m_iter;



	bool m_bisAllClear;

	bool m_bisSetting;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);






	void setEnemy(int countX, int countY, int stage, int baseX, int baseY, int intervalX, int intervalY);

	void setEnemy(vector<int> vec, int stage);

	void setTarget(spaceShip* pTarget);


	inline bool getisAllClear() { return m_bisAllClear; };

	inline bool getIsSetting() { return m_bisSetting; }

	inline std::vector<enemy*>	getVecEnemy() { return m_vecEnemy; }
	inline std::vector<enemy*>::iterator getIterEnemy() { return m_iter; }

	enemyManager();
	~enemyManager();
};

