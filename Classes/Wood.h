#ifndef _Wood_h_
#define _Wood_h_

#include "cocos2d.h"
#include "ColorEnum.h"

class Wood : public cocos2d::Sprite
{
public:
	bool init(cocos2d::SpriteFrame* spFrame, bool green, bool brown);
	static Wood* create(cocos2d::SpriteFrame* spFrame, bool green = false, bool brown = false);

	eColor _colors[2] = { eColor::GREEN, eColor::BROWN };
	bool _bGreen, _bBrown;
};

#endif // !_Wood_h_
