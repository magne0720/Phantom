#include "TitleObjects.h"

using namespace cocos2d;

bool TitleObjects::init()
{
	if (!Node::init()) return false;

	return true;
}

TitleObjects* TitleObjects::create()
{
	TitleObjects* pRet = new TitleObjects();
	return pRet;
}