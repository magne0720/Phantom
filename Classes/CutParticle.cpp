#include "CutParticle.h"


CutSingle* CutSingle::create(float scaletimer, float decaytimer, float emissionrotate, bool isSprite)
{
	CutSingle *pRet = new CutSingle();
	if (pRet && pRet->init( scaletimer, decaytimer, emissionrotate, isSprite))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	};
};

bool CutSingle::init(float scaletimer, float decaytimer, float emissionrotate, bool isSprite)
{
	if (!Node::init())return false;

	scaleTimer = scaletimer;
	decayTimer = decaytimer;
	emissionRotate = emissionrotate;

	//emissionRotate = rand() % 360;

	if (isSprite)
	{

	}
	mySprite = Sprite::create("slash.png");
	addChild(mySprite);

	isEnd = false;

	/*
	MoveBy* move = MoveBy::create(scaleTimer, Vec2(random(-200, 200), random(-200, 200)));
	mySprite->runAction(move);
	*/

	/*RotateBy* by = RotateBy::create(scaleTimer, 360*scaleTimer);
	mySprite->runAction(by);
*/
	scheduleUpdate();

	return true;
};

void CutSingle::update(float delta)
{
	allTimer += 1.0f / 60.0f;

	mySprite->setScale(allTimer* scaleTimer);
	if (mySprite->getOpacity() > 0)
	{
		mySprite->setOpacity((int)(255.0f - (allTimer / scaleTimer)*255.0f));
	}
	if (allTimer > scaleTimer)
	{
		isEnd = true;
		unscheduleUpdate();
	}
};

CutParticle* CutParticle::create(float scaleMax, Color4F baseColor)
{
	CutParticle *pRet = new CutParticle();
	if (pRet && pRet->init(scaleMax,baseColor))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	};
};

bool CutParticle::init(float scale, Color4F baseColor)
{
	if (!Node::init())return false;

	fromPosition = Vec2(0, 0);
	toPosition = Vec2(0, 0);

	scaleMax = scale;

	scheduleUpdate();

	return true;
};

void CutParticle::update(float delta) 
{

	for (int i = 0; i < cuts.size(); i++)
	{
		if (cuts.at(i)->isEnd)
		{
			cuts.at(i)->removeFromParentAndCleanup(true);
			cuts.erase(i);
		}
	}
	if (isRoop) 
	{
		CutSingle* b = CutSingle::create(scaleMax);
		addChild(b);
		b->setPosition(getRandoLine(random<float>(1,100)/100));
		cuts.pushBack(b);
	}
};

//ìôä‘äuÇ…ê∂ê¨
void CutParticle::createParticle(int num,float scale)
{
	cuts.clear();
	for (int i = 0; i < num; i++)
	{
		CutSingle* b = CutSingle::create(scale);
		addChild(b);
		b->setPosition(getRandoLine((float)i/(float)num));
		cuts.pushBack(b);
		CutSingle* a = CutSingle::create(scale);
		addChild(a);
		a->setPosition(getRandoLine((float)(num-i)/(float)num));
		cuts.pushBack(a);
	}
};

void CutParticle::startParticle() 
{
	isRoop = true;
};

void CutParticle::stopParticle() 
{
	isRoop = false;
};

void CutParticle::setLine(Vec2 from, Vec2 to) 
{
	fromPosition = from;
	toPosition = to;
};

Vec2 CutParticle::getRandoLine(float alpha)
{
	return  fromPosition*(1 - alpha) + alpha*toPosition;
};
