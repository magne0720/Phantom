#include "TitleCharacter.h"
#include "TitleLayer.h"

using namespace cocos2d;

bool TitleCharacter::init()
{
	if (!Sprite::init()) return false;

	_charAnim = CharacterAnimation::create("Character/TitleAnim.png", Size(250, 250), 0.3f);
	this->addChild(_charAnim);
	_charAnim->changeAnimation(DIR::RIGHT);
	_state = eSTATE::MOVE;

	this->scheduleUpdate();

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
			_charAnim->stopAnimation(DIR::FRONT);
			changeState();
			((TitleLayer*)this->getParent())->tbg->_scSp->setScrollSpriteSpeed(0);
		}
		break;
	case TitleCharacter::STAND:
		if (_timer > 2.0f)
		{
			_state = eSTATE::JUMP;
			_timer = 0.0f;
			_charAnim->stopAction();
			auto rotateR = RotateTo::create(0.5f,15);
			auto rotateL = RotateTo::create(0.5f, -15);
			auto rotateC = RotateTo::create(0.5f, 0);
			auto jump = JumpBy::create(0.5f, Vec2(0, 0), 20.0f, 1);
			auto flip = FlipX::create(true);
			auto flipF = FlipX::create(false);
			auto spo0 = Spawn::create(jump, rotateR, flip, NULL);
			auto spo1 = Spawn::create(jump, rotateL, flipF, NULL);
			auto spo2 = Spawn::create(jump, rotateC, flipF, NULL);
			auto seq = Sequence::create(spo0, spo1, spo0, spo2, NULL);
			_charAnim->getSp()->runAction(seq);
		}
		break;
	case TitleCharacter::JUMP:
		if (_timer > 3.0f)
		{
			_state = eSTATE::MOVE;
			_timer = 0.0f;
			_charAnim->startAnimation(DIR::RIGHT);
			((TitleLayer*)this->getParent())->tbg->_scSp->setScrollSpriteSpeed(((TitleLayer*)this->getParent())->tbg->_scrollSpeed);
			changeState();
		}
		break;
	default:
		break;
	}
	_timer += delta;
}

void TitleCharacter::changeState()
{
	auto jump = JumpBy::create(0.5f, Vec2(0, 0), 5.0f, 1);
	_charAnim->runAction(jump);
}