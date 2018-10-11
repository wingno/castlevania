#include "stdafx.h"
#include "ItemUse.h"


void ItemUse::init(int cType, int cCount, int cIdx, int cAtt, int cDef, int cStr, int cInt, int cCon, int cLuc, int cHp, int cMp, string cName, string cExplanation)
{
	item::init(cType, cCount, cIdx, cAtt, cDef, cStr, cInt, cCon, cLuc, cHp, cMp, cName, cExplanation);
}


void ItemUse::release()
{
}

void ItemUse::update()
{
}

void ItemUse::render()
{
}

ItemUse::ItemUse()
{
}


ItemUse::~ItemUse()
{
}
