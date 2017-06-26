#include "TitleLayer.h"
#include "TitleCharacter.h"
#include "SaveData.h"
#include "TitleLogo.h"
#include "TitleSelectScene.h"
#include "SaveData.h"
#include "ColorEnum.h"

using namespace cocos2d;

bool TitleLayer::init()
{
	if (!Layer::init()) return false;

	_replacedScene = false;

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(TitleLayer::onTouchBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	auto saveData = SaveData::create();

	Rect rect = Rect(0, 0, designResolutionSize.width, designResolutionSize.height);
	Sprite* sky = Sprite::create();
	sky->setTextureRect(rect);
	sky->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->addChild(sky);
	
	ScrollSprite* deco;
	float decoSpeed = 0.05f;
	switch (saveData->loadTimeZone())
	{
	case MORNING:
		sky->setColor(getColorCode(eColor::SKY));

		decoSpeed = 0.5f;
		deco = ScrollSprite::create("Title/Cloud.png", decoSpeed, ScrollSprite::eOrientation::landscape);
		this->addChild(deco);		
		break;
	case EVENING:
		sky->setColor(getColorCode(eColor::ORANGE));

		if (saveData->loadStarAppear())
		{
			deco = ScrollSprite::create("Title/OneStar.png", decoSpeed, ScrollSprite::eOrientation::landscape, getColorCode(eColor::YELLOW));
			this->addChild(deco);
		}		
		break;
	case NIGHT:
		sky->setColor(getColorCode(eColor::INDIGO));

		if (saveData->loadStarAppear())
		{
			deco = ScrollSprite::create("Title/Star.png", decoSpeed, ScrollSprite::eOrientation::landscape, getColorCode(eColor::YELLOW));
			this->addChild(deco);
		}		
		break;
	default:
		break;
	}
	
	int cleareStage = saveData->loadClear();

	ws = WoodScroll::create(_woodScrollSpeed, cleareStage);
	this->addChild(ws);

	ts = TitleScroll::create(_scrollSpeed, cleareStage);
	this->addChild(ts);

	auto ground = Sprite::create("Title/Ground.png");
	ground->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->addChild(ground);

	TitleCharacter* titleCharacter = TitleCharacter::create();
	titleCharacter->setPosition(designResolutionSize.width*0.5f, designResolutionSize.height*0.18f);
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
	if (_replacedScene && ((TitleSelectScene*)this->getParent())->_replaceLayer) return false;
	_replacedScene = true;
	((TitleSelectScene*)this->getParent())->replaceSelect();
	return true;
}

void TitleLayer::setScrollStop()
{
	ws->setScrollSpriteSpeed(0);
	ts->setScrollSpriteSpeed(0);
}

void TitleLayer::setDefaultSpeed()
{
	ws->setScrollSpriteSpeed(_woodScrollSpeed);
	ts->setScrollSpriteSpeed(_scrollSpeed);
}