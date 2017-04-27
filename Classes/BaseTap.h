#ifndef _BaseTap_h_
#define _BaseTap_h_

#include "cocos2d.h"

template <class T> class BaseTap : public cocos2d::Node
{
public:
	typedef std::function<bool(cocos2d::Touch*, cocos2d::Event*)> ccTouchBeganCallback;
	typedef std::function<void(cocos2d::Touch*, cocos2d::Event*)> ccTouchCallback;

	// タッチイベント処理
	//bool titleTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	//bool selectTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	//void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);

	cocos2d::Vec2 _touchPos;
	cocos2d::EventListenerTouchOneByOne* listener;

	bool init();
	virtual void update(float delta);

	void initialize()
	{
		listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);

		//listener->onTouchBegan = CC_CALLBACK_2(BaseTap::titleTouchBegan, this);
		//listener->onTouchMoved = CC_CALLBACK_2(BaseTap::onTouchMoved, this);
		//listener->onTouchEnded = CC_CALLBACK_2(BaseTap::onTouchEnded, this);
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	}

	void changeBegan(bool (T::*method)(cocos2d::Touch* pTouch, cocos2d::Event* pEvent))
	{
		listener->onTouchBegan = std::bind(method, this, std::placeholders::_1, std::placeholders::_2);
	}
	void changeMoved(void (T::*method)(cocos2d::Touch* pTouch, cocos2d::Event* pEvent))
	{
		listener->onTouchMoved = std::bind(method, this, std::placeholders::_1, std::placeholders::_2);
	}
	void changeCancelled(void (T::*method)(cocos2d::Touch* pTouch, cocos2d::Event* pEvent))
	{
		listener->onTouchCancelled = std::bind(method, this, std::placeholders::_1, std::placeholders::_2);
	}
	void changeEnded(void (T::*method)(cocos2d::Touch* pTouch, cocos2d::Event* pEvent))
	{
		listener->onTouchEnded = std::bind(method, this, std::placeholders::_1, std::placeholders::_2);
	}
};

#endif // !_BaseTap_h_
