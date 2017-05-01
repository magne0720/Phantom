#include "PictureManager.h"
#include "AllTags.h"
//#include "TapDetection.h"


using namespace cocos2d;

PictureManager* PictureManager::create()
{
	PictureManager *pRet = new PictureManager();
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

bool PictureManager::init()
{
	if (!Node::init())
	{
		return false;
	}
	//template<class T>;
	for (int i = 0; i < _stageNum; i++)
	{
		_Pictures[i] = Sprite::create("HelloWorld.png");
		_Pictures[i]->setPosition(designResolutionSize.width*0.3f*i, designResolutionSize.height*0.5f);
		this->addChild(_Pictures[i]);
	}
	
	//baseTap.changeBegan(&PictureManager::onTouchBegan);
	//baseTap.me = &PictureManager::onTouchBegan;
	//baseTap.tapper = this;
	//baseTap.began();
	//baseTap = BaseTap();
	_baseTap.changeBegan(&PictureManager::onTouchBegan, this);
	return true;
}

void PictureManager::touchEnded(Touch* pTouch)
{
	for (int i = 0; i < _stageNum; i++)
	{
		Rect rect = _Pictures[i]->getBoundingBox();
		if (rect.containsPoint(pTouch->getLocation()))
		{
			log("atatta!");
		}
	}
}

bool PictureManager::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	log("Began");
	return true;
}

void PictureManager::onTouchMoved(Touch* pTouch, Event* pEvent)
{

}

void PictureManager::onTouchEnded(Touch* pTouch, Event* pEvent)
{

}