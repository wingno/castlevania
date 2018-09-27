#pragma once
#include <vector>
#include "missile.h"
#include "enemyMissile.h"

class missileManager
{
private:
	std::vector<missile*>	m_vecMissile;
	std::vector<missile*>::iterator	m_iter;

	const char* m_szImageName;
	float		m_fRange;
	float		m_fShootAngle;
	int			m_nMaxCount;

	// Å¸°Ù
	player*	m_pTarget;

public:
	HRESULT init();
	HRESULT init(const char* szImageName, float range, int maxCount);
	void release();
	void update();
	void render(HDC hdc);

	void fire(float x, float y, float angle, float speed,int patton=0);
	void fire(float x, float y);
	void move();

	inline std::vector<missile*> getVecMissile()
	{
		return m_vecMissile;
	}
	inline void setTarget(player* pTarget) { m_pTarget = pTarget; }

	missileManager();
	~missileManager();
};

