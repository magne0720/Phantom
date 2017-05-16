#include "CharacterAnimation.h"

using namespace cocos2d;
using namespace std;

bool CharacterAnimation::init(string fileName, Size chipSize)
{
	if (!Node::init()) return false;

	vector<SpriteFrame*> charSp;
	Sprite* sp = Sprite::create(fileName);
	_mySprite = Sprite::create();
	this->addChild(_mySprite);
	_animationChache = AnimationCache::sharedAnimationCache();

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

	_animFront = Animation::create();
	_animBack = Animation::create();
	_animLeft = Animation::create();
	_animRight = Animation::create();

	for (int i = 0; i < width; i++)
	{
		_animFront->addSpriteFrame(charSp[i]);
		_animBack->addSpriteFrame(charSp[width + i]);
		_animLeft->addSpriteFrame(charSp[2 * width + i]);
		_animRight->addSpriteFrame(charSp[3 * width + i]);
	}

	_animFront->setDelayPerUnit(0.5f);
	_animBack->setDelayPerUnit(0.5f);
	_animLeft->setDelayPerUnit(0.5f);
	_animRight->setDelayPerUnit(0.5f);

	_animationChache->addAnimation(_animFront, "FRONT");
	_animationChache->addAnimation(_animBack, "BACK");
	_animationChache->addAnimation(_animLeft, "LEFT");
	_animationChache->addAnimation(_animRight, "RIGHT");

	changeAnimation("FRONT");

	return true;
}

CharacterAnimation* CharacterAnimation::create(string fileName, Size chipSize)
{
	CharacterAnimation* pRet = new CharacterAnimation();
	if (pRet && pRet->init(fileName, chipSize))
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

void CharacterAnimation::changeAnimation(string dirName)
{
	_mySprite->stopAllActions();
	Animation* anim = _animationChache->animationByName(dirName);
	auto action = RepeatForever::create(Animate::create(anim));
	_mySprite->runAction(action);
}