#include "TitleLayer.h"
#include "TitleCharacter.h"
#include "AllTags.h"
#include "TitleLogo.h"
#include "TitleSelectScene.h"

using namespace cocos2d;

bool TitleLayer::init()
{
	if (!Layer::init()) return false;

	_replacedScene = false;

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(TitleLayer::onTouchBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	tbg = TitleBackground::create();
	this->addChild(tbg);

	TitleCharacter* titleCharacter = TitleCharacter::create();
	titleCharacter->setPosition(designResolutionSize.width*0.5f, 203.0f);
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