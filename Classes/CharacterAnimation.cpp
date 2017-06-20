#include "CharacterAnimation.h"
#include <cmath>

using namespace cocos2d;
using namespace std;

bool CharacterAnimation::init(string fileName, Size chipSize, float delay, bool move)
{
	if (!Node::init()) return false;

	vector<SpriteFrame*> charSp;	// �؂������`�b�v���ꎞ�I�Ɋi�[
	Sprite* sp = Sprite::create(fileName);	// �摜�ǂݍ���
	_mySprite = Sprite::create();			// �L�����N�^�[�X�v���C�g�쐬
	this->addChild(_mySprite);
	_animationChache = AnimationCache::sharedAnimationCache();		// �A�j���[�V�����L���b�V���ɗ��߂邱�Ƃœǂݍ��݌��炷

	int i = 0;
	int width = sp->getContentSize().width / chipSize.width;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Rect rect(x*chipSize.width, y*chipSize.height, chipSize.width, chipSize.height);
			charSp.push_back(SpriteFrame::createWithTexture(sp->getTexture(), rect));
		}
	}

	//-----------------------------------------------------------------------------------------
	// �ړ��p�A�j���[�V����
	//-----------------------------------------------------------------------------------------
	// �A�j���[�V�����쐬
	Animation* _animFront = Animation::create();
	Animation* _animBack = Animation::create();
	Animation* _animLeft = Animation::create();
	Animation* _animRight = Animation::create();

	// �`�b�v��U�蕪��
	for (int i = 1; i < width; i++)
	{
		_animFront->addSpriteFrame(charSp[i]);
		_animBack->addSpriteFrame(charSp[width + i]);
		_animLeft->addSpriteFrame(charSp[2 * width + i]);
		_animRight->addSpriteFrame(charSp[3 * width + i]);
	}

	// �f�B���C�ݒ�
	_animFront->setDelayPerUnit(delay);
	_animBack->setDelayPerUnit(delay);
	_animLeft->setDelayPerUnit(delay);
	_animRight->setDelayPerUnit(delay);

	// �L���b�V���ɗ��߂�
	_animationChache->addAnimation(_animFront, "FRONT");
	_animationChache->addAnimation(_animBack, "BACK");
	_animationChache->addAnimation(_animLeft, "LEFT");
	_animationChache->addAnimation(_animRight, "RIGHT");

	//-----------------------------------------------------------------------------------------
	// �X�g�b�v�p�A�j���[�V����
	//-----------------------------------------------------------------------------------------
	// �A�j���[�V�����쐬
	Animation* _stopFront = Animation::create();
	Animation* _stopBack = Animation::create();
	Animation* _stopLeft = Animation::create();
	Animation* _stopRight = Animation::create();

	// �`�b�v�U�蕪��
	_stopFront->addSpriteFrame(charSp[0]);
	_stopBack->addSpriteFrame(charSp[width]);
	_stopLeft->addSpriteFrame(charSp[width*2]);
	_stopRight->addSpriteFrame(charSp[width*3]);

	// �f�B���C�ݒ�
	_stopFront->setDelayPerUnit(delay);
	_stopBack->setDelayPerUnit(delay);
	_stopLeft->setDelayPerUnit(delay);
	_stopRight->setDelayPerUnit(delay);

	// �L���b�V���ɗ��߂�
	_animationChache->addAnimation(_stopFront, "STOP_F");
	_animationChache->addAnimation(_stopBack, "STOP_B");
	_animationChache->addAnimation(_stopLeft, "STOP_L");
	_animationChache->addAnimation(_stopRight, "STOP_R");

	_dir = eDIR::FRONT;
	_movedAnim = move;
	_movedAnim = !_movedAnim;
	if (!_movedAnim) startAnimation();
	else stopAnimation();

	return true;
}

CharacterAnimation* CharacterAnimation::create(string fileName, Size chipSize, float delay)
{
	CharacterAnimation* pRet = new CharacterAnimation();
	if (pRet && pRet->init(fileName, chipSize, delay, true))
	{
		pRet->autorelease();
		pRet->_movedAnim = true;
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

CharacterAnimation* CharacterAnimation::createInStop(string fileName, Size chipSize, float delay)
{
	CharacterAnimation* pRet = new CharacterAnimation();
	if (pRet && pRet->init(fileName, chipSize, delay, false))
	{
		pRet->autorelease();
		pRet->_movedAnim = false;
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

CharacterAnimation* CharacterAnimation::createInMove(string fileName, Size chipSize, float delay)
{
	CharacterAnimation* pRet = new CharacterAnimation();
	if (pRet && pRet->init(fileName, chipSize, delay, true))
	{
		pRet->autorelease();
		pRet->_movedAnim = true;
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

void CharacterAnimation::changeAnimation(eDIR dirName)
{
	if (_movedAnim)
	{
		startAnimation(dirName);
	}
	else
	{
		stopAnimation(dirName);
	}
}

void CharacterAnimation::changeAnimation(Vec2 dir)
{
	if (abs(dir.x) > abs(dir.y))
	{
		if (dir.x > 0.0f)
		{
			// �E
			changeAnimation(eDIR::RIGHT);
		}
		else
		{
			// ��
			changeAnimation(eDIR::LEFT);
		}
	}
	else
	{
		if (dir.y > 0.0f)
		{
			// ���
			changeAnimation(eDIR::BACK);
		}
		else
		{
			// �O
			changeAnimation(eDIR::FRONT);
		}
	}
}

void CharacterAnimation::stopAnimation(eDIR dirName)
{
	if (_movedAnim == false && _dir == dirName) return;
	_mySprite->stopAllActions();
	_dir = dirName;
	_movedAnim = false;
	Animation* anim;
	switch (dirName)
	{
	case eDIR::FRONT:
		anim = _animationChache->animationByName("STOP_F");
		break;
	case eDIR::BACK:
		anim = _animationChache->animationByName("STOP_B");
		break;
	case eDIR::LEFT:
		anim = _animationChache->animationByName("STOP_L");
		break;
	case eDIR::RIGHT:
		anim = _animationChache->animationByName("STOP_R");
		break;
	default:
		break;
	}
	auto action = RepeatForever::create(Animate::create(anim));
	_mySprite->runAction(action);
}

void CharacterAnimation::stopAnimation()
{
	if (!_movedAnim) return;
	stopAnimation(_dir);
}

void CharacterAnimation::startAnimation(eDIR dirName)
{
	if (_movedAnim && _dir == dirName) return;
	_mySprite->stopAllActions();
	_dir = dirName;
	_movedAnim = true;
	Animation* anim;
	switch (dirName)
	{
	case eDIR::FRONT:
		anim = _animationChache->animationByName("FRONT");
		break;
	case eDIR::BACK:
		anim = _animationChache->animationByName("BACK");
		break;
	case eDIR::LEFT:
		anim = _animationChache->animationByName("LEFT");
		break;
	case eDIR::RIGHT:
		anim = _animationChache->animationByName("RIGHT");
		break;
	default:
		break;
	}
	auto action = RepeatForever::create(Animate::create(anim));
	_mySprite->runAction(action);
}

void CharacterAnimation::startAnimation()
{
	if (_movedAnim) return;
	startAnimation(_dir);
}

void CharacterAnimation::stopAction()
{
	_mySprite->stopAllActions();
}

Sprite* CharacterAnimation::getSp()
{
	return _mySprite;
}

void CharacterAnimation::setDelay(float delayTime)
{
	_animationChache->animationByName("FRONT")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("BACK")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("RIGHT")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("LEFT")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("STOP_F")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("STOP_B")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("STOP_R")->setDelayPerUnit(delayTime);
	_animationChache->animationByName("STOP_L")->setDelayPerUnit(delayTime);
}

float CharacterAnimation::getDelay()
{
	return _animationChache->animationByName("FRONT")->getDelayPerUnit();
}

void CharacterAnimation::setDir(Vec2 dir)
{
	changeAnimation(dir);
}