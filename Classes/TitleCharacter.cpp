#include "TitleCharacter.h"

using namespace cocos2d;

bool TitleCharacter::init()
{
	if (!Sprite::init()) return false;

	String path = "Character/HelloWorld%d.png";
	anim = Animation::create();
	for (int i = 0; i < 2; i++)
	{
		String* spritePath = String::createWithFormat(path.getCString(), i);
		anim->addSpriteFrameWithFile(spritePath->getCString());
	}
	anim->setDelayPerUnit(0.5f);
	anim->setRestoreOriginalFrame(true);
	Animate* animate = Animate::create(anim);
	this->runAction(RepeatForever::create(animate));

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