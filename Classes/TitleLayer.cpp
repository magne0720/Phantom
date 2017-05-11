#include "TitleLayer.h"
#include "TitleCharacter.h"
#include "AllTags.h"
#include "TitleBackground.h"

using namespace cocos2d;

bool TitleLayer::init()
{
	if (!Layer::init()) return false;

	TitleCharacter* titleCharacter = TitleCharacter::create();
	titleCharacter->setPosition(designResolutionSize*0.5f);
	this->addChild(titleCharacter);


	auto tbg = TitleBackground::create();
	this->addChild(tbg);

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