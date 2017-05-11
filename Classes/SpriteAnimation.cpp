#include "SpriteAnimation.h"

using namespace cocos2d;
using namespace std;

bool SpriteAnimation::init(string fileName, int num, float time)
{
	if (!Sprite::init()) return false;

	_switchTime = time;

	anim = Animation::create();
	for (int i = 0; i < num; i++)
	{
		String* spritePath = String::createWithFormat(fileName.c_str(), i);
		anim->addSpriteFrameWithFile(spritePath->getCString());
	}
	anim->setDelayPerUnit(time);
	anim->setRestoreOriginalFrame(true);

	Animate* animate = Animate::create(anim);
	this->runAction(RepeatForever::create(animate));

	return true;
}

SpriteAnimation* SpriteAnimation::create(string fileName, int num, float time)
{
	SpriteAnimation* pRet = new SpriteAnimation();
	if (pRet && pRet->init(fileName, num, time))
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

void SpriteAnimation::setSpriteSwitchTime(float time)
{
	_switchTime = time;
	//anim->setDelayPerUnit(_switchTime);
}