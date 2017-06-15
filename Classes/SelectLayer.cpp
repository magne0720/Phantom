#include "SelectLayer.h"
#include "PictureManager.h"
#include "SelectBackground.h"
#include "AllTags.h"

using namespace cocos2d;

SelectLayer* SelectLayer::create()
{
	SelectLayer *pRet = new SelectLayer();
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

SelectLayer* SelectLayer::create(cocos2d::Color4F color)
{
	SelectLayer *pRet = new SelectLayer();
	if (pRet && pRet->init(color))
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

bool SelectLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	PictureManager* pictureManager = PictureManager::create();
	this->addChild(pictureManager);

	SelectBackground* selectBackground = SelectBackground::create();
	selectBackground->setZOrder(-1);
	this->addChild(selectBackground);

	//_toTitle = Sprite::create("Select/ToTitle.png");
	//_toTitle->setPosition(designResolutionSize.width*0.07f, designResolutionSize.height*0.9f);
	//this->addChild(_toTitle);

	return true;
}

bool SelectLayer::init(Color4F color)
{
	if (!Layer::init())
	{
		return false;
	}

	PictureManager* pictureManager = PictureManager::create();
	this->addChild(pictureManager);

	SelectBackground* selectBackground = SelectBackground::create(color);
	selectBackground->setZOrder(-1);
	this->addChild(selectBackground);

	// “h‚è‚Â‚Ô‚µ‚½‰~i‘å‚«‚È“_j
	_dot = DrawNode::create();
	_dot->drawDot(Vec2::ZERO, designResolutionSize.width * 0.7f, color);
	_dot->setPosition(designResolutionSize*0.5f);
	this->addChild(_dot);

	auto scale = ScaleTo::create(1.5f, 0.0f);
	auto easeIn = EaseSineIn::create(scale);
	auto call = CallFunc::create([&]() {
		_dot->removeFromParentAndCleanup(true);
	});
	auto seq = Sequence::create(easeIn, call, NULL);
	_dot->runAction(seq);

	return true;
}