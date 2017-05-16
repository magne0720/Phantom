#include "TitleLogo.h"
#include "AllTags.h"

using namespace cocos2d;

bool TitleLogo::init()
{
	if (!Node::init()) return false;

	_logoSp = Sprite::create("HelloWorld.png");
	_logoSp->setPosition(designResolutionSize.width*0.5f, designResolutionSize.height*1.2f);
	auto move = MoveTo::create(3, Vec2(designResolutionSize.width*0.5f, designResolutionSize.height*0.7f));
	_logoSp->runAction(move);
	this->addChild(_logoSp);

	_shadowSp = Sprite::create("HelloWorld.png");
	_shadowSp->setColor(Color3B::BLACK);
	_shadowSp->setOpacity(70);
	_shadowSp->setScale(1.02f);
	_shadowSp->setScaleX(1.1f);
	_shadowSp->setPosition(_logoSp->getContentSize().width*0.5f, _logoSp->getContentSize().height*0.45f);
	_logoSp->addChild(_shadowSp, -1);

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