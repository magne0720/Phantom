#include "CutParticle.h"

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

bool CutParticle::init(float scaleMax, Color4F baseColor)
{
	if (!Node::init())return false;


	for (int i = 0; i < 20; i++) 
	{
		CutSingle* a = CutSingle::create(3);
		a->setPosition(designResolutionSize*0.7f);
		addChild(a);
	}



	return true;

};

void CutParticle::update(float delta) 
{


};

CutSingle* CutSingle::create(float scaletimer, float decaytimer , float emissionrotate , bool isSprite)
{
	CutSingle *pRet = new CutSingle();
	if (pRet && pRet->init(scaletimer,decaytimer,emissionrotate,isSprite))
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
	scaleTimer = 5.0f;
	emissionRotate = rand() % 360;

	if (isSprite) 
	{

	}
	mySprite = Sprite::create("CloseNormal.png");
	//mySprite->setPosition(designResolutionSize*0.5f);
	addChild(mySprite);

	scheduleUpdate();

	return true;
};

void CutSingle::update(float delta) 
{
	allTimer += 1.0f / 60.0f;

	mySprite->setScale(allTimer* scaleTimer);
	mySprite->setOpacity((int)(255.0f-allTimer/scaleTimer*255.0f));
	//setPosition(designResolutionSize*0.7f);


	if (getOpacity() <= 0) 
	{
		removeFromParentAndCleanup(true);
	}
};
