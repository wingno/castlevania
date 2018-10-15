#include "stdafx.h"
#include "missile.h"
#include "player.h"
#include "room.h"

//using namespace MY_UTIL;

HRESULT missile::init()
{
	m_fAngle = PI / 2;
	m_fRange = 500.0f;
	m_fSpeed = 5.0f;
	m_fX = 0.0f;
	m_fY = 0.0f;
	m_fFiredX = 0.0f;
	m_fFiredY = 0.0f;
	m_isFire = false;

	//memset(&m_rc, 3, sizeof(m_rc));
	ZeroMemory(&m_rc, sizeof(m_rc));

	m_pImg = IMAGEMANAGER->findImage("enemy_missile_1");
	m_pPlayer = g_mainGame.getPlayer();

	return S_OK;
}

HRESULT missile::init(const char * szImageName, float speed,
	float x, float y, float angle, float range ,int kind)
{
	m_fAngle = angle;
	m_fRange = range;
	m_fSpeed = speed;
	m_fX = x;
	m_fY = y;
	m_fFiredX = x;
	m_fFiredY = y;
	m_isFire = false;

	m_nKind = kind;

	m_fMapX = m_fX - ROOMMANAGER->getCurrRoom()->getPosMap().x;
	m_fMapY = m_fY - ROOMMANAGER->getCurrRoom()->getPosMap().y;

	//memset(&m_rc, 3, sizeof(m_rc));
	ZeroMemory(&m_rc, sizeof(m_rc));

	switch (kind)
	{
	case 0:
		m_pImg = IMAGEMANAGER->findImage("image/RipperL.bmp");
		break;
	case 1:
		m_pImg = IMAGEMANAGER->findImage("image/RipperR.bmp");
		break;
	default:
		break;
	}

	

	return S_OK;
}

void missile::release()
{
}

void missile::update()
{
	move();
}

void missile::render(HDC hdc)
{
	if (m_isFire)
	{
		Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
		if (m_nKind ==0)
		{
			m_pImg->render(hdc, m_fMapX - 8*3, m_fMapY - 4*3,176,8,16,8,3);
		}
		else if (m_nKind == 1)
		{
			m_pImg->render(hdc, m_fMapX - 8*3, m_fMapY - 4*3,0,8,16,8,3);
		}
		else
		{
			m_pImg->render(hdc, m_fMapX - m_pImg->getWidth() / 2, m_fMapY - m_pImg->getHeight() / 2);
		}

	}
}

void missile::fire(float x, float y)
{
	if (!m_isFire)
	{
		m_isFire = true;
		// ���� ��ġ
		m_fFiredX = m_fX = x;
		m_fFiredY = m_fY = y;


		if (m_nKind < 2)
		{
			m_rc = RectMakeCenter(m_fX, m_fY,
				m_pImg->getFrameWidth()*3, 8*3);
		}
		else 
		{
			m_rc = RectMakeCenter(m_fX, m_fY,
				m_pImg->getWidth(), m_pImg->getHeight());
		}


		//// �÷��̾��� ��ġ�� �˾ƾ� ������ ���� �� �ִ�
		//if (m_pPlayer)
		//{
		//	m_fAngle = MY_UTIL::getAngle(
		//		m_fX, m_fY,
		//		m_pPlayer->getFx(), m_pPlayer->getFY());
		//}

		int a = 0;
	}
}

void missile::move()
{
	if (m_isFire)
	{
		m_fX += cosf(m_fAngle) * m_fSpeed;
		m_fY += -sinf(m_fAngle) * m_fSpeed;

		m_fMapX = m_fX - ROOMMANAGER->getCurrRoom()->getPosMap().x;
		m_fMapY = m_fY - ROOMMANAGER->getCurrRoom()->getPosMap().y;

		if (m_nKind < 2)
		{
			m_rc = RectMakeCenter(m_fMapX, m_fMapY,
				m_pImg->getFrameWidth()*3, 8*3);
		}
		else
		{
			m_rc = RectMakeCenter(m_fX, m_fY,
				m_pImg->getWidth(), m_pImg->getHeight());
		}

		if (m_fRange < MY_UTIL::getDistance(m_fFiredX, m_fFiredY, m_fX, m_fY))
		{
			m_isFire = false;
		}
	}
}

missile::missile()
{
}


missile::~missile()
{
}
