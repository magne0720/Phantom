#ifndef _TapDetection_
#define _TapDetection_
#include "cocos2d.h"

class TapDetection : public cocos2d::Node
{
public:
	typedef std::function<bool(cocos2d::Touch*, cocos2d::Event*)> ccTouchBeganCallback;
	typedef std::function<void(cocos2d::Touch*, cocos2d::Event*)> ccTouchCallback;
	
	static TapDetection* create(e_Scene scene);

	cocos2d::Vec2 _touchPos;
	cocos2d::EventListenerTouchOneByOne* listener;

	bool init(e_Scene scene);
	void update(float delta);
	void outSideBlockG();
	void outSideBlockT();
	void outSideBlockR();

	// タッチイベント処理
	bool startTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	bool tutrialTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	bool playTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	bool resultTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	
	void changePhase(bool (TapDetection::*method)(cocos2d::Touch* pTouch, cocos2d::Event* pEvent));

private:
	void(TapDetection::*outSideBlock)();
};

#endif
