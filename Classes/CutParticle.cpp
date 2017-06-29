#include "CutParticle.h"


CutSingle* CutSingle::create(string name,float scaletimer, float decaytimer, float emissionrotate)
{
	CutSingle *pRet = new CutSingle();
	if (pRet && pRet->init(name, scaletimer, decaytimer, emissionrotate))
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

bool CutSingle::init(string name,float scaletimer, float decaytimer, float emissionrotate)
{
	if (!Node::init())return false;

	scaleTimer = scaletimer;
	decayTimer = decaytimer;
	emissionRotate = emissionrotate;

	//emissionRotate = rand() % 360;

	mySprite = Sprite::create(name);
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

CutParticle* CutParticle::create(string name,int num,float scaleMax, Color4F baseColor)
{
	CutParticle *pRet = new CutParticle();
	if (pRet && pRet->init(name,num,scaleMax,baseColor))
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

bool CutParticle::init(string name,int num,float scale, Color4F baseColor)
{
	if (!Node::init())return false;

	fromPosition = Vec2(0, 0);
	toPosition = Vec2(0, 0);

	spriteName = name;

	scaleMax = scale;
	absoluteNumber = num;

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
		if (cuts.size() < absoluteNumber)
		{
			CutSingle* b = CutSingle::create(spriteName,scaleMax);
			addChild(b);
			b->setPosition(getRandoLine(random<float>(1, 100) / 100));
			cuts.pushBack(b);
		}
	}
};

//���Ԋu�ɐ���
void CutParticle::createParticle()
{
	cuts.clear();
	for (int i = 0; i < absoluteNumber; i++)
	{
		CutSingle* b = CutSingle::create(spriteName,scaleMax);
		addChild(b);
		b->setPosition(getRandoLine((float)i/(float)absoluteNumber));
		cuts.pushBack(b);
		CutSingle* a = CutSingle::create(spriteName,scaleMax);
		addChild(a);
		a->setPosition(getRandoLine((float)(absoluteNumber-i)/(float)absoluteNumber));
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
