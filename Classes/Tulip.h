#ifndef _Tulip_h_
#define _Tulip_h_

#include "cocos2d.h"

class Tulip : public cocos2d::Sprite
{
public:
	bool init(cocos2d::SpriteFrame* spFrame, bool red, bool pink, bool green);
	static Tulip* create(cocos2d::SpriteFrame* spFrame, bool red = false, bool pink = false, bool green = false);
	bool _bRed, _bPink, _bGreen;

	void update(float delta);
};
#endif // !_Tulip_h_
