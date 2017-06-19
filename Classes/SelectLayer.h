#ifndef _SelectLayer_
#define _SelectLayer_

#include "cocos2d.h"
#include "ToTitleButton.h"

class SelectLayer : public cocos2d::Layer
{
public:
	bool init();
	bool init(cocos2d::Color4F color);
	static SelectLayer* create();
	static SelectLayer* create(cocos2d::Color4F color);

	// タッチイベント処理
	virtual bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	virtual void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);

	cocos2d::DrawNode* _dot;
	bool _isSceneReplace = false;
	bool _selectedButton = false;

	ToTitleButton* _toTitleButton;
};

#endif