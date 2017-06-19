#ifndef _ToTitleButton_h_
#define _ToTitleButton_h_

#include "cocos2d.h"

class ToTitleButton : public cocos2d::Sprite
{
public:
	bool init();
	static ToTitleButton* create();

	cocos2d::Sprite* _shadow;
};

#endif // !_ToTitleButton_h_
