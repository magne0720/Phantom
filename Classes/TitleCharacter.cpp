#include "TitleCharacter.h"
#include "SpriteAnimation.h"

using namespace cocos2d;

bool TitleCharacter::init()
{
	if (!Sprite::init()) return false;

	auto sp = SpriteAnimation::create("Character/HelloWorld%d.png", 2, 0.5f);
	this->addChild(sp);

	return true;
}

TitleCharacter* TitleCharacter::create()
{
	TitleCharacter* pRet = new TitleCharacter();
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