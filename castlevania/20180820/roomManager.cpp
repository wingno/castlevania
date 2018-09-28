#include "stdafx.h"
#include "roomManager.h"
#include "room.h"


roomManager::roomManager()
{
}


roomManager::~roomManager()
{
}

HRESULT roomManager::init()
{
	return S_OK;
}

void roomManager::release()
{
}

void roomManager::update()
{
}

void roomManager::render(HDC hdc)
{
}

room * roomManager::addRoom(string roomName, room * pRoom)
{
	if (!pRoom)	return NULL;

	m_mapRooms.insert(pair<string, room*>(roomName, pRoom));

	return pRoom;
}

HRESULT roomManager::changeRoom(string sceneName)
{

	// 맵에서 바꾸고자하는 씬을 찾는다
	m_iter = m_mapRooms.find(sceneName);
	// 맵에서 바꾸고자하는 씬을 못 찾으면
	if (m_iter == m_mapRooms.end())	return E_FAIL;

	// 바꾸고자하는 씬과 현재씬이 같으면
	if (m_iter->second == m_pCurrRoom)	return S_OK;

	// 바꾸고자하는 씬을 찾았으면 초기화
	if (SUCCEEDED(m_iter->second->init()))
	{
		// 초기화 성공 시, 현재 씬을 release
		if (m_pCurrRoom)
			m_pCurrRoom->release();

		// 현재 씬을 바꾸고자하는 씬으로 교체
		m_pCurrRoom = m_iter->second;
		return S_OK;
	}

	return E_FAIL;

}

