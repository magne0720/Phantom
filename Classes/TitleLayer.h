#ifndef _TitleLayer_h_
#define _TitleLayer_h_

#include "cocos2d.h"
#include "TitleBackground.h"
#include "TitleScroll.h"

class TitleLayer : public cocos2d::Layer
{
public:
	bool init();
	static TitleLayer* create();
	TitleBackground* tbg;
	bool _replacedScene;
	TitleScroll* ts;
	float _scrollSpeed = 5.0f;
	
	bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
};

#endif