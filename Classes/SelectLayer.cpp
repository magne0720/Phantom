#include "SelectLayer.h"
#include "PictureManager.h"
#include "SelectBackground.h"
#include "AllTags.h"
#include "TitleSelectScene.h"
#include "ColorEnum.h"

using namespace cocos2d;

SelectLayer* SelectLayer::create(SaveData* saveData)
{
	SelectLayer *pRet = new SelectLayer();
	if (pRet && pRet->init(saveData))
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

SelectLayer* SelectLayer::create(cocos2d::Color4F color, SaveData* saveData)
{
	SelectLayer *pRet = new SelectLayer();
	if (pRet && pRet->init(color, saveData))
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

bool SelectLayer::init(SaveData* saveData)
{
	if (!Layer::init())
	{
		return false;
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(SelectLayer::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(SelectLayer::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	PictureManager* pictureManager = PictureManager::create(saveData);
	this->addChild(pictureManager);

	_saveData = saveData;
	SelectBackground* selectBackground = SelectBackground::create(Color4F(getColorCode(_saveData->loadLastClear())));
	selectBackground->setZOrder(-1);
	this->addChild(selectBackground);

	_toTitleButton = ToTitleButton::create();
	_toTitleButton->setPosition(designResolutionSize.width*0.07f, designResolutionSize.height*0.9f);
	this->addChild(_toTitleButton);

	return true;
}

bool SelectLayer::init(Color4F color, SaveData* saveData)
{
	if (!Layer::init())
	{
		return false;
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(SelectLayer::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(SelectLayer::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	PictureManager* pictureManager = PictureManager::create(saveData);
	this->addChild(pictureManager);

	SelectBackground* selectBackground = SelectBackground::create(color);
	selectBackground->setZOrder(-1);
	this->addChild(selectBackground);

	_toTitleButton = ToTitleButton::create();
	_toTitleButton->setPosition(designResolutionSize.width*0.07f, designResolutionSize.height*0.9f);
	this->addChild(_toTitleButton);

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

bool SelectLayer::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	Rect rect = _toTitleButton->getBoundingBox();
	if (rect.containsPoint(pTouch->getLocation()))
	{
		return true;
	}
	return false;
}

void SelectLayer::onTouchEnded(Touch* pTouch, Event* pEvent)
{
	if (_isSceneReplace && ((TitleSelectScene*)this->getParent())->_replaceLayer) return;
	_isSceneReplace = true;

	((TitleSelectScene*)this->getParent())->replaceTitle();
}