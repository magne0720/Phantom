#ifndef _TitleLayer_h_
#define _TitleLayer_h_

#include "cocos2d.h"

class TitleLayer : public cocos2d::Layer
{
public:
	bool init();
	static TitleLayer* create();
};

#endif