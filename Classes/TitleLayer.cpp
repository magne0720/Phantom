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
	/*switch (TIME_ZONE)
	{
	case MORNING:
		sky->setColor(getColorCode(eColor::SKY));
		break;
	case EVENING:
		sky->setColor(getColorCode(eColor::ORANGE));
		break;
	case NIGHT:
		sky->setColor(getColorCode(eColor::INDIGO));
		break;
	case STAR:
		sky->setColor(getColorCode(eColor::INDIGO));
		break;
	}*/
	this->addChild(sky);

	auto cloud = ScrollSprite::create("Title/Back.png", 2.0f, ScrollSprite::eOrientation::landscape);
	//cloud->setPosition(designResolutionSize*0.5f);
	this->addChild(cloud);

	ws = WoodScroll::create(_woodScrollSpeed, saveData->loadClear());
	this->addChild(ws);

	ts = TitleScroll::create(_scrollSpeed, saveData->loadClear());
	this->addChild(ts);

	auto ground = Sprite::create("Title/Ground.png");
	ground->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->addChild(ground);

	TitleCharacter* titleCharacter = TitleCharacter::create();
	titleCharacter->setPosition(designResolutionSize.width*0.5f, designResolutionSize.height*0.175f);
	this->addChild(titleCharacter);

	TitleLogo* titleLogo = TitleLogo::create();
	this->addChild(titleLogo);

	//auto sample = Sprite::create("Character/Sample.png");
	//sample->setPosition(designResolutionSize.width*0.7f, designResolutionSize.height*0.5f);
	//this->addChild(sample);

	//auto player = Sprite::create();
	//auto rect = Rect(0, 0, 300, 300);
	//player->setPosition(designResolutionSize.width*0.5f, 203.0f);
	//player->setTextureRect(rect);
	//player->setColor(Color3B::BLUE);
	//this->addChild(player);

	////ƒuƒŒƒ“ƒh
	//ccBlendFunc blend;
	//blend.src = GL_ZERO;
	//blend.dst = GL_SRC_COLOR;
	//player->setBlendFunc(blend);

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
	if (_replacedScene) return false;
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