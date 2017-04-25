#include "TapDetection.h"

USING_NS_CC;

TapDetection* TapDetection::create(e_Scene scene)
{
	TapDetection *pRet = new TapDetection();
	if (pRet && pRet->init(scene))
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

bool TapDetection::init(e_Scene scene)
{
	if (!Node::init())
	{
		return false;
	}

	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(TapDetection::playTouchBegan, this);
	//listener->onTouchMoved = CC_CALLBACK_2(TapDetection::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(TapDetection::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();

	return true;
}

void TapDetection::update(float delta)
{

}

void TapDetection::outSideBlockS()
{
	
}

void TapDetection::outSideBlockT()
{
	
}

void TapDetection::outSideBlockR()
{
	
}

bool TapDetection::startTouchBegan(Touch* pTouch, Event* pEvent)
{
	
	return true;
}

bool TapDetection::tutrialTouchBegan(Touch* pTouch, Event* pEvent)
{
	
	return true;
}

bool TapDetection::playTouchBegan(Touch* pTouch, Event* pEvent)
{
	_touchPos = pTouch->getLocation();
	(this->*outSideBlock)();	// タップ箇所がブロックの外側か
	return true;
}

bool TapDetection::resultTouchBegan(Touch* pTouch, Event* pEvent)
{

	return true;
}

//bool TapDetection::onTouchBegan(Touch* pTouch, Event* pEvent)
//{
//	Vec2 touchPos = pTouch->getLocation();
//	return true;
//}

void TapDetection::onTouchEnded(Touch* pTouch, Event* pEvent)
{
	
	//changePhase(&TapDetection::playTouchBegan);
}

void TapDetection::changePhase(bool (TapDetection::*method)(Touch* pTouch, Event* pEvent))
{
	listener->onTouchBegan = std::bind(method, this, std::placeholders::_1, std::placeholders::_2);
	//std::bind(クラスの呼びたいメンバ関数, クラスのインスタンス, onTouchBeganの第１引数を呼びたいメンバ関数の第１引数へ, onTouchBeganの第2引数を呼びたいメンバ関数の第2引数へ);
	// std::placeholders::_1は呼ばれた時の第１引数。これを呼びたい関数の第ナニ引数に入れるかは順番さえ変えれば自由。
	//onTouchBeganは、bool onTouchBegan(Touch* pTouch, Event* pEvent)　これが呼ばれたら、bool method(Touch* pTouch, Event* pEvent)を呼ぶ。(methodは関数名)
}
