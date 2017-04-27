#include "TapDetection.h"

USING_NS_CC;
TapDetection* TapDetection::tapDetection = NULL;

TapDetection* TapDetection::sharedTap()
{
	if (tapDetection == NULL)
	{
		tapDetection = new TapDetection();
		if (tapDetection && tapDetection->init())
		{
			tapDetection->autorelease();
			return tapDetection;
		}
		else
		{
			delete tapDetection;
			tapDetection = NULL;
			return NULL;
		}
	}
	return tapDetection;
}

TapDetection::TapDetection()
{

}

bool TapDetection::init()
{
	if (!Node::init())
	{
		return false;
	}

	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	outSideBlock = &TapDetection::outSideBlockT;
	listener->onTouchBegan = CC_CALLBACK_2(TapDetection::titleTouchBegan, this);
	//listener->onTouchMoved = CC_CALLBACK_2(TapDetection::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(TapDetection::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	
	this->scheduleUpdate();

	return true;
}

void TapDetection::update(float delta)
{

}

void TapDetection::outSideBlockT()
{

}

void TapDetection::outSideBlockS()
{
	
}

bool TapDetection::titleTouchBegan(Touch* pTouch, Event* pEvent)
{
	log("title");
	return true;
}

bool TapDetection::selectTouchBegan(Touch* pTouch, Event* pEvent)
{
	_touchPos = pTouch->getLocation();
	log("select");
	//(this->*outSideBlock)();	// タップ箇所がブロックの外側か
	return true;
}

//bool TapDetection::onTouchBegan(Touch* pTouch, Event* pEvent)
//{
//	Vec2 touchPos = pTouch->getLocation();
//	return true;
//}

void TapDetection::onTouchEnded(Touch* pTouch, Event* pEvent)
{
	//PictureManager::touchEnded(pTouch);
	//changeBegan(&TapDetection::selectTouchBegan);
}

void TapDetection::changeBegan(bool (BaseTap::*method)(Touch* pTouch, Event* pEvent))
{
	listener->onTouchBegan = std::bind(method, this, std::placeholders::_1, std::placeholders::_2);
}
