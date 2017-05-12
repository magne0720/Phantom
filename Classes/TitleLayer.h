#ifndef _TitleLayer_h_
#define _TitleLayer_h_

#include "cocos2d.h"
#include "TitleBackground.h"

class TitleLayer : public cocos2d::Layer
{
public:
	bool init();
	static TitleLayer* create();
	TitleBackground* tbg;
	
	bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
};

#endif