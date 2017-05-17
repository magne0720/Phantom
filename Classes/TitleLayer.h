#ifndef _TitleLayer_h_
#define _TitleLayer_h_

#include "cocos2d.h"
#include "TitleBackground.h"
#include "CharacterAnimation.h"

class TitleLayer : public cocos2d::Layer
{
public:
	bool init();
	static TitleLayer* create();
	TitleBackground* tbg;
	CharacterAnimation* ca;
	
	bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
};

#endif