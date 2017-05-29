#include "TitleLayer.h"
#include "TitleCharacter.h"
#include "AllTags.h"
#include "TitleLogo.h"
#include "TitleSelectScene.h"

using namespace cocos2d;

bool TitleLayer::init()
{
	if (!Layer::init()) return false;

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(TitleLayer::onTouchBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	tbg = TitleBackground::create();
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

bool TitleLayer::onTouchBegan(Touch* touch, Event* event)
{
	((TitleSelectScene*)this->getParent())->replaceSelect();
	return true;
}