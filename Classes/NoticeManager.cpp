#include "NoticeManager.h"

using namespace cocos2d;

NoticeManager* NoticeManager::create()
{
	NoticeManager *pRet = new NoticeManager();
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

bool NoticeManager::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}