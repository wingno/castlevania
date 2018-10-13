#include "stdafx.h"
#include "enemy.h"
#include "missileManager.h"





HRESULT enemy::init(const char * szFileName, POINT position )
{

	//std::string strFile = std::string(szFileName);
	//m_pImg = IMAGEMANAGER->addImage(strFile, szFileName,
	//	530, 32, 10, 1, true, RGB(255, 0, 255));

	//m_rc = RectMakeCenter(position.x, position.y,
	//	m_pImg->getFrameWidth(), m_pImg->getFrameHeight());

	//m_pMissileMgr = new missileManager;
	//m_pMissileMgr->init("image/bullet.bmp", 200.0f, 10);

	m_fX = position.x;
	m_fY = position.y;

	m_bIsAlive = false;
	m_pMissileMgr = NULL;

	switch (m_eKind)
	{
	case RIPPER:
		m_mState

		break;
	default:
		break;
	}



	return S_OK;
}


void enemy::release()
{
	if (m_pMissileMgr)
	{
		m_pMissileMgr->release();
		delete m_pMissileMgr;
	}
}

void enemy::update()
{

}

void enemy::render(HDC hdc)
{

}

void enemy::move()
{


}

void enemy::fire()
{

}

enemy::enemy()
{
}


enemy::~enemy()
{
}
