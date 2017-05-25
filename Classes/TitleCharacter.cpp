#include "TitleCharacter.h"
#include "CharacterAnimation.h"

using namespace cocos2d;

bool TitleCharacter::init()
{
	if (!Sprite::init()) return false;

	CharacterAnimation* charAnim = CharacterAnimation::create("Character/TitleAnim.png", Size(250, 250));
	this->addChild(charAnim);
	charAnim->changeAnimation(CharacterAnimation::eDIR::FRONT);

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