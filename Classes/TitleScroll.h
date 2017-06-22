#ifndef _TitleScroll_h_
#define _TitleScroll_h_

#include "cocos2d.h"
#include "ScrollSprite.h"

class TitleScroll : public ScrollSprite
{
public:
	bool init(float scrollSpeed);
	static TitleScroll* create(float scrollSpeed);
};
#endif // !_TitleScroll_h_
