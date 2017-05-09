#include "TitleLayer.h"
#include "TitleCharacter.h"

using namespace cocos2d;

bool TitleLayer::init()
{
	if (!Layer::init()) return false;

	TitleCharacter* titleCharacter = TitleCharacter::create();
	this->addChild(titleCharacter);

	return true;
}

TitleLayer* TitleLayer::create()
{
	TitleLayer* pRet = new TitleLayer();
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