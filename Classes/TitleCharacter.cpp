#include "TitleCharacter.h"

using namespace cocos2d;

bool TitleCharacter::init()
{
	if (!Node::init()) return false;


	return true;
}

TitleCharacter* TitleCharacter::create()
{
	TitleCharacter* pRet = new TitleCharacter();
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