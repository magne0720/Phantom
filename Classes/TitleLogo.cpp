#include "TitleLogo.h"

using namespace cocos2d;

bool TitleLogo::init()
{
	if (!Node::init()) return false;

	return true;
}

TitleLogo* TitleLogo::create()
{
	TitleLogo* pRet = new TitleLogo();
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