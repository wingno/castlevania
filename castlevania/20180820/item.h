#pragma once
class item
{
protected:
	image*	m_imgIcon;
	string	m_sName;
	string	m_sExplanation;

	int		m_nCount;

public:
	item();
	~item();
};

