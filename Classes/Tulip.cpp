#include "Tulip.h"

using namespace cocos2d;

bool Tulip::init(SpriteFrame* spFrame, bool red, bool pink, bool green)
{
	if (!Sprite::init()) return false;
	this->initWithSpriteFrame(spFrame);
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);

	_bRed = red;
	_bPink = pink;
	_bGreen = green;

	float time = 0.6f;
	auto scaleMin = ScaleTo::create(time*0.5f, 0.95f);
	auto scaleDef = ScaleTo::create(time*0.5f, 1.0f);
	auto skewR = SkewTo::create(time, 3.0f, 0.0f);
	auto skewL = SkewTo::create(time, -3.0f, 0.0f);
	auto scale = Sequence::create(scaleMin, scaleDef, NULL);
	auto shakeR = Spawn::create(scale, skewR, NULL);
	auto shakeL = Spawn::create(scale, skewL, NULL);
	Sequence* seq = Sequence::create(shakeR, shakeL, NULL);
	auto repeat = RepeatForever::create(seq);
	this->runAction(repeat);

	return true;
}

Tulip* Tulip::create(SpriteFrame* spFrame, bool red, bool pink, bool green)
{
	auto pRet = new Tulip();
	if (pRet && pRet->init(spFrame, red, pink, green))
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

void Tulip::update(float delta)
{
	
}