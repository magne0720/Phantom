#ifndef _WoodScroll_h_
#define _WoodScroll_h_

#include "cocos2d.h"
#include "ScrollSprite.h"

class WoodScroll : public ScrollSprite
{
public:
	static WoodScroll* create(float scrollSpeed);
	bool init(float scrollSpeed);
};

#endif // !_WoodScroll_h_
