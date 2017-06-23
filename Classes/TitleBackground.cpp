#include "TitleBackground.h"
#include "AllTags.h"
#include "TitleTulip.h"
#include "Batterfly.h"
#include "TitleWood.h"

using namespace cocos2d;
using namespace std;

bool TitleBackground::init(int clearedStage)
{
	if (!Sprite::init()) return false;

	//auto wood = TitleWood::create();
	//this->addChild(wood);

	auto tulip = TitleTulip::create(clearedStage);
	this->addChild(tulip);

	auto fly = Batterfly::create();
	fly->setPosition(designResolutionSize*0.5f);
	this->addChild(fly);

	this->setContentSize(designResolutionSize * 2.0f);

	return true;
}

TitleBackground* TitleBackground::create(int clearedStage)
{
	TitleBackground* pRet = new TitleBackground();
	if (pRet && pRet->init(clearedStage))
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