#ifndef _TapDetection_
#define _TapDetection_
#include "cocos2d.h"
#include "BaseTap.h"

class TapDetection : public cocos2d::Node
{
public:
	typedef std::function<bool(cocos2d::Touch*, cocos2d::Event*)> ccTouchBeganCallback;
	typedef std::function<void(cocos2d::Touch*, cocos2d::Event*)> ccTouchCallback;
	
	static TapDetection* sharedTap();

	cocos2d::Vec2 _touchPos;
	cocos2d::EventListenerTouchOneByOne* listener;

	bool init();
	void update(float delta);
	void outSideBlockT();
	void outSideBlockS();

	// タッチイベント処理
	bool titleTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	bool selectTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	
	void changeBegan(bool (BaseTap::*method)(cocos2d::Touch* pTouch, cocos2d::Event* pEvent));

private:
	static TapDetection* tapDetection;
	TapDetection();
	TapDetection(const TapDetection&);
	TapDetection& operator = (const TapDetection&);
	~TapDetection();
	void(TapDetection::*outSideBlock)();
};

#endif
