#include "TitleBackground.h"
#include "AllTags.h"
#include "TitleTulip.h"
#include "Batterfly.h"
#include "TitleWood.h"

using namespace cocos2d;
using namespace std;

bool TitleBackground::init()
{
	if (!Sprite::init()) return false;

	//this->initWithFile("Title/Back.png");
	//this->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);

	auto wood = TitleWood::create();
	this->addChild(wood);

	auto tulip = TitleTulip::create();
	this->addChild(tulip);

	auto fly = Batterfly::create();
	fly->setPosition(designResolutionSize*0.5f);
	this->addChild(fly);

	auto ground = Sprite::create("Title/Ground.png");
	ground->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->addChild(ground);

	this->setContentSize(ground->getContentSize());

	return true;
}

TitleBackground* TitleBackground::create()
{
	TitleBackground* pRet = new TitleBackground();
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