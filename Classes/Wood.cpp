#include "Wood.h"

using namespace cocos2d;

bool Wood::init(SpriteFrame* spFrame, bool green, bool brown)
{
	if (!Sprite::init()) return false;

	_bGreen = green;
	_bBrown = brown;

	return true;
}

Wood* Wood::create(SpriteFrame* spFrame, bool green, bool brown)
{
	auto pRet = new Wood();
	if (pRet && pRet->init(spFrame, green, brown))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return pRet;
	}
}