#include "TitleCharacter.h"

using namespace cocos2d;

bool TitleCharacter::init()
{
	if (!Sprite::init()) return false;

	charAnim = CharacterAnimation::create("Character/TitleAnim.png", Size(250, 250));
	this->addChild(charAnim);
	charAnim->changeAnimation(DIR::RIGHT);

	_state = eSTATE::MOVE;

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

void TitleCharacter::update(float delta)
{
	switch (_state)
	{
	case TitleCharacter::MOVE:
		if (_timer > 5.0f)
		{
			_state = eSTATE::STAND;
			_timer = 0.0f;
			charAnim->changeAnimation(DIR::FRONT);
			charAnim->stopAnimation();
		}
		break;
	case TitleCharacter::STAND:
		if (_timer > 2.0f)
		{
			_state = eSTATE::JUMP;
			_timer = 0.0f;

		}
		break;
	case TitleCharacter::JUMP:
		if (_timer > 2.0f)
		{
			_state = eSTATE::MOVE;
			_timer = 0.0f;

		}
		break;
	default:
		break;
	}
	_timer += delta;
}