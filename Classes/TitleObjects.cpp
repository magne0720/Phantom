#include "TitleObjects.h"

using namespace cocos2d;
using namespace std;

bool TitleObjects::init()
{
	if (!Node::init()) return false;

	

	return true;
}

TitleObjects* TitleObjects::create()
{
	TitleObjects* pRet = new TitleObjects();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}