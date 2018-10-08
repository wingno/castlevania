#pragma once
class item
{
protected:
	image*	m_imgIcon;
	string	m_sName;
	string	m_sExplanation;

	int		m_nType;
	int		m_nCount;
	int		m_nIdx;

	int m_nChangeAtt;
	int m_nChangeDef;
	int m_nChangeStr;
	int m_nChangeInt;
	int m_nChangeCon;
	int m_nChangeLck;

	int m_nChangeMP;
	int m_nChangeHP;



public:
	item();
	~item();
};

