#include "TitleLayer.h"
#include "TitleCharacter.h"
#include "AllTags.h"
#include "TitleBackground.h"
#include "TitleLogo.h"

using namespace cocos2d;

bool TitleLayer::init()
{
	if (!Layer::init()) return false;

	auto tbg = TitleBackground::create();
	this->addChild(tbg);

	TitleCharacter* titleCharacter = TitleCharacter::create();
	titleCharacter->setPosition(designResolutionSize.width*0.5f, designResolutionSize.height*0.3f);
	this->addChild(titleCharacter);

	TitleLogo* titleLogo = TitleLogo::create();
	this->addChild(titleLogo);

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