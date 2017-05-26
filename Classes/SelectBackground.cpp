#include "SelectBackground.h"

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

	ParticleSystemQuad* a = ParticleSystemQuad::create("SelectBack.plist");

	return true;
}