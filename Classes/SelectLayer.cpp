#include "SelectLayer.h"
#include "PictureManager.h"

using namespace cocos2d;

SelectLayer* SelectLayer::create()
{
	SelectLayer *pRet = new SelectLayer();
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

bool SelectLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	PictureManager* pictureManager = PictureManager::create();
	this->addChild(pictureManager);

	return true;
}