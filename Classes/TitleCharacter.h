#ifndef _TitleCharacter_h_
#define _TitleCharacter_h_

#include "cocos2d.h"

class TitleCharacter : public cocos2d::Sprite
{
public:
	bool init();
	static TitleCharacter* create();
	cocos2d::Animation* anim;
};

#endif // !_TitleCharacter_h_
