#include "Tulip.h"

using namespace cocos2d;

bool Tulip::init()
{
	if (!Sprite::init()) return false;



	return true;
}

Tulip* Tulip::create()
{
	auto pRet = new Tulip();
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