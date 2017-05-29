#include "SelectBackground.h"
#include "AllTags.h"

using namespace cocos2d;

SelectBackground* SelectBackground::create()
{
	SelectBackground* pRet = new SelectBackground();
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

bool SelectBackground::init()
{
	if (!Node::init()) return false;

	int sizeX = 0, sizeY = 0;
	float sumX = 0.0f, sumY = 0.0f;
	ParticleSystemQuad* p = ParticleSystemQuad::create("Select/SelectBack.plist");
	p->setPosition(designResolutionSize*0.5f);
	p->setPosVar(designResolutionSize*0.5f);
	p->setEmissionRate(0.00010417 * (designResolutionSize.width*designResolutionSize.height));
	this->addChild(p);

	return true;
}