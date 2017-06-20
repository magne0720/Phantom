#ifndef _TitleScroll_h_
#define _TitleScroll_h_

#include "cocos2d.h"
#include "ScrollSprite.h"

class TitleScroll : public ScrollSprite
{
public:
	bool init(float scrollSpeed, eOrientation orientation);
	static TitleScroll* create(float scrollSpeed, eOrientation orientation);
};
#endif // !_TitleScroll_h_
