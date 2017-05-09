#ifndef _TitleCharacter_h_
#define _TitleCharacter_h_

#include "cocos2d.h"

class TitleCharacter : public cocos2d::Node
{
public:
	bool init();
	static TitleCharacter* create();
};

#endif // !_TitleCharacter_h_
