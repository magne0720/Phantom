#include "Batterfly.h"

using namespace cocos2d;

bool Batterfly::init(bool purple, bool blue)
{
	if (!Sprite::init()) return false;

	_bPurple = purple;
	_bBlue = blue;
	_scaling = 0.1f;

	_mySp = Sprite::create("Title/Batterfly.png");
	_mySp->setAnchorPoint(Vec2(0.5f,0.2f));
	
	this->addChild(_mySp);

	this->scheduleUpdate();

	return true;
}

Batterfly* Batterfly::create(bool purple, bool blue)
{
	auto pRet = new Batterfly();
	if (pRet && pRet->init(purple, blue))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return pRet;
	}
}

void Batterfly::update(float delta)
{
	if (scaleRange(_mySp->getScaleY()) == 0.0f)
	{
		_scaling = abs(_scaling);
	}
	else if (scaleRange(_mySp->getScaleY()) == 1.0f)
	{
		_scaling = abs(_scaling) * -1;
	}
	_mySp->setScaleY(_mySp->getScaleY() + _scaling);
}

float Batterfly::scaleRange(float f)
{
	if (f <= 0.0f) return 0.0f;
	if (f >= 1.0f) return 1.0f;
	return f;
}