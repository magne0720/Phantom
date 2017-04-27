#ifndef _PictureManager_
#define _PictureManager_

#include "cocos2d.h"

class PictureManager : public cocos2d::Node
{
public:
	static PictureManager* create();
	bool init();
	void touchEnded(cocos2d::Touch* pTouch);

	// タッチイベント処理
	bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	void onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);

private:
	cocos2d::Sprite* _Pictures[3];
	int _stageNum = 3;
};

#endif
