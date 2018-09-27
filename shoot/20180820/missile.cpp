#include "stdafx.h"
#include "missile.h"
#include "player.h"

//using namespace MY_UTIL;

HRESULT missile::init()
{
	m_fAngle = 0;
	m_fRange = 1000.0f;
	m_fSpeed = 5.0f;
	m_fX = 0.0f;
	m_fY = 0.0f;
	m_fFiredX = 0.0f;
	m_fFiredY = 0.0f;
	m_isFire = false;

	m_nDamage = 5;
	//memset(&m_rc, 3, sizeof(m_rc));
	ZeroMemory(&m_rc, sizeof(m_rc));

	m_pImg = IMAGEMANAGER->findImage("enemy_missile_1");

	return S_OK;
}

HRESULT missile::init(const char * szImageName, float speed,
	float x, float y, float angle, float range ,int kind/*=0*/)
{
	m_fAngle = angle;
	m_fRange = range;
	m_fSpeed = speed;
	m_fX = x;
	m_fY = y;
	m_fFiredX = x;
	m_fFiredY = y;
	m_isFire = false;

	m_kind = kind;

	//memset(&m_rc, 3, sizeof(m_rc));
	ZeroMemory(&m_rc, sizeof(m_rc));

	switch (m_kind)
	{
	case 0:
		m_pImg = IMAGEMANAGER->findImage("enemy_missile_1");
		m_nDamage = 3;
		break;
	case 1:
		m_pImg = IMAGEMANAGER->findImage("image/invadermissile.bmp");
		m_rectControler = 40;
		m_nDamage = 10;
		break;
	case 2:
		m_pImg = IMAGEMANAGER->findImage("image/invaderbullet.bmp");
		m_nLifeCount = 0;
		m_nDamage = 5;
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
		


		switch (m_kind)
		{
		case 0:
			m_pImg->render(hdc, m_fX - m_pImg->getWidth() / 2, m_fY - m_pImg->getHeight() / 2);
			break;
		case 1:
			m_pImg->rotateRender(hdc, (-m_fAngle)*(180/PI), m_fX , m_fY );
			break;
		case 2:
			//m_pImg->rotateRender(hdc, m_fX - m_pImg->getWidth() / 2, m_fY - m_pImg->getHeight() / 2,0,0,m_pImg->getWidth(),m_pImg->getHeight(),5);
			m_pImg->rotateRender(hdc, m_nLifeCount, m_fX - m_pImg->getWidth() / 2, m_fY - m_pImg->getHeight() / 2,5);
			break;
		default:
			break;
		}

		//Rectangle(hdc, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);

	}
}

void missile::fire(float x, float y)
{
	if (!m_isFire)
	{
		m_isFire = true;
		// 시작 위치
		m_fFiredX = m_fX = x;
		m_fFiredY = m_fY = y;



		// 플레이어의 위치를 알아야 각도를 구할 수 있다

		switch (m_kind)
		{
		case 0:
			m_rc = RectMakeCenter(m_fX, m_fY,
				m_pImg->getWidth(), m_pImg->getHeight());
			break;
		case 1:
			m_rc = RectMakeCenter(m_fX, m_fY,
				m_pImg->getWidth(), m_pImg->getHeight());
			break;
		case 2:
			if (m_pTarget)
			{
				m_fAngle = MY_UTIL::getAngle(
					m_fX, m_fY,
					m_pTarget->getX(), m_pTarget->getY());

				m_rc = RectMakeCenter(m_fX, m_fY,
					m_pImg->getWidth()*5, m_pImg->getHeight()*5);
				
			}
			break;
		default:
			break;
		}



	}
}

void missile::move()
{
	if (m_isFire)
	{
		

		m_fX += cosf(m_fAngle) * m_fSpeed;
		m_fY += -sinf(m_fAngle) * m_fSpeed;

		m_rc = RectMakeCenter(m_fX, m_fY,
			m_pImg->getWidth(), m_pImg->getHeight());

		if (m_fRange < MY_UTIL::getDistance(m_fFiredX, m_fFiredY, m_fX, m_fY))
		{
			m_isFire = false;
		}
		if (m_kind == 1)
		{
			m_fAngle += 0.015f;
			m_fSpeed = 8;

			m_rc = RectMakeCenter(m_fX- m_pImg->getWidth() + 180, m_fY-m_pImg->getHeight() + m_rectControler *2,
				-80+((m_rectControler)*5), 50);
			m_rectControler++;

			if (m_fY > WINSIZEY)
			{
				m_isFire = false;
				
			}

		}
		else if (m_kind == 2)
		{
			if (m_pTarget)
			{
				if (m_nLifeCount < 150)
				{
					m_fAngle = MY_UTIL::getAngle(
						m_fX, m_fY,
						m_pTarget->getX(), m_pTarget->getY());
					m_nLifeCount++;

				}

			}
		}

	}
}

missile::missile()
{
}


missile::~missile()
{
}
