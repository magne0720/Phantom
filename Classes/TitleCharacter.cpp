#include "TitleCharacter.h"
#include "SpriteAnimation.h"
#include "CharacterAnimation.h"

using namespace cocos2d;

bool TitleCharacter::init()
{
	if (!Sprite::init()) return false;

	CharacterAnimation* charAnim = CharacterAnimation::create("Character/AnimChip.png", Size(60, 60));
	this->addChild(charAnim);

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