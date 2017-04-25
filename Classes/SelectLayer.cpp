#include "SelectLayer.h"
#include "NoticeManager.h"

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

	NoticeManager* noticeManager = NoticeManager::create();
	this->addChild(noticeManager);

	return true;
}